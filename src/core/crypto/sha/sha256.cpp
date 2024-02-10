#include "sha256.h"
#include "../../utils.h"
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>

typedef uint32_t uint32;

/**
 * SHA256 class constructor
 */
sha256::sha256() = default;

/**
 * SHA256 class destructor
 */
sha256::~sha256() = default;

/**
 * Returns a message digest using the SHA256 algorithm
 * @param input message string used as an input to the SHA256 algorithm, must be < size_t bits
 */
std::string sha256::hash(const std::string& input){
    size_t nBuffer; // amount of message blocks
    uint32** buffer; // message block buffers (each 512-bit = 16 32-bit words)
    auto* h = new uint32[HASH_LEN]; // buffer holding the message digest (256-bit = 8 32-bit words)

    buffer = preprocess((unsigned char*) input.c_str(), nBuffer);
    process(buffer, nBuffer, h);

    freeBuffer(buffer, nBuffer);
    return digest(h);
}

/**
 * Preprocessing of the SHA256 algorithm
 * @param input message in byte representation
 * @param nBuffer amount of message blocks
 */
uint32** sha256::preprocess(const unsigned char* input, size_t &nBuffer) const{
    // Padding: input || 1 || 0*K || l (in 64-bit representation)
    size_t mLen = strlen((const char*) input);
    size_t l = mLen * CHAR_LEN_BITS; // length of input in bits
    size_t K = (448 - 1 - l) % MESSAGE_BLOCK_SIZE; // length of zero bit padding (l + 1 + K = 448 mod 512)
    nBuffer = (l + 1 + K + 64) / MESSAGE_BLOCK_SIZE;

    auto** buffer = new uint32*[nBuffer];

    for(size_t i=0; i<nBuffer; i++){
        buffer[i] = new uint32[SEQUENCE_LEN];
    }

    uint32 in;
    size_t index;

    // Either copy existing message, add 1 bit or add 0 bit
    for(size_t i=0; i<nBuffer; i++){
        for(size_t j=0; j<SEQUENCE_LEN; j++){
            in = static_cast<unsigned int>(0x00u);
            for(size_t _k=0; _k < WORD_LEN; _k++){
                index = i*64 +j*4 + _k;
                if(index < mLen){
                    in = in<<8 | static_cast<unsigned int>(input[index]);
                }else if(index == mLen){
                    in = in<<8 | static_cast<unsigned int>(0x80u);
                }else{
                    in = in<<8 | static_cast<unsigned int>(0x00u);
                }
            }
            buffer[i][j] = in;
        }
    }

    // Append the length to the last two 32-bit blocks
    appendLen(l, buffer[nBuffer-1][SEQUENCE_LEN-1], buffer[nBuffer-1][SEQUENCE_LEN-2]);
    return buffer;
}

/**
 * Processing of the SHA256 algorithm
 * @param buffer array holding the preprocessed
 * @param nBuffer amount of message blocks
 * @param h array of output message digest
 */
void sha256::process(uint32** buffer, size_t nBuffer, uint32* h){
    uint32 s[WORKING_VAR_LEN];
    uint32 w[MESSAGE_SCHEDULE_LEN];

    memcpy(h, hPrime, WORKING_VAR_LEN*sizeof(uint32));

    for(size_t i=0; i<nBuffer; i++){
        // copy over to message schedule
        memcpy(w, buffer[i], SEQUENCE_LEN*sizeof(uint32));

        // Prepare the message schedule
        for(size_t j=16; j<MESSAGE_SCHEDULE_LEN; j++){
            w[j] = w[j-16] + sig0_s(w[j-15]) + w[j-7] + sig1_s(w[j-2]);
        }
        // Initialize the working variables
        memcpy(s, h, WORKING_VAR_LEN*sizeof(uint32));

        // Compression
        for(size_t j=0; j<MESSAGE_SCHEDULE_LEN; j++){
            uint32 temp1 = s[7] + Sig1_s(s[4]) + Ch_s(s[4], s[5], s[6]) + k[j] + w[j];
            uint32 temp2 = Sig0_s(s[0]) + Maj_s(s[0], s[1], s[2]);

            s[7] = s[6];
            s[6] = s[5];
            s[5] = s[4];
            s[4] = s[3] + temp1;
            s[3] = s[2];
            s[2] = s[1];
            s[1] = s[0];
            s[0] = temp1 + temp2;
        }

        // Compute the intermediate hash values
        for(size_t j=0; j<WORKING_VAR_LEN; j++){
            h[j] += s[j];
        }
    }

}

/**
 * Appends the length of the message in the last two message blocks
 * @param l message size in bits
 * @param lo pointer to second last message block
 * @param hi pointer to last message block
 */
void sha256::appendLen(size_t l, uint32& lo, uint32& hi){
    lo = l;
    hi = 0x00;
}

/**
 * Outputs the final message digest in hex representation
 * @param h array of output message digest
 */
std::string sha256::digest(uint32* h) const{
    std::stringstream ss;
    for(size_t i=0; i<OUTPUT_LEN; i++){
        ss << std::hex << std::setw(8) << std::setfill('0') << h[i];
    }
    delete[] h;
    return ss.str();
}

/**
 * Free the buffer correctly
 * @param buffer array holding the preprocessed
 * @param nBuffer amount of message blocks
 */
void sha256::freeBuffer(uint32** buffer, size_t nBuffer){
    for(size_t i=0; i<nBuffer; i++){
        delete[] buffer[i];
    }
    delete[] buffer;
}

std::string sha256::fast(const std::string & input){
    return sha256().hash(input);
}

hash256 sha256::fastH(const std::string & input){
    return to_hash256(fast(input));
}
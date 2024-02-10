#include <cstring>
#include <iomanip>
#include <ios>
#include "sha384.h"
#include "../../utils.h"

typedef unsigned long long uint64;

/**
 * SHA384 class constructor
 */
sha384::sha384() = default;

/**
 * SHA384 class destructor
 */
sha384::~sha384() = default;

/**
 * Returns a message digest using the SHA384 algorithm
 * @param input message string used as an input to the SHA384 algorithm, must be < size_t bits
 */
std::string sha384::hash(const std::string& input){
    size_t nBuffer; // amount of message blocks
    uint64** buffer; // message block buffers (each 1024-bit = 16 64-bit words)
    auto* h = new uint64[HASH_LEN]; // buffer holding the message digest (512-bit = 8 64-bit words)

    buffer = preprocess((unsigned char*) input.c_str(), nBuffer);
    process(buffer, nBuffer, h);

    freeBuffer(buffer, nBuffer);
    return digest(h);
}

/**
 * Preprocessing of the SHA384 algorithm
 * @param input message in byte representation
 * @param nBuffer amount of message blocks
 */
uint64** sha384::preprocess(const unsigned char* input, size_t &nBuffer) const{
    // Padding: input || 1 || 0*k || l (in 128-bit representation)
    size_t mLen = strlen((const char*) input);
    size_t l = mLen * CHAR_LEN_BITS; // length of input in bits
    size_t K= (896-1-l) % MESSAGE_BLOCK_SIZE; // length of zero bit padding (l + 1 + k = 896 mod 1024)
    nBuffer = (l+1+K+128) / MESSAGE_BLOCK_SIZE;

    auto** buffer = new uint64*[nBuffer];

    for(size_t i=0; i<nBuffer; i++){
        buffer[i] = new uint64[SEQUENCE_LEN];
    }

    uint64 in;
    size_t index;

    // Either copy existing message, add 1 bit or add 0 bit
    for(size_t i=0; i<nBuffer; i++){
        for(size_t j=0; j<SEQUENCE_LEN; j++){
            in = 0x0ULL;
            for(size_t _k=0; _k<WORD_LEN; _k++){
                index = i*128+j*8+_k;
                if(index < mLen){
                    in = in<<8 | (uint64)input[index];
                }else if(index == mLen){
                    in = in<<8 | 0x80ULL;
                }else{
                    in = in<<8 | 0x0ULL;
                }
            }
            buffer[i][j] = in;
        }
    }

    // Append the length to the last two 64-bit blocks
    appendLen(l, buffer[nBuffer-1][SEQUENCE_LEN-1], buffer[nBuffer-1][SEQUENCE_LEN-2]);
    return buffer;
}

/**
 * Processing of the SHA384 algorithm
 * @param buffer array holding the preprocessed
 * @param nBuffer amount of message blocks
 * @param h array of output message digest
 */
void sha384::process(uint64** buffer, size_t nBuffer, uint64* h){
    uint64 s[WORKING_VAR_LEN];
    uint64 w[MESSAGE_SCHEDULE_LEN];

    memcpy(h, hPrime, WORKING_VAR_LEN*sizeof(uint64));

    for(size_t i=0; i<nBuffer; i++){
        // copy over to message schedule
        memcpy(w, buffer[i], SEQUENCE_LEN*sizeof(uint64));

        // Prepare the message schedule
        for(size_t j=16; j<MESSAGE_SCHEDULE_LEN; j++){
            w[j] = w[j-16] + sig0(w[j-15]) + w[j-7] + sig1(w[j-2]);
        }
        // Initialize the working variables
        memcpy(s, h, WORKING_VAR_LEN*sizeof(uint64));

        // Compression
        for(size_t j=0; j<MESSAGE_SCHEDULE_LEN; j++){
            uint64 temp1 = s[7] + Sig1(s[4]) + Ch(s[4], s[5], s[6]) + k[j] + w[j];
            uint64 temp2 = Sig0(s[0]) + Maj(s[0], s[1], s[2]);

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
void sha384::appendLen(size_t l, uint64& lo, uint64& hi){
    lo = l;
    hi = 0x00ULL;
}

/**
 * Outputs the final message digest in hex representation
 * @param h array of output message digest
 */
std::string sha384::digest(uint64* h) const{
    std::stringstream ss;
    for(size_t i=0; i<OUTPUT_LEN; i++){
        ss << std::hex << std::setw(16) << std::setfill('0') << h[i];
    }
    delete[] h;
    return ss.str();
}

/**
 * Free the buffer correctly
 * @param buffer array holding the preprocessed
 * @param nBuffer amount of message blocks
 */
void sha384::freeBuffer(uint64** buffer, size_t nBuffer){
    for(size_t i=0; i<nBuffer; i++){
        delete[] buffer[i];
    }

    delete[] buffer;
}

std::string sha384::fast(const std::string & input){
    return sha384().hash(input);
}

hash384 sha384::fastH(const std::string & input){
    return to_hash384(fast(input));
}
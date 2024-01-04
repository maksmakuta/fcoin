#include <cstring>
#include <ios>
#include <iomanip>
#include "sha256.h"

sha256::sha256(): m_blocklen(0), m_bitlen(0) {
    m_state[0] = 0x6a09e667;
    m_state[1] = 0xbb67ae85;
    m_state[2] = 0x3c6ef372;
    m_state[3] = 0xa54ff53a;
    m_state[4] = 0x510e527f;
    m_state[5] = 0x9b05688c;
    m_state[6] = 0x1f83d9ab;
    m_state[7] = 0x5be0cd19;
}

void sha256::update(const u8* data, size_t length) {
    for (size_t i = 0 ; i < length ; i++) {
        m_data[m_blocklen++] = data[i];
        if (m_blocklen == 64) {
            transform();

            // End of the block
            m_bitlen += 512;
            m_blocklen = 0;
        }
    }
}

void sha256::update(const str &data) {
    update(reinterpret_cast<const u8*> (data.c_str()), data.size());
}

arr<u8,32> sha256::digest() {
    arr<u8,32> hash{};
    pad();
    revert(hash);
    return hash;
}


u32 sha256::rotr(u32 x, u32 n) {
    return (x >> n) | (x << (32 - n));
}

u32 sha256::choose(u32 e, u32 f, u32 g) {
    return (e & f) ^ (~e & g);
}

u32 sha256::majority(u32 a, u32 b, u32 c) {
    return (a & (b | c)) | (b & c);
}

u32 sha256::sig0(u32 x) {
    return sha256::rotr(x, 7) ^ sha256::rotr(x, 18) ^ (x >> 3);
}

u32 sha256::sig1(u32 x) {
    return sha256::rotr(x, 17) ^ sha256::rotr(x, 19) ^ (x >> 10);
}

void sha256::transform() {
    u32 maj, xorA, ch, xorE, sum, newA, newE, m[64];
    u32 state[8];

    for (u8 i = 0, j = 0; i < 16; i++, j += 4) { // Split data in 32 bit blocks for the 16 first words
        m[i] = (m_data[j] << 24) | (m_data[j + 1] << 16) | (m_data[j + 2] << 8) | (m_data[j + 3]);
    }

    for (u8 k = 16 ; k < 64; k++) { // Remaining 48 blocks
        m[k] = sha256::sig1(m[k - 2]) + m[k - 7] + sha256::sig0(m[k - 15]) + m[k - 16];
    }

    for(u8 i = 0 ; i < 8 ; i++) {
        state[i] = m_state[i];
    }

    for (u8 i = 0; i < 64; i++) {
        maj   = sha256::majority(state[0], state[1], state[2]);
        xorA  = sha256::rotr(state[0], 2) ^ sha256::rotr(state[0], 13) ^ sha256::rotr(state[0], 22);

        ch = choose(state[4], state[5], state[6]);

        xorE  = sha256::rotr(state[4], 6) ^ sha256::rotr(state[4], 11) ^ sha256::rotr(state[4], 25);

        sum  = m[i] + K[i] + state[7] + ch + xorE;
        newA = xorA + maj + sum;
        newE = state[3] + sum;

        state[7] = state[6];
        state[6] = state[5];
        state[5] = state[4];
        state[4] = newE;
        state[3] = state[2];
        state[2] = state[1];
        state[1] = state[0];
        state[0] = newA;
    }

    for(u8 i = 0 ; i < 8 ; i++) {
        m_state[i] += state[i];
    }
}

void sha256::pad() {

    u64 i = m_blocklen;
    u8 end = m_blocklen < 56 ? 56 : 64;

    m_data[i++] = 0x80; // Append a bit 1
    while (i < end) {
        m_data[i++] = 0x00; // Pad with zeros
    }

    if(m_blocklen >= 56) {
        transform();
        memset(m_data, 0, 56);
    }

    // Append to the padding the total message's length in bits and transform.
    m_bitlen += m_blocklen * 8;
    m_data[63] = m_bitlen;
    m_data[62] = m_bitlen >> 8;
    m_data[61] = m_bitlen >> 16;
    m_data[60] = m_bitlen >> 24;
    m_data[59] = m_bitlen >> 32;
    m_data[58] = m_bitlen >> 40;
    m_data[57] = m_bitlen >> 48;
    m_data[56] = m_bitlen >> 56;
    transform();
}

void sha256::revert(arr<u8, 32> & hash) {
    // SHA uses big endian byte ordering
    // Revert all bytes
    for (u8 i = 0 ; i < 4 ; i++) {
        for(u8 j = 0 ; j < 8 ; j++) {
            hash[i + (j * 4)] = (m_state[j] >> (24 - i * 8)) & 0x000000ff;
        }
    }
}

str sha256::toString(const arr<u8, 32> & digest) {
    std::stringstream s;
    s << std::setfill('0') << std::hex;

    for(u8 i = 0 ; i < 32 ; i++) {
        s << std::setw(2) << (unsigned int) digest[i];
    }

    return s.str();
}
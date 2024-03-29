#include <cstring>
#include <sstream>
#include <iomanip>
#include "ripemd160.h"

/* ROL(x, n) cyclically rotates x over n bits to the left */
/* x must be of an unsigned 32 bits type and 0 <= n < 32. */
#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* the three basic functions F(), G() and H() */
#define F(x, y, z)	((x) ^ (y) ^ (z))
#define G(x, y, z)	(((x) & (y)) | (~(x) & (z)))
#define H(x, y, z)	(((x) | ~(y)) ^ (z))
#define I(x, y, z)	(((x) & (z)) | ((y) & ~(z)))
#define J(x, y, z)	((x) ^ ((y) | ~(z)))

/* the eight basic operations FF() through III() */
#define FF(a, b, c, d, e, x, s)	{\
	(a) += F((b), (c), (d)) + (x);\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define GG(a, b, c, d, e, x, s)	{\
	(a) += G((b), (c), (d)) + (x) + 0x5a827999UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define HH(a, b, c, d, e, x, s) {\
	(a) += H((b), (c), (d)) + (x) + 0x6ed9eba1UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define II(a, b, c, d, e, x, s) {\
	(a) += I((b), (c), (d)) + (x) + 0x8f1bbcdcUL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define JJ(a, b, c, d, e, x, s) {\
	(a) += J((b), (c), (d)) + (x) + 0xa953fd4eUL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define FFF(a, b, c, d, e, x, s)	{\
	(a) += F((b), (c), (d)) + (x);\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define GGG(a, b, c, d, e, x, s)	{\
	(a) += G((b), (c), (d)) + (x) + 0x7a6d76e9UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define HHH(a, b, c, d, e, x, s) {\
	(a) += H((b), (c), (d)) + (x) + 0x6d703ef3UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define III(a, b, c, d, e, x, s) {\
	(a) += I((b), (c), (d)) + (x) + 0x5c4dd124UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

#define JJJ(a, b, c, d, e, x, s) {\
	(a) += J((b), (c), (d)) + (x) + 0x50a28be6UL;\
	(a) = ROL((a), (s)) + (e);\
	(c) = ROL((c), 10);\
	}

ripemd160::ripemd160(){
    iv[0] = 0x67452301UL;
    iv[1] = 0xefcdab89UL;
    iv[2] = 0x98badcfeUL;
    iv[3] = 0x10325476UL;
    iv[4] = 0xc3d2e1f0UL;
    bytesHi = 0;
    bytesLo = 0;
}

void rmd160ByteSwap (u32 * dest, u8 const *src, unsigned int words){
    do
    {
        *dest++ = (u32) ((unsigned) src[3] << 8 | src[2]) << 16 |
                  ((unsigned) src[1] << 8 | src[0]);
        src += 4;
    }
    while (--words);
}

void RMDcompress (u32 * MDbuf, const u32 * X){
    u32 aa = MDbuf[0], bb = MDbuf[1], cc = MDbuf[2],
            dd = MDbuf[3], ee = MDbuf[4];
    u32 aaa = MDbuf[0], bbb = MDbuf[1], ccc = MDbuf[2],
            ddd = MDbuf[3], eee = MDbuf[4];

/* round 1 */
    FF (aa, bb, cc, dd, ee, X[0], 11)
    FF (ee, aa, bb, cc, dd, X[1], 14)
    FF (dd, ee, aa, bb, cc, X[2], 15)
    FF (cc, dd, ee, aa, bb, X[3], 12)
    FF (bb, cc, dd, ee, aa, X[4], 5)
    FF (aa, bb, cc, dd, ee, X[5], 8)
    FF (ee, aa, bb, cc, dd, X[6], 7)
    FF (dd, ee, aa, bb, cc, X[7], 9)
    FF (cc, dd, ee, aa, bb, X[8], 11)
    FF (bb, cc, dd, ee, aa, X[9], 13)
    FF (aa, bb, cc, dd, ee, X[10], 14)
    FF (ee, aa, bb, cc, dd, X[11], 15)
    FF (dd, ee, aa, bb, cc, X[12], 6)
    FF (cc, dd, ee, aa, bb, X[13], 7)
    FF (bb, cc, dd, ee, aa, X[14], 9)
    FF (aa, bb, cc, dd, ee, X[15], 8)

/* round 2 */
    GG (ee, aa, bb, cc, dd, X[7], 7)
    GG (dd, ee, aa, bb, cc, X[4], 6)
    GG (cc, dd, ee, aa, bb, X[13], 8)
    GG (bb, cc, dd, ee, aa, X[1], 13)
    GG (aa, bb, cc, dd, ee, X[10], 11)
    GG (ee, aa, bb, cc, dd, X[6], 9)
    GG (dd, ee, aa, bb, cc, X[15], 7)
    GG (cc, dd, ee, aa, bb, X[3], 15)
    GG (bb, cc, dd, ee, aa, X[12], 7)
    GG (aa, bb, cc, dd, ee, X[0], 12)
    GG (ee, aa, bb, cc, dd, X[9], 15)
    GG (dd, ee, aa, bb, cc, X[5], 9)
    GG (cc, dd, ee, aa, bb, X[2], 11)
    GG (bb, cc, dd, ee, aa, X[14], 7)
    GG (aa, bb, cc, dd, ee, X[11], 13)
    GG (ee, aa, bb, cc, dd, X[8], 12)

/* round 3 */
    HH (dd, ee, aa, bb, cc, X[3], 11)
    HH (cc, dd, ee, aa, bb, X[10], 13)
    HH (bb, cc, dd, ee, aa, X[14], 6)
    HH (aa, bb, cc, dd, ee, X[4], 7)
    HH (ee, aa, bb, cc, dd, X[9], 14)
    HH (dd, ee, aa, bb, cc, X[15], 9)
    HH (cc, dd, ee, aa, bb, X[8], 13)
    HH (bb, cc, dd, ee, aa, X[1], 15)
    HH (aa, bb, cc, dd, ee, X[2], 14)
    HH (ee, aa, bb, cc, dd, X[7], 8)
    HH (dd, ee, aa, bb, cc, X[0], 13)
    HH (cc, dd, ee, aa, bb, X[6], 6)
    HH (bb, cc, dd, ee, aa, X[13], 5)
    HH (aa, bb, cc, dd, ee, X[11], 12)
    HH (ee, aa, bb, cc, dd, X[5], 7)
    HH (dd, ee, aa, bb, cc, X[12], 5)

/* round 4 */
    II (cc, dd, ee, aa, bb, X[1], 11)
    II (bb, cc, dd, ee, aa, X[9], 12)
    II (aa, bb, cc, dd, ee, X[11], 14)
    II (ee, aa, bb, cc, dd, X[10], 15)
    II (dd, ee, aa, bb, cc, X[0], 14)
    II (cc, dd, ee, aa, bb, X[8], 15)
    II (bb, cc, dd, ee, aa, X[12], 9)
    II (aa, bb, cc, dd, ee, X[4], 8)
    II (ee, aa, bb, cc, dd, X[13], 9)
    II (dd, ee, aa, bb, cc, X[3], 14)
    II (cc, dd, ee, aa, bb, X[7], 5)
    II (bb, cc, dd, ee, aa, X[15], 6)
    II (aa, bb, cc, dd, ee, X[14], 8)
    II (ee, aa, bb, cc, dd, X[5], 6)
    II (dd, ee, aa, bb, cc, X[6], 5)
    II (cc, dd, ee, aa, bb, X[2], 12)

/* round 5 */
    JJ (bb, cc, dd, ee, aa, X[4], 9)
    JJ (aa, bb, cc, dd, ee, X[0], 15)
    JJ (ee, aa, bb, cc, dd, X[5], 5)
    JJ (dd, ee, aa, bb, cc, X[9], 11)
    JJ (cc, dd, ee, aa, bb, X[7], 6)
    JJ (bb, cc, dd, ee, aa, X[12], 8)
    JJ (aa, bb, cc, dd, ee, X[2], 13)
    JJ (ee, aa, bb, cc, dd, X[10], 12)
    JJ (dd, ee, aa, bb, cc, X[14], 5)
    JJ (cc, dd, ee, aa, bb, X[1], 12)
    JJ (bb, cc, dd, ee, aa, X[3], 13)
    JJ (aa, bb, cc, dd, ee, X[8], 14)
    JJ (ee, aa, bb, cc, dd, X[11], 11)
    JJ (dd, ee, aa, bb, cc, X[6], 8)
    JJ (cc, dd, ee, aa, bb, X[15], 5)
    JJ (bb, cc, dd, ee, aa, X[13], 6)

/* parallel round 1 */
    JJJ (aaa, bbb, ccc, ddd, eee, X[5], 8)
    JJJ (eee, aaa, bbb, ccc, ddd, X[14], 9)
    JJJ (ddd, eee, aaa, bbb, ccc, X[7], 9)
    JJJ (ccc, ddd, eee, aaa, bbb, X[0], 11)
    JJJ (bbb, ccc, ddd, eee, aaa, X[9], 13)
    JJJ (aaa, bbb, ccc, ddd, eee, X[2], 15)
    JJJ (eee, aaa, bbb, ccc, ddd, X[11], 15)
    JJJ (ddd, eee, aaa, bbb, ccc, X[4], 5)
    JJJ (ccc, ddd, eee, aaa, bbb, X[13], 7)
    JJJ (bbb, ccc, ddd, eee, aaa, X[6], 7)
    JJJ (aaa, bbb, ccc, ddd, eee, X[15], 8)
    JJJ (eee, aaa, bbb, ccc, ddd, X[8], 11)
    JJJ (ddd, eee, aaa, bbb, ccc, X[1], 14)
    JJJ (ccc, ddd, eee, aaa, bbb, X[10], 14)
    JJJ (bbb, ccc, ddd, eee, aaa, X[3], 12)
    JJJ (aaa, bbb, ccc, ddd, eee, X[12], 6)

/* parallel round 2 */
    III (eee, aaa, bbb, ccc, ddd, X[6], 9)
    III (ddd, eee, aaa, bbb, ccc, X[11], 13)
    III (ccc, ddd, eee, aaa, bbb, X[3], 15)
    III (bbb, ccc, ddd, eee, aaa, X[7], 7)
    III (aaa, bbb, ccc, ddd, eee, X[0], 12)
    III (eee, aaa, bbb, ccc, ddd, X[13], 8)
    III (ddd, eee, aaa, bbb, ccc, X[5], 9)
    III (ccc, ddd, eee, aaa, bbb, X[10], 11)
    III (bbb, ccc, ddd, eee, aaa, X[14], 7)
    III (aaa, bbb, ccc, ddd, eee, X[15], 7)
    III (eee, aaa, bbb, ccc, ddd, X[8], 12)
    III (ddd, eee, aaa, bbb, ccc, X[12], 7)
    III (ccc, ddd, eee, aaa, bbb, X[4], 6)
    III (bbb, ccc, ddd, eee, aaa, X[9], 15)
    III (aaa, bbb, ccc, ddd, eee, X[1], 13)
    III (eee, aaa, bbb, ccc, ddd, X[2], 11)

/* parallel round 3 */
    HHH (ddd, eee, aaa, bbb, ccc, X[15], 9)
    HHH (ccc, ddd, eee, aaa, bbb, X[5], 7)
    HHH (bbb, ccc, ddd, eee, aaa, X[1], 15)
    HHH (aaa, bbb, ccc, ddd, eee, X[3], 11)
    HHH (eee, aaa, bbb, ccc, ddd, X[7], 8)
    HHH (ddd, eee, aaa, bbb, ccc, X[14], 6)
    HHH (ccc, ddd, eee, aaa, bbb, X[6], 6)
    HHH (bbb, ccc, ddd, eee, aaa, X[9], 14)
    HHH (aaa, bbb, ccc, ddd, eee, X[11], 12)
    HHH (eee, aaa, bbb, ccc, ddd, X[8], 13)
    HHH (ddd, eee, aaa, bbb, ccc, X[12], 5)
    HHH (ccc, ddd, eee, aaa, bbb, X[2], 14)
    HHH (bbb, ccc, ddd, eee, aaa, X[10], 13)
    HHH (aaa, bbb, ccc, ddd, eee, X[0], 13)
    HHH (eee, aaa, bbb, ccc, ddd, X[4], 7)
    HHH (ddd, eee, aaa, bbb, ccc, X[13], 5)

/* parallel round 4 */
    GGG (ccc, ddd, eee, aaa, bbb, X[8], 15)
    GGG (bbb, ccc, ddd, eee, aaa, X[6], 5)
    GGG (aaa, bbb, ccc, ddd, eee, X[4], 8)
    GGG (eee, aaa, bbb, ccc, ddd, X[1], 11)
    GGG (ddd, eee, aaa, bbb, ccc, X[3], 14)
    GGG (ccc, ddd, eee, aaa, bbb, X[11], 14)
    GGG (bbb, ccc, ddd, eee, aaa, X[15], 6)
    GGG (aaa, bbb, ccc, ddd, eee, X[0], 14)
    GGG (eee, aaa, bbb, ccc, ddd, X[5], 6)
    GGG (ddd, eee, aaa, bbb, ccc, X[12], 9)
    GGG (ccc, ddd, eee, aaa, bbb, X[2], 12)
    GGG (bbb, ccc, ddd, eee, aaa, X[13], 9)
    GGG (aaa, bbb, ccc, ddd, eee, X[9], 12)
    GGG (eee, aaa, bbb, ccc, ddd, X[7], 5)
    GGG (ddd, eee, aaa, bbb, ccc, X[10], 15)
    GGG (ccc, ddd, eee, aaa, bbb, X[14], 8)

/* parallel round 5 */
    FFF (bbb, ccc, ddd, eee, aaa, X[12], 8)
    FFF (aaa, bbb, ccc, ddd, eee, X[15], 5)
    FFF (eee, aaa, bbb, ccc, ddd, X[10], 12)
    FFF (ddd, eee, aaa, bbb, ccc, X[4], 9)
    FFF (ccc, ddd, eee, aaa, bbb, X[1], 12)
    FFF (bbb, ccc, ddd, eee, aaa, X[5], 5)
    FFF (aaa, bbb, ccc, ddd, eee, X[8], 14)
    FFF (eee, aaa, bbb, ccc, ddd, X[7], 6)
    FFF (ddd, eee, aaa, bbb, ccc, X[6], 8)
    FFF (ccc, ddd, eee, aaa, bbb, X[2], 13)
    FFF (bbb, ccc, ddd, eee, aaa, X[13], 6)
    FFF (aaa, bbb, ccc, ddd, eee, X[14], 5)
    FFF (eee, aaa, bbb, ccc, ddd, X[0], 15)
    FFF (ddd, eee, aaa, bbb, ccc, X[3], 13)
    FFF (ccc, ddd, eee, aaa, bbb, X[9], 11)
    FFF (bbb, ccc, ddd, eee, aaa, X[11], 11)

/* combine results */
    ddd += cc + MDbuf[1];		/* final result for MDbuf[0] */
    MDbuf[1] = MDbuf[2] + dd + eee;
    MDbuf[2] = MDbuf[3] + ee + aaa;
    MDbuf[3] = MDbuf[4] + aa + bbb;
    MDbuf[4] = MDbuf[0] + bb + ccc;
    MDbuf[0] = ddd;
}


void ripemd160::update(const u8 * data, size_t len){
    unsigned i;

    /* Update bitcount */
    u32 t = bytesLo;
    if ((bytesLo = t + len) < t)
        bytesHi++;		/* Carry from low to high */

    i = (unsigned) t % RMD160_BLOCKBYTES;	/* Bytes already in ctx->key */

    /* i is always less than RMD160_BLOCKBYTES. */
    if (RMD160_BLOCKBYTES - i > len)
    {
        std::memcpy ( key + i, data, len);
        return;
    }

    if (i)
    {				/* First chunk is an odd size */
        memcpy ((u8 *) key + i, data, RMD160_BLOCKBYTES - i);
        rmd160ByteSwap (key, (u8 *) key, RMD160_BLOCKWORDS);
        RMDcompress (iv, key);
        data += RMD160_BLOCKBYTES - i;
        len -= RMD160_BLOCKBYTES - i;
    }

    /* Process data in 64-byte chunks */
    while (len >= RMD160_BLOCKBYTES)
    {
        rmd160ByteSwap (key, data, RMD160_BLOCKWORDS);
        RMDcompress (iv, key);
        data += RMD160_BLOCKBYTES;
        len -= RMD160_BLOCKBYTES;
    }

    /* Handle any remaining bytes of data. */
    if (len)
        memcpy (key, data, len);
}

void ripemd160::update(const str &data){
    update(reinterpret_cast<const u8 *>(data.c_str()), data.size());
}

void RMDFinish (u32 * MDbuf, u8 * strptr, u32 lswlen,u32 mswlen){
    u32 i;			/* counter */
    u32 X[16];		/* message words */

    memset (X, 0, 16 * sizeof (u32));

/* put bytes from strptr into X */
    for (i = 0; i < (lswlen & 63); i++)
    {
        /* byte i goes into word X[i div 4] at pos. 8*(i mod 4) */
        X[i >> 2] ^= (u32) * strptr++ << (8 * (i & 3));
    }

    /* append the bit m_n == 1 */
    X[(lswlen >> 2) & 15] ^= (u32) 1 << (8 * (lswlen & 3) + 7);

    if ((lswlen & 63) > 55)
    {
        /* length goes to next block */
        RMDcompress (MDbuf, X);
        memset (X, 0, 16 * sizeof (u32));
    }

    /* append length in bits */
    X[14] = lswlen << 3;
    X[15] = (lswlen >> 29) | (mswlen << 3);
    RMDcompress (MDbuf, X);
}

str ripemd160::digest(){
    int i;
    u32 t;
    u8 digest[RMD160_HASHBYTES];
    RMDFinish (iv, (u8 *) key, bytesLo, bytesHi);
    for (i = 0; i < RMD160_HASHWORDS; i++){
        t = iv[i];
        digest[i * 4 + 0] = (u8) t;
        digest[i * 4 + 1] = (u8) (t >> 8);
        digest[i * 4 + 2] = (u8) (t >> 16);
        digest[i * 4 + 3] = (u8) (t >> 24);
    }
    clear();
    std::stringstream s;
    s << std::setfill('0') << std::hex;
    for(u8 j : digest) {
        s << std::setw(2) << (unsigned int) j;
    }
    return s.str();
}

void ripemd160::clear() {
    memset(key,0,RMD160_BLOCKWORDS);
    memset(iv,0,RMD160_HASHWORDS);
    this->bytesHi = 0;
    this->bytesLo = 0;
}

str ripemd160::fast(const str& input){
    ripemd160 r;
    r.update(input);
    return r.digest();
}
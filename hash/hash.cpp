#include "pch.h"
#include "hash.h"

void SHA1ProcessMessageBlock(uint32_t intermediateHash[], uint8_t block[]) {
	/* Constants defined in FIPS 180-3, section 4.2.1 */
	const uint32_t K[4] = {
		0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
	};
	int t; /* Loop counter */
	uint32_t temp; /* Temporary word value */
	uint32_t W[80]; /* Word sequence */
	uint32_t A, B, C, D, E; /* Word buffers */

	/*
     * Initialize the first 16 words in the array W
     */
	for (t = 0; t < 16; t++) {
		W[t] = (block[t * 4]) << 24;
		W[t] |= (block[t * 4 + 1]) << 16;
		W[t] |= (block[t * 4 + 2]) << 8;
		W[t] |= (block[t * 4 + 3]);
	}

	for (t = 16; t < 80; t++)
		W[t] = SHA1_ROTL(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);

	A = intermediateHash[0];
	B = intermediateHash[1];
	C = intermediateHash[2];
	D = intermediateHash[3];
	E = intermediateHash[4];

	for (t = 0; t < 20; t++) {
		temp = SHA1_ROTL(5, A) + SHA_Ch(B, C, D) + E + W[t] + K[0];
		E = D;
		D = C;
		C = SHA1_ROTL(30, B);
		B = A;
		A = temp;
	}

	for (t = 20; t < 40; t++) {
		temp = SHA1_ROTL(5, A) + SHA_Parity(B, C, D) + E + W[t] + K[1];
		E = D;
		D = C;
		C = SHA1_ROTL(30, B);
		B = A;
		A = temp;
	}

	for (t = 40; t < 60; t++) {
		temp = SHA1_ROTL(5, A) + SHA_Maj(B, C, D) + E + W[t] + K[2];
		E = D;
		D = C;
		C = SHA1_ROTL(30, B);
		B = A;
		A = temp;
	}

	for (t = 60; t < 80; t++) {
		temp = SHA1_ROTL(5, A) + SHA_Parity(B, C, D) + E + W[t] + K[3];
		E = D;
		D = C;
		C = SHA1_ROTL(30, B);
		B = A;
		A = temp;
	}

	intermediateHash[0] += A;
	intermediateHash[1] += B;
	intermediateHash[2] += C;
	intermediateHash[3] += D;
	intermediateHash[4] += E;
}
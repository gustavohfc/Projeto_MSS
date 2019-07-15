#pragma once

#define SHA1_ROTL(bits, word) \
	(((word) << (bits)) | ((word) >> (32 - (bits))))

#define SHA_Ch(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))

#define SHA_Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define SHA_Parity(x, y, z) ((x) ^ (y) ^ (z))

void SHA1ProcessMessageBlock(uint32_t intermediateHash[], uint8_t block[]);
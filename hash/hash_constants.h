#pragma once

#define HASH_CMD_ADDR 0x8000 // 1 word

#define HASH_DATA_START_ADDR (HASH_CMD_ADDR + 4) // 32 words
#define HASH_DATA_LAST_ADDR (HASH_DATA_START_ADDR + 0x7C)

#define HASH_RESULT_START_ADDR (HASH_DATA_LAST_ADDR + 4) // 16 words
#define HASH_RESULT_LAST_ADDR (HASH_RESULT_START_ADDR + 0x3C)

enum HashCmd : int {
	Sha1Next = 0,
	Sha1Last,
	Sha1Reset,

	Sha256Next,
	Sha256Last,
	Sha256Reset,

	Sha512Next,
	Sha512Last,
	Sha512Reset,
};

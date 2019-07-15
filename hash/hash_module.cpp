#include "pch.h"
#include "hash_module.h"
#include "hash_constants.h"
#include "hash.h"

void hash_module::wait_loop() {
	if (wait_count > 0) {
		wait_count--;
	}
}

simple_bus_status hash_module::read(int* data, unsigned address) {
	if (address >= HASH_RESULT_START_ADDR && address <= HASH_RESULT_LAST_ADDR) {
		if (wait_count != 0) {
			return SIMPLE_BUS_WAIT;
		}

		auto t = (address - HASH_RESULT_START_ADDR) / 4;

		*data = sha1Intermediate[(address - HASH_RESULT_START_ADDR) / 4];
		return SIMPLE_BUS_OK;
	}

	sb_fprintf(stdout, "%s %s : Invalid read address (%u) \n", sc_time_stamp().to_string().c_str(), name(), address);
	return SIMPLE_BUS_ERROR;
}

simple_bus_status hash_module::write(int* data, unsigned address) {
	if (wait_count != 0) {
		return SIMPLE_BUS_WAIT;
	}

	if (address == HASH_LAST_BLOCK_SIZE) {

		lastBlockSize = *data;
		return SIMPLE_BUS_OK;
	}

	if (address >= HASH_DATA_START_ADDR && address <= HASH_DATA_LAST_ADDR) {

		auto baseAddr = address - HASH_DATA_START_ADDR;

		this->data[baseAddr] = uint8_t(*data >> 24);
		this->data[baseAddr + 1] = uint8_t(*data >> 16);
		this->data[baseAddr + 2] = uint8_t(*data >> 8);
		this->data[baseAddr + 3] = uint8_t(*data);
		return SIMPLE_BUS_OK;
	}

	if (address == HASH_CMD_ADDR) {

		switch (*data) {
			case Sha1Next:
				sha1Next();
				wait_count = nr_wait_states;
				return SIMPLE_BUS_OK;

			case Sha1Last:
				sha1Last();
				wait_count = nr_wait_states;
				return SIMPLE_BUS_OK;

			case Sha1Reset:
				sha1Reset();
				return SIMPLE_BUS_OK;

			default:
				sb_fprintf(stdout, "%s %s : Invalid CMD address (%d) \n", sc_time_stamp().to_string().c_str(), name(), *data);
				return SIMPLE_BUS_ERROR;
		}
	}

	sb_fprintf(stdout, "%s %s : Invalid write address (%u) \n", sc_time_stamp().to_string().c_str(), name(), address);
	return SIMPLE_BUS_ERROR;
}

bool hash_module::direct_read(int* data, unsigned address) {
	read(data, address); // TODO
	return true;
}

bool hash_module::direct_write(int* data, unsigned address) {
	write(data, address); // TODO
	return true;
}

unsigned int hash_module::start_address() const {
	return HASH_CMD_ADDR;
}

unsigned int hash_module::end_address() const {
	return HASH_RESULT_LAST_ADDR;
}

void hash_module::sha1Next() {
	SHA1ProcessMessageBlock(sha1Intermediate, data);
	sha1Size += 64;
}

void hash_module::sha1Last() {
	auto blockIndex = lastBlockSize;
	sha1Size += lastBlockSize;

	if (lastBlockSize >= (64 - 8)) {
		data[blockIndex++] = 0x80;

		while (blockIndex < 64) {
			data[blockIndex++] = 0;
		}

		SHA1ProcessMessageBlock(sha1Intermediate, data);

		blockIndex = 0;

	} else {
		data[blockIndex++] = 0x80;
	}

	while (blockIndex < (64 - 8)) {
		data[blockIndex++] = 0;
	}

	/*
	 * Store the message length as the last 8 octets
	 */
	sha1Size *= 8;
	data[56] = uint8_t(sha1Size >> 56);
	data[57] = uint8_t(sha1Size >> 48);
	data[58] = uint8_t(sha1Size >> 40);
	data[59] = uint8_t(sha1Size >> 32);
	data[60] = uint8_t(sha1Size >> 24);
	data[61] = uint8_t(sha1Size >> 16);
	data[62] = uint8_t(sha1Size >> 8);
	data[63] = uint8_t(sha1Size);

	SHA1ProcessMessageBlock(sha1Intermediate, data);
}

void hash_module::sha1Reset() {
	sha1Intermediate[0] = 0x67452301;
	sha1Intermediate[1] = 0xEFCDAB89;
	sha1Intermediate[2] = 0x98BADCFE;
	sha1Intermediate[3] = 0x10325476;
	sha1Intermediate[4] = 0xC3D2E1F0;

	sha1Size = 0;
}

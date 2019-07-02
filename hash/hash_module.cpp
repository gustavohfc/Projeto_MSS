#include "pch.h"
#include "hash_module.h"
#include "hash_constants.h"

void hash_module::wait_loop() {
	if (wait_count > 0) {
		wait_count--;
	}
}

bool hash_module::direct_read(int* data, unsigned address) {
	return false;
}

bool hash_module::direct_write(int* data, unsigned address) {
	return false;
}

simple_bus_status hash_module::read(int* data, unsigned address) {
	if (address >= HASH_RESULT_START_ADDR && address <= HASH_RESULT_LAST_ADDR) {
		if (wait_count != 0) {
			return SIMPLE_BUS_WAIT;
		}

		*data = result[(address - HASH_RESULT_START_ADDR) / 4];
		return SIMPLE_BUS_OK;
	}

	sb_fprintf(stdout, "%s %s : Invalid read address (%u) \n", sc_time_stamp().to_string().c_str(), name(), address);
	return SIMPLE_BUS_ERROR;
}

simple_bus_status hash_module::write(int* data, unsigned address) {
	if (address >= HASH_DATA_START_ADDR && address <= HASH_DATA_LAST_ADDR) {

		this->data[(address - HASH_DATA_START_ADDR) / 4] = *data;

	} else if (address == HASH_CMD_ADDR) {

		switch (*data) {
			case Sha1Next:
				break;

			case Sha1Last:
				break;

			case Sha1Reset:
				break;

			default:
				sb_fprintf(stdout, "%s %s : Invalid CMD address (%d) \n", sc_time_stamp().to_string().c_str(), name(), *data);
				return SIMPLE_BUS_ERROR;
		}
	}

	sb_fprintf(stdout, "%s %s : Invalid write address (%u) \n", sc_time_stamp().to_string().c_str(), name(), address);
	return SIMPLE_BUS_ERROR;
}

unsigned int hash_module::start_address() const {
	return HASH_CMD_ADDR;
}

unsigned int hash_module::end_address() const {
	return HASH_RESULT_LAST_ADDR;
}

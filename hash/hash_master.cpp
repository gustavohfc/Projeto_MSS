#include "pch.h"
#include "hash_master.h"
#include "hash/hash_constants.h"

void hash_master::main_action() {
	wait();
	int data;
	uint32_t result[5];

	sb_fprintf(stdout, "%s %s : Writing \"abcd\" to SHA-1\n", sc_time_stamp().to_string().c_str(), name());
	data = 0x61626364;
	bus_port->write(m_unique_priority, &data, HASH_DATA_START_ADDR, m_lock);

	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}

	sb_fprintf(stdout, "%s %s : Writing \"efgh\" to SHA-1\n", sc_time_stamp().to_string().c_str(), name());
	data = 0x65666768;
	bus_port->write(m_unique_priority, &data, HASH_DATA_START_ADDR + 4, m_lock);

	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}

	sb_fprintf(stdout, "%s %s : Writing the last block size to SHA-1\n", sc_time_stamp().to_string().c_str(), name());
	data = 8;
	bus_port->write(m_unique_priority, &data, HASH_LAST_BLOCK_SIZE, m_lock);

	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}

	sb_fprintf(stdout, "%s %s : Starting the SHA-1 last block calculation\n", sc_time_stamp().to_string().c_str(), name());
	data = Sha1Last;
	bus_port->write(m_unique_priority, &data, HASH_CMD_ADDR, m_lock);

	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}

	sb_fprintf(stdout, "%s %s : Trying to read the result\n", sc_time_stamp().to_string().c_str(), name());

	bus_port->read(m_unique_priority, &data, HASH_RESULT_START_ADDR, m_lock);

	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : The result isn't ready yet\n", sc_time_stamp().to_string().c_str(), name());
		wait();
	}

	if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_OK) {
		result[0] = data;
	} else if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : ERROR cannot write OP\n", sc_time_stamp().to_string().c_str(), name());
	}

	bus_port->read(m_unique_priority, &data, HASH_RESULT_START_ADDR + 4, m_lock);
	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}
	if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_OK) {
		result[1] = data;
	} else if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : ERROR cannot write OP\n", sc_time_stamp().to_string().c_str(), name());
	}

	bus_port->read(m_unique_priority, &data, HASH_RESULT_START_ADDR + 8, m_lock);
	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}
	if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_OK) {
		result[2] = data;
	} else if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : ERROR cannot write OP\n", sc_time_stamp().to_string().c_str(), name());
	}

	bus_port->read(m_unique_priority, &data, HASH_RESULT_START_ADDR + 16, m_lock);
	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}
	if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_OK) {
		result[3] = data;
	} else if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : ERROR cannot write OP\n", sc_time_stamp().to_string().c_str(), name());
	}

	bus_port->read(m_unique_priority, &data, HASH_RESULT_START_ADDR + 20, m_lock);
	while (bus_port->get_status(m_unique_priority) != SIMPLE_BUS_OK && bus_port->get_status(m_unique_priority) != SIMPLE_BUS_ERROR) {
		wait();
	}
	if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_OK) {
		result[4] = data;
	} else if (bus_port->get_status(m_unique_priority) == SIMPLE_BUS_ERROR) {
		sb_fprintf(stdout, "%s %s : ERROR cannot write OP\n", sc_time_stamp().to_string().c_str(), name());
	}

	sb_fprintf(stdout, "%s %s : The SHA-1 of the string \"abcdefgh\" is %8x%8x%8x%8x\n", sc_time_stamp().to_string().c_str(), name(), result[0], result[1], result[2], result[3]);
}

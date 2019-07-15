#pragma once
#include "simple_bus_slave_if.h"

class hash_module : public simple_bus_slave_if,
                    sc_module {
public:
	sc_in_clk clock;

	SC_HAS_PROCESS(hash_module);

	hash_module(sc_module_name name, unsigned int nr_wait_states)
	    : sc_module(name)
	    , nr_wait_states(nr_wait_states)
	    , wait_count(0) {

		// process declaration
		SC_METHOD(wait_loop);
		dont_initialize();
		sensitive << clock.pos();
	}

	// direct Slave Interface
	bool direct_read(int* data, unsigned int address) override;
	bool direct_write(int* data, unsigned int address) override;

	// Slave Interface
	simple_bus_status read(int* data, unsigned int address) override;
	simple_bus_status write(int* data, unsigned int address) override;

	unsigned int start_address() const override;
	unsigned int end_address() const override;

private:
	void wait_loop();

	void sha1Next();
	void sha1Last();
	void sha1Reset();

	unsigned int nr_wait_states, wait_count;

	uint8_t data[64];
	uint32_t result[16];
	uint32_t lastBlockSize;

	uint32_t sha1Intermediate[5] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };
	uint64_t sha1Size = 0;
};

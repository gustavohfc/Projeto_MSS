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

	unsigned int nr_wait_states, wait_count;

	uint32_t data[32];
	uint32_t result[16];
};

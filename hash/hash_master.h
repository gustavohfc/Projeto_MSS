#pragma once
#include "simple_bus_non_blocking_if.h"

SC_MODULE(hash_master) {
	sc_in_clk clock;
	sc_port<simple_bus_non_blocking_if> bus_port;

	SC_HAS_PROCESS(hash_master);

	// constructor
	hash_master(sc_module_name _name, unsigned int unique_priority, bool lock, int timeout)
	    : sc_module(_name)
	    , m_unique_priority(unique_priority)
	    , m_lock(lock)
	    , m_timeout(timeout) {

		SC_THREAD(main_action);
		sensitive << clock.pos();
	}

	// process
	void main_action();

private:
	unsigned int m_unique_priority;
	bool m_lock;
	int m_timeout;

};

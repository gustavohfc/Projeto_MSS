#include "pch.h"
#include "simple_bus_test.h"

int sc_main(int argc, char* argv[]) {
	simple_bus_test top("top");

	sc_start(10000, SC_NS);

	return 0;
}

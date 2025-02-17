/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) under one or
  more contributor license agreements.  See the NOTICE file distributed
  with this work for additional information regarding copyright ownership.
  Accellera licenses this file to you under the Apache License, Version 2.0
  (the "License"); you may not use this file except in compliance with the
  License.  You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
  implied.  See the License for the specific language governing
  permissions and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

   simple_bus_test.h : The test bench.

   Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

  *****************************************************************************/

/*****************************************************************************

	MODIFICATION LOG - modifiers, enter your name, affiliation, date and
	changes you are making here.

		Name, Affiliation, Date:
	Description of Modification:

   *****************************************************************************/

#pragma once

#include "simple_bus_slow_mem.h"
#include "simple_bus.h"
#include "simple_bus_fast_mem.h"
#include "simple_bus_arbiter.h"
#include "hash/hash_module.h"
#include "hash/hash_master.h"

SC_MODULE(simple_bus_test) {
	// channels
	sc_clock C1;

	// module instances
	simple_bus_slow_mem* mem_slow;
	simple_bus* bus;
	simple_bus_fast_mem* mem_fast;
	simple_bus_arbiter* arbiter;
	hash_module* hasher;
	hash_master* master;

	// constructor
	SC_CTOR(simple_bus_test)
	    : C1("C1") {
		// create instances
		mem_fast = new simple_bus_fast_mem("mem_fast", 0x00, 0x7f);
		mem_slow = new simple_bus_slow_mem("mem_slow", 0x80, 0xff, 1);
		bus = new simple_bus("bus");
		arbiter = new simple_bus_arbiter("arbiter");

		hasher = new hash_module("hasher", 3);
		master = new hash_master("master", 1, false, 20);

		// connect instances
		bus->clock(C1);
		mem_slow->clock(C1);
		hasher->clock(C1);
		master->clock(C1);

		master->bus_port(*bus);

		bus->arbiter_port(*arbiter);
		bus->slave_port(*mem_slow);
		bus->slave_port(*mem_fast);
		bus->slave_port(*hasher);
	}

	// destructor
	~simple_bus_test() {
		if (mem_slow) {
			delete mem_slow;
			mem_slow = nullptr;
		}
		if (bus) {
			delete bus;
			bus = nullptr;
		}
		if (mem_fast) {
			delete mem_fast;
			mem_fast = nullptr;
		}
		if (arbiter) {
			delete arbiter;
			arbiter = nullptr;
		}
		if (hasher) {
			delete hasher;
			hasher = nullptr;
		}
		if (master) {
			delete master;
			master = nullptr;
		}
	}

}; // end class simple_bus_test

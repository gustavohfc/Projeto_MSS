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

   simple_bus_direct_if.h : The direct BUS/Slave interface.

   Original Author: Ric Hilderink, Synopsys, Inc., 2001-10-11

  *****************************************************************************/

/*****************************************************************************

	MODIFICATION LOG - modifiers, enter your name, affiliation, date and
	changes you are making here.

		Name, Affiliation, Date:
	Description of Modification:

   *****************************************************************************/

#pragma once

class simple_bus_direct_if
    : public virtual sc_interface {
public:
	// direct BUS/Slave interface
	virtual bool direct_read(int* data, unsigned int address) = 0;
	virtual bool direct_write(int* data, unsigned int address) = 0;

}; // end class simple_bus_direct_if

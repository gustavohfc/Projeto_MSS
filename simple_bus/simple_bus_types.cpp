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

   simple_bus_types.h : The common types.

   Original Author: Holger Keding, Synopsys, Inc., 2002-01-28

  *****************************************************************************/

/*****************************************************************************

	MODIFICATION LOG - modifiers, enter your name, affiliation, date and
	changes you are making here.

		Name, Affiliation, Date:
	Description of Modification:

   *****************************************************************************/

#include "pch.h"

// only needed for more readable debug output
char simple_bus_status_str[4][20] = { "SIMPLE_BUS_OK", "SIMPLE_BUS_REQUEST", "SIMPLE_BUS_WAIT", "SIMPLE_BUS_ERROR" };

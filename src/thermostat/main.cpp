/*
thermostat - wall thermostat control example GUI project

Copyright (C) 2025 Gagistech Oy <gagistechoy@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* ================ LICENSE END ================ */

#include <ruisapp/application.hpp>

#include "application.hpp"

namespace thermostat {

const ruisapp::application_factory app_fac([](auto executbale, auto args) {
	return create_application(executbale, args);
});

} // namespace thermostat

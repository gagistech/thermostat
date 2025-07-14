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

#include "application.hpp"

#include <iomanip>

#include <clargs/parser.hpp>
#include <papki/fs_file.hpp>
#include <ruis/widget/group/overlay.hpp>
#include <utki/debug.hpp>

#include "gui.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

using namespace thermostat;

namespace {
constexpr auto screen_dim = 1080;
} // namespace

application::application(bool window, //
	std::string_view res_path) :
	ruisapp::application( //
		"thermostat"s,
		{
			.dims = {screen_dim, screen_dim}
		}
	),
	res_path(papki::as_dir(res_path))
{
	this->set_fullscreen(!window);

	this->gui.init_standard_widgets(*this->get_res_file());

	// this->gui.context.get().loader.mount_res_pack(*this->get_res_file(this->res_path));

	auto c = make_root_widgets(this->gui.context);

	this->gui.set_root(c);
}

std::unique_ptr<application> thermostat::make_application(
	std::string_view executable, //
	utki::span<std::string_view> args
)
{
	bool window = false;

	std::string res_path = []() {
		papki::fs_file local_share("/usr/local/share/thermostat/"sv);

		if (local_share.exists()) {
			return local_share.path();
		}

		return "/usr/share/thermostat/"s;
	}();

	clargs::parser p;

	p.add("window", "run in window mode", [&]() {
		window = true;
	});

	p.add("res-path", "resources path, default = /usr/share/thermostat/", [&](std::string_view v) {
		res_path = v;
	});

	p.parse(args);

	return std::make_unique<application>(window, res_path);
}

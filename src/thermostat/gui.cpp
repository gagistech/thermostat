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

#include "gui.hpp"

#include <ruis/widget/button/push_button.hpp>
#include <ruis/widget/group/overlay.hpp>
#include <ruis/widget/label/gap.hpp>
#include <ruis/widget/label/image.hpp>
#include <ruis/widget/label/margins.hpp>
#include <ruis/widget/label/rectangle.hpp>
#include <ruis/widget/label/text.hpp>

#include "style.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

using namespace ruis::length_literals;

using namespace thermostat;

namespace {
std::vector<utki::shared_ref<ruis::widget>> make_buttons(utki::shared_ref<ruis::context> c)
{
	constexpr const auto button_icon_padding = 5_pp;

	auto make_button = [&](std::string_view icon_res_id, std::string id) {
		// clang-format off
		return m::push_button(c,
			{
				.layout_params = {
					.dims = {ruis::dim::min, ruis::dim::fill}
				},
				.widget_params = {
					.id = std::move(id)
				}
			},
			{
				m::margins(c,
                    {
                        .layout_params = {
                            .dims = {ruis::dim::min, ruis::dim::fill}
                        },
                        .container_params = {
                            .layout = ruis::layout::pile
                        },
                        .frame_params = {
                            .borders = {button_icon_padding, button_icon_padding, button_icon_padding, button_icon_padding}
                        }
                    },
                    {
						m::image(c,
							{
								.layout_params = {
									.dims = {ruis::dim::min, ruis::dim::fill}
								},
								.image_params = {
									.img = c.get().loader.load<ruis::res::image>(icon_res_id),
									.keep_aspect_ratio = true
								}
							}
						)
					}
                )
			}
		);
		// clang-format on
	};

	// clang-format off
	return {
		make_button("img_home"sv, "home_button"),
		make_button("img_cog"sv, "settings_button"),
		m::gap(c,
			{
				.layout_params = {
					.weight = 1
				}
			}
		),
		make_button("img_questionmark"sv, "about_button"),
		make_button("img_exit"sv, "exit_button"),
	};
	// clang-format on
}
} // namespace

namespace {
utki::shared_ref<ruis::rectangle> make_separator(utki::shared_ref<ruis::context> c, bool vertical = false)
{
	// clang-format off
	return m::rectangle(
		std::move(c),
		{
			.layout_params = {
				.dims = {
					vertical ? ruis::dimension(1_pp) : ruis::dimension(ruis::dim::fill),
					vertical ? ruis::dimension(ruis::dim::fill) : ruis::dimension(1_pp)
				}
			},
			.color_params = {
				.color = style::color_border
			}
		}
	);
	// clang-format on
}

auto make_horizontal_separator(utki::shared_ref<ruis::context> c)
{
	return make_separator(c);
}

auto make_vertical_separator(utki::shared_ref<ruis::context> c)
{
	return make_separator(c, true);
}
} // namespace

namespace {
utki::shared_ref<ruis::widget> make_root_widget_structure(utki::shared_ref<ruis::context> c)
{
	constexpr auto alarms_area_height = 70_pp;
	constexpr auto buttons_area_height = 50_pp;
	constexpr auto clock_area_width = 100_pp;

	// clang-format off
	return m::container(c,
		{
			.layout_params = {
				.dims = {ruis::dim::fill, ruis::dim::fill}
			},
			.container_params = {
				.layout = ruis::layout::column
			}
		},
		{
			m::row(c,
				{
					.layout_params = {
						.dims = {ruis::dim::fill, alarms_area_height}
					}
				},
				{
					m::row(c,
						{
							.layout_params = {
								.dims = {ruis::dim::fill, ruis::dim::fill},
								.weight = 1
							},
							.widget_params = {
								.id = "notification_area"s,
							}
						}
					),
					make_vertical_separator(c),
					m::gap(c,
						{
							.layout_params = {
								.dims = {style::clock_padding, 0_pp}
							}
						}
					),
					m::pile(c,
						{
							.layout_params = {
								.dims = {clock_area_width, ruis::dim::min},
								.align = {ruis::align::center, ruis::align::center}

							}
						},
						{
							m::text(c,
								{
									.widget_params = {
										.id = "clock_text"s
									},
									.color_params = {
										.color = style::color_info_text
									},
									.text_params = {
										.font_size = style::font_size_label
									}
								}
							)
						}
					),
					m::gap(c,
						{
							.layout_params = {
								.dims = {style::clock_padding, 0_pp}
							}
						}
					)
				}
			),
			make_horizontal_separator(c),
			m::pile(c,
				{
					.layout_params = {
						.dims = {ruis::dim::fill, ruis::dim::fill},
						.weight = 1
					}
				},
				{
					m::column(c,
						{
							.layout_params = {
								.dims = {ruis::dim::fill, ruis::dim::fill}
							},
							.widget_params = {
								.id = "pw_container"s
							}
						}
					),
					m::row(c,
						{
							.layout_params = {
								.dims = {ruis::dim::fill, ruis::dim::fill}
							}
						},
						{
							m::pile(c,
								{
									.layout_params = {
										.dims = {ruis::dim::fill, ruis::dim::fill},
										.weight = 3
									},
									.widget_params = {
										.id = "menu_area"s
									}
								}
							),
							m::gap(c,
								{
									.layout_params = {
										.weight = 1
									}
								}
							)
						}
					)
				}
			),
			make_horizontal_separator(c),
			m::row(c,
				{
					.layout_params = {
						.dims = {ruis::dim::fill, buttons_area_height}
					},
					.widget_params = {
						.id = "button_area"s
					}
				},
				make_buttons(c)
			)
		}
	);
	// clang-format on
}
} // namespace

utki::shared_ref<ruis::widget> thermostat::make_root_widgets(utki::shared_ref<ruis::context> c)
{
	// clang-format off
	return m::overlay(c,
		{},
		{
			make_root_widget_structure(c)
		}
	);
	// clang-format on
}

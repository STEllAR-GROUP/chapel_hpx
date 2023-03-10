//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <hpx/modules/program_options.hpp>

namespace hello6_taskpar_dist {

    hpx::program_options::options_description get_config_variables();

    void init();

    void main();
}    // namespace hello6_taskpar_dist

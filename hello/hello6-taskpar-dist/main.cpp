//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>

#include "hello6-taskpar-dist.hpp"

int hpx_main(int argc, char* argv[])
{
    hello6_taskpar_dist::main();
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    hpx::program_options::options_description desc_commandline;
    desc_commandline.add(hello6_taskpar_dist::get_config_variables());

    hpx::init_params init_args;
    init_args.desc_cmdline = desc_commandline;

    return hpx::init(argc, argv, init_args);
}

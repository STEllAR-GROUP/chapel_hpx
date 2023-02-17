//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/iostream.hpp>
#include <hpx/modules/format.hpp>

#include "hello.hpp"

namespace hello {

    void init()
    {
        // Simple hello world
        hpx::util::format_to(hpx::cout,
            "Hello world!\n");    // print 'Hello, world!' to the console
    }

    void main()
    {
        init();
    }
}    // namespace hello

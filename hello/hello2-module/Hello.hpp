//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <hpx/modules/program_options.hpp>

namespace Hello {

    hpx::program_options::options_description get_config_variables();

    // Any top-level code in a module is executed as part of the module's
    // initialization when the program begins executing. Thus, in the previous
    // one-line :ref:`hello.chpl <primers-hello>`, the presence of a `writeln()`
    // at the file scope formed the implicit `hello` module's initialization and
    // would be executed at program startup. Since there was no explicit
    // `main()` function or any other top-level code, that's all that the
    // program would do.
    void init();

    //
    // In this program, we define an entry point for the program by defining a
    // procedure named `main()`. This will be invoked after this module and all
    // the modules it uses are initialized.
    //
    void main();
}    // namespace Hello

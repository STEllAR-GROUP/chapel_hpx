//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/iostream.hpp>
#include <hpx/modules/format.hpp>
#include <hpx/modules/program_options.hpp>

#include <string>

#include "Hello.hpp"

//
// The following statement declares a module named 'Hello'. If a source file
// contains no module declarations, the filename minus its ``.chpl`` extension
// serves as the module name for the code it contains. Thus, 'hello' would be
// the automatic module name for the previous :ref:`hello.chpl <primers-hello>`
// example.
//
namespace Hello {

    //
    // This next statement declares a `configuration constant` named `message`.
    // The type is inferred to be a string since the initializing expression is
    // a string literal.Users may override the default values of configuration
    // constants and variables on the executable command-line. For example, we
    // could change the default message for a given run using the command line:
    // ``./hello --message="hiya!"``.
    //
    std::string message = "Hello, world!";

    hpx::program_options::options_description get_config_variables()
    {
        hpx::program_options::options_description options;

        // clang-format off
        options.add_options()
            ("message",
                hpx::program_options::value<std::string>(&message),
                R"(config const message = "Hello world!")")
        ;
        // clang-format on

        return options;
    }

    // Any top-level code in a module is executed as part of the module's
    // initialization when the program begins executing. Thus, in the previous
    // one-line :ref:`hello.chpl <primers-hello>`, the presence of a `writeln()`
    // at the file scope formed the implicit `hello` module's initialization and
    // would be executed at program startup. Since there was no explicit
    // `main()` function or any other top-level code, that's all that the
    // program would do.
    void init() {}

    //
    // In this program, we define an entry point for the program by defining a
    // procedure named `main()`. This will be invoked after this module and all
    // the modules it uses are initialized.
    //
    void main()
    {
        init();

        hpx::util::format_to(hpx::cout, R"({}{})", message, "\n");
    }
}    // namespace Hello

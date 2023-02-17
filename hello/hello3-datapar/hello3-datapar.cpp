//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/algorithm.hpp>
#include <hpx/iostream.hpp>
#include <hpx/modules/format.hpp>
#include <hpx/modules/program_options.hpp>

#include "hello3-datapar.hpp"

// Data-parallel hello world

/* This program uses Chapel's data parallel features to create a
   parallel hello world program that utilizes multiple cores on a
   single `locale` (compute node).
 */

namespace hello3_datapar {

    //
    // The following `configuration constant` indicates the number of
    // messages to print out.  The default can be overridden on the
    // command-line (e.g., ``./hello --numMessages=1000000``).
    //
    int numMessages = 100;

    hpx::program_options::options_description get_config_variables()
    {
        hpx::program_options::options_description options;

        // clang-format off
        options.add_options()
            ("numMessages",
                hpx::program_options::value<int>(&numMessages),
                R"(config const numMessages = 100")")
        ;
        // clang-format on

        return options;
    }

    //
    // Next, we use a data-parallel `forall-loop` to iterate over a `range`
    // representing the number of messages to print. By default, forall-loops
    // will typically be executed cooperatively by a number of tasks
    // proportional to the hardware parallelism on which the loop is running.
    // Ranges like ``1..numMessages`` are always local to the current task's
    // locale, so this forall-loop will execute using the number of local
    // processing units or cores.
    //
    // Because the messages are printed within a parallel loop, they may
    // be displayed in any order.  The `writeln()` procedure protects
    // against finer-grained interleaving of the messages themselves.
    //

    struct forall_1
    {
        void operator()(int msg) const
        {
            hpx::util::format_to(hpx::cout,
                "Hello, world! (from iteration {} of {})\n", msg, numMessages);
        }
    };

    void init()
    {
        hpx::experimental::for_loop(
            hpx::execution::par, 0, numMessages, forall_1());
    }

    //
    // For further examples of using data parallelism, refer to the data
    // parallel :ref:`primer examples <primers>`.
    //
    void main()
    {
        init();
    }
}    // namespace hello3_datapar

//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/iostream.hpp>
#include <hpx/modules/algorithms.hpp>
#include <hpx/modules/distribution_policies.hpp>
#include <hpx/modules/executors_distributed.hpp>
#include <hpx/modules/format.hpp>
#include <hpx/modules/program_options.hpp>
#include <hpx/modules/runtime_distributed.hpp>

#include "hello6-taskpar-dist.hpp"

// Distributed memory task parallel hello world

/* This program shows how to use Chapel's task parallelism and
   locality features to create a concurrent "Hello, world" program
   that spans distributed memory `locales` (compute nodes) as well as
   (optionally) the processing units (cores) within each locale.  The
   number of locales on which to run is specified on the executable's
   command line using the `-nl` or `--numLocales` flag (e.g.,
   ``./hello -nl 64``).
 */

namespace hello6_taskpar_dist {

    //
    // The following `config const` specifies whether or not the locale name
    // should be printed (for ease-of-testing purposes); the default can be
    // overridden on the execution command line (e.g.,
    // ``--printLocaleName=false``).
    //
    bool printLocaleName = true;

    //
    // This one specifies the number of tasks to use per locale:
    //
    int tasksPerLocale = 1;

    hpx::program_options::options_description get_config_variables()
    {
        hpx::program_options::options_description options;

        // clang-format off
        options.add_options()
            ("printLocaleName",
                hpx::program_options::value<bool>(&printLocaleName),
                R"(config const printLocaleName = true")")
            ("tasksPerLocale",
                hpx::program_options::value<int>(&tasksPerLocale),
                R"(config const tasksPerLocale = 1")")
        ;
        // clang-format on

        return options;
    }

    //
    // Use a `coforall-loop` to create a distinct task per locale on which
    // the program is executing.  Here, we're iterating over the built-in
    // `Locales` array which stores an array of locale values
    // corresponding 1:1 with the system's compute nodes on which the
    // program is executing.  Thus, each iteration corresponds to one of
    // the locales, represented by the loop index variable `loc`.
    //
    struct coforall_2
    {
        void operator()(int tid) const
        {
            //
            // Start building up the message to print using a string variable,
            // `message`.
            //
            std::string message = "Hello, world! (from ";

            //
            // If we're running more than one task per locale, specialize the
            // message based on the task ID.
            //
            if (tasksPerLocale > 1)
            {
                message += "task " + std::to_string(tid + 1) + " of " +
                    std::to_string(tasksPerLocale) + " on ";
            }

            //
            // Specialize the message based on the locale on which this task is
            // running:
            //
            // - `here` refers to the locale on which this task is running (same
            //    as `loc`)
            // - `.id` queries its unique ID in 0..`numLocales`-1
            // - .name` queries its name (similar to UNIX ``hostname``)
            // - `numLocales` refers to the number of locales (as specified by
            //   -nl)
            //
            message += "locale " + std::to_string(hpx::get_locality_id() + 1) +
                " of " +
                std::to_string(hpx::get_num_localities(hpx::launch::sync));

            if (printLocaleName)
            {
                message += " named " + hpx::get_locality_name();
            }

            //
            // Terminate the message
            //
            message += ")";

            //
            // Print out the message.  Since each message is being printed by a
            // distinct task, they may appear in an arbitrary order.
            //
            hpx::util::format_to(hpx::cout, "{}\n", message);
        }
    };

    struct coforall_1
    {
        void operator()(int) const
        {
            //
            // Now use a second coforall-loop to create a number of tasks
            // corresponding to the `tasksPerLocale` configuration constant.
            // Since this loop body doesn't contain any on-clauses, all tasks
            // will remain local to the current locale.
            //
            auto chunk_size =
                hpx::execution::experimental::static_chunk_size(1);

            hpx::experimental::for_loop(hpx::execution::par.with(chunk_size), 0,
                tasksPerLocale, coforall_2());
        }
    };

    void init()
    {
        //
        // Migrate each task to its corresponding locale, `loc`. This is done
        // using an `'on'-clause`, which moves execution of the current task to
        // the locale corresponding to the expression following it.
        //
        auto exec = hpx::parallel::execution::distribution_policy_executor(
            hpx::components::default_layout);
        auto chunk_size = hpx::execution::experimental::static_chunk_size(1);

        hpx::experimental::for_loop(
            hpx::execution::par.on(exec).with(chunk_size), 0,
            hpx::get_num_localities(hpx::launch::sync), coforall_1());
    }

    void main()
    {
        init();
    }
}    // namespace hello6_taskpar_dist

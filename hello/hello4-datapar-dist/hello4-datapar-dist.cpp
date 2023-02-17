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

#include "hello4-datapar-dist.hpp"

// Distributed-memory data-parallel hello, world

/* This program uses Chapel's distributed data parallel features to
   create a parallel hello world program that utilizes multiple cores
   on multiple `locales` (compute nodes). The number of locales on
   which to run is specified on the executable command line using
   the `-nl` or `--numLocales` flag (e.g., ``./hello -nl 64``). This
   test is very similar to :ref:`hello-datapar.chpl
   <primers-hello3-datapar>`, so we won't repeat the explanation of
   concepts introduced there.
 */

namespace hello4_datapar_dist {

    //
    // Declare the number of messages to print:
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

    struct forall_1
    {
        void operator()(int msg) const
        {
            hpx::util::format_to(hpx::cout,
                "Hello, world! (from iteration {} of {} owned by locale {} of "
                "{})\n",
                msg, numMessages, hpx::get_locality_id() + 1,
                hpx::get_num_localities(hpx::launch::sync));
        }
    };

    void init()
    {
        auto exec = hpx::parallel::execution::distribution_policy_executor(
            hpx::components::default_layout);

        hpx::experimental::for_loop(
            hpx::execution::par.on(exec), 1, numMessages + 1, forall_1());
    }

    void main()
    {
        init();
    }
}    // namespace hello4_datapar_dist

//  Copyright (c) 2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/iostream.hpp>
#include <hpx/modules/algorithms.hpp>
#include <hpx/modules/execution.hpp>
#include <hpx/modules/format.hpp>

#include "hello5-taskpar.hpp"

// Task-parallel hello world

/* This program uses Chapel's `task parallel` features to express an
   explicitly concurrent hello world program that utilizes multiple
   cores on a single `locale` (compute node).
 */

namespace hello5_taskpar {

    //
    // First, we specify the number of tasks to create via a `config const`. By
    // default, set it to the runtime's estimation of maximum parallelism that
    // the current locale ('`here`') is capable of executing (``.maxTaskPar``).
    //
    int numTasks = 100;

    hpx::program_options::options_description get_config_variables()
    {
        hpx::program_options::options_description options;

        // clang-format off
        options.add_options()
            ("numTasks",
                hpx::program_options::value<int>(&numTasks),
                R"(config const numTasks = 100")")
        ;
        // clang-format on

        return options;
    }

    //
    // Next, we create the specified number tasks using a `coforall-loop`. This
    // is a parallel loop form that will create a distinct task per iteration.
    //
    // This coforall-loop is iterating over the `range` ``0..#numTasks`` which
    // represents the first `numTasks` integers starting at 0 (equivalent to
    // ``0..numTasks-1``). The result will be `numTasks` iterations, each of
    // which will be executed as a distinct parallel task.
    //
    // Each iteration prints out a message that is unique based on its value of
    // `tid`. Due to the task parallelism, the messages may be printed in any
    // order. However, the `writeln()` procedure will prevent finer-grained
    // interleaving of the messages themselves.
    //
    struct coforall_1
    {
        void operator()(int tid) const
        {
            hpx::util::format_to(hpx::cout,
                "Hello, world! (from task {} of {})\n", tid + 1, numTasks);
        }
    };

    void init()
    {
        auto chunk_size = hpx::execution::experimental::static_chunk_size(1);

        hpx::experimental::for_loop(
            hpx::execution::par.with(chunk_size), 0, numTasks, coforall_1());
    }

    void main()
    {
        init();
    }

    //
    // For further examples of using task parallelism, refer to
    // :ref:`examples/primers/taskParallel.chpl <primers-taskParallel>`.
    //
}    // namespace hello5_taskpar

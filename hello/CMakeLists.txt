# Copyright (c) 2023 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(examples hello hello2-module hello3-datapar hello4-datapar-dist
             hello5-taskpar hello6-taskpar-dist
)

foreach(example ${examples})
  add_subdirectory(${example})
endforeach()

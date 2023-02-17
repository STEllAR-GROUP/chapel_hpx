# Copyright (c) 2023 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

set(example_program hello2-module)

set(sources Hello.cpp main.cpp)
set(headers Hello.hpp)

source_group("Source Files" FILES ${sources})
source_group("Header Files" FILES ${headers})

add_hpx_executable(
  ${example_program} INTERNAL_FLAGS
  SOURCES ${sources} ${headers}
  FOLDER "Hello"
  COMPONENT_DEPENDENCIES iostreams
)

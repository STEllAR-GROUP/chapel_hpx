# Copyright (c) 2023 Hartmut Kaiser
#
# SPDX-License-Identifier: BSL-1.0
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.19)

project(chapel_hpx CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(HPX)

add_subdirectory(hello)

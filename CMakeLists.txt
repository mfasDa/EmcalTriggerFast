# Fast simulation tool for the trigger response of the ALICE EMCAL-DCAL
# Detector system
# Copyright (C) 2015  Markus Fasel, ALICE Collaboration
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

project(EMCALTriggerFast CXX)
cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(CheckCXXCompilerFlag)

# ROOT NEEDED for tests
find_package(ROOT 5.34.30 REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
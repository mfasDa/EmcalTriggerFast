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

cmake_minimum_required(VERSION 2.8.11)

execute_process ( COMMAND root-config --etcdir WORKING_DIRECTORY /tmp OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE )
set( CMAKE_MODULE_PATH "${ROOT_ETCDIR}/cmake" )
find_package(ROOT) # REQUIRED)

if (ROOT_FOUND)
	message (STATUS "ROOT found via root-config --etcdir and etc/FindROOT.cmake : CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
  # Check for ROOT Version for C++11 support
  execute_process(COMMAND root-config --version OUTPUT_VARIABLE ROOT_VERSION ERROR_VARIABLE error OUTPUT_STRIP_TRAILING_WHITESPACE )
  if(error)
    message(FATAL_ERROR "Error retrieving ROOT version : ${error}")
  endif(error)
  string(STRIP "${ROOT_VERSION}" ROOT_VERSION)
  string(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+.*" "\\1" ROOT_VERSION_MAJOR "${ROOT_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" ROOT_VERSION_MINOR "${ROOT_VERSION}")
  string(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+).*" "\\1" ROOT_VERSION_PATCH "${ROOT_VERSION}")
  if(${ROOT_VERSION_MAJOR} GREATER 5)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if(CMAKE_CXX_COMPILER_ID EQUAL Clang)
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID EQUAL Clang)
  endif()
endif (ROOT_FOUND)

if (ROOT-NOTFOUND)
	message (STATUS "ROOT not found - checking with the provided FindROOT.cmake")
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
	message (STATUS "+ROOT CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
	find_package(ROOT REQUIRED)
endif(ROOT-NOTFOUND)

if (ROOT_FOUND)
	include_directories(
	    ${ROOT_INCLUDE_DIR}
	    ${EMCALTriggerFast_SOURCE_DIR}/src
	    ${CMAKE_CURRENT_SOURCE_DIR}
	)
	add_executable(channelmaptester channelmaptester.cxx)
	target_link_libraries(channelmaptester ${ROOT_LIBRARIES} EMCALTriggerFast )
	install(TARGETS channelmaptester RUNTIME DESTINATION bin)
else()
	message(WARNING "no ROOT -> channelmaptester will not be compiled")
endif (ROOT_FOUND)

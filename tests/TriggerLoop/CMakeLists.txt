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

set(EXE_SRCS testETF.cxx)
string(REPLACE ".cxx" "" EXE_NAME "${EXE_SRCS}")

find_package(Boost REQUIRED random math_c99 system)
if (BOOST-NOTFOUND)
	message(SEND_ERROR "Boost or one of the components not found. Will not compile ${EXE_NAME}")
endif (BOOST-NOTFOUND)

include_directories(
    ${Boost_INCLUDE_DIR}
    ${EMCALTriggerFast_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${EXE_NAME} ${EXE_SRCS})
target_link_libraries(${EXE_NAME} ${Boost_LIBRARIES} EMCALTriggerFast )

install(TARGETS ${EXE_NAME}
        RUNTIME DESTINATION bin )

install(FILES ${HDRS} DESTINATION include)


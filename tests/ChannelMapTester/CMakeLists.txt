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

include_directories(
    ${ROOT_INCLUDE_DIR}
    ${EMCALTriggerFast_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)
link_directories(
    ${ROOT_LIBDIR}
)

SET(LIBDEPS EMCALTriggerFast Core EG Geom Gpad Graf Hist MathCore Matrix Physics RIO Tree VMC)

add_executable(channelmaptester channelmaptester.cxx)
target_link_libraries(channelmaptester ${LIBDEPS})

install(TARGETS channelmaptester RUNTIME DESTINATION bin)
# Fume is a client implementation for Liquid War 7.
# Copyright (C)  2015  Christian Mauduit <ufoot@ufoot.org>
#
# This program is free software; you can redistribute it and/or modify
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
#
# Fumes homepage: https://github.com/ufoot/fumes
# Contact author: ufoot@ufoot.org

AM_CXXFLAGS = @FM_CXXFLAGS@
AM_LDFLAGS = @FM_LDFLAGS@

noinst_LTLIBRARIES = libfmsys.la
libfmsys_la_SOURCES = fmlog.cpp

libexec_PROGRAMS = fmsys-log-test
fmsys_log_test_SOURCES = fmlog-test.cpp
fmsys_log_test_LDFLAGS = @cppunit_LIBS@
fmsys_log_test_LDADD = libfmsys.la
TESTS = fmsys-log-test

check-local:
	valgrind ./fmsys-log-test

EXTRA_DIST = fmsys.hpp fmsys-test.hpp

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

noinst_LTLIBRARIES = libfumes_s.la
FM_FILES = 
FM_LIBS = fmbuild/libfmbuild.la
libfumes_s_la_SOURCES = $(FM_FILES)
libfumes_s_la_LIBADD = $(FM_LIBS)

lib_LTLIBRARIES = libfumes.la
libfumes_la_SOURCES = $(FM_FILES)
libfumes_la_LIBADD = $(FM_LIBS)
libfumes_la_LDFLAGS = -release @PACKAGE_VERSION@ @FM_LDFLAGS@
libfumesdir = $(includedir)/@PACKAGE_TARNAME@
libfumes_HEADERS = fumes.hpp

SUBDIRS = fmbuild


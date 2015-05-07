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

AC_INIT([Fumes Client],[0.0.0],[ufoot@ufoot.org],[fumes],[https://github.com/ufoot/fumes])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL

dnl Headers, some are optional
AC_CHECK_HEADERS(stdlib.h)

AC_OUTPUT([Makefile
	src/Makefile.am
])


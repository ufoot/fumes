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

if FM_DOXYGEN
all-local: doxygen.dummy
endif # FM_DOXYGEN

# dependency on doxygen.cfg.in and not doxygen.cfg to avoid too many builds
doxygen.dummy: doxygen.cfg.in
	export FM_DOXYGEN_INPUT=${top_srcdir}/src ; if test -f doxygen.cfg ; then doxygen doxygen.cfg ; fi
	touch $@

clean-local:
	rm -rf html xml latex doxygen.dummy doxygen_sqlite3.db


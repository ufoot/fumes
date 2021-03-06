// Fume is a client implementation for Liquid War 7.
// Copyright (C)  2015  Christian Mauduit <ufoot@ufoot.org>

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// Fumes homepage: https://github.com/ufoot/fumes
// Contact author: ufoot@ufoot.org

#include "fmbuild.hpp"

namespace fmbuild {
// constants set by stamp.sh
constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 1;
constexpr char VERSION_STAMP[] = "24";
}

int fmbuild::get_version_major() { return fmbuild::VERSION_MAJOR; }

int fmbuild::get_version_minor() { return fmbuild::VERSION_MINOR; }

std::string fmbuild::get_version_stamp() {
  std::string s = {fmbuild::VERSION_STAMP};

  return s;
}

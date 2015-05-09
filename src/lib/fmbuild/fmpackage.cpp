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
constexpr char PACKAGE_TARNAME[] = "fumes";
constexpr char PACKAGE_NAME[] = "Fumes Client";
constexpr char PACKAGE_EMAIL[] = "ufoot@ufoot.org";
constexpr char PACKAGE_URL[] = "http://www.ufoot.org/liquidwar/v7/fumes";
}

std::string fmbuild::get_package_tarname() {
  std::string s = {fmbuild::PACKAGE_TARNAME};

  return s;
}

std::string fmbuild::get_package_name() {
  std::string s = {fmbuild::PACKAGE_NAME};

  return s;
}

std::string fmbuild::get_package_email() {
  std::string s = {fmbuild::PACKAGE_EMAIL};

  return s;
}

std::string fmbuild::get_package_url() {
  std::string s = {fmbuild::PACKAGE_URL};

  return s;
}

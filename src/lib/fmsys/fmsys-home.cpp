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

#include "fmsys.hpp"

#include <cstdlib>

namespace fmsys {
constexpr char ENV_HOME[] = "HOME";
}

std::string fmsys::program_home(const std::string& program) {
  char* val_c = getenv(fmsys::ENV_HOME);
  std::string val_cpp =
      std::string((val_c == nullptr) ? "" : std::string(val_c));

  std::string path = fmsys::dir_exists(val_cpp)
                         ? val_cpp + fmsys::PATH_SEP + fmsys::PATH_DOT + program
                         : std::string(PATH_DOT);

  return path;
}

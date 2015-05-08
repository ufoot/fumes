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

#ifndef FMSYS_HPP
#define FMSYS_HPP

#include <string>
#include <ostream>
#include <fstream>

namespace fmsys {
  class log {
    std::string f;
    std::ofstream *os;
  public:
    log(std::string &filename);
    ~log();
    std::ostream & get();
};

  std::ostream & crit();
  std::ostream & error();
  std::ostream & warning();
  std::ostream & notice();
  std::ostream & info();
  std::ostream & debug();
}

#endif // FMSYS_HPP

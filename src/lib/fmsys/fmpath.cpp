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

std::string fmsys::path_join(std::vector<std::string> v) {
  std::string ret;
  bool first = true;

  for (std::string s : v) {
    if (first) {
      ret = s;
      first = false;
    } else {
      ret += fmsys::PATH_SEP + s;
    }
  }

  return ret;
}

std::vector<std::string> fmsys::path_split(std::string s) {
  std::vector<std::string> ret;
  std::string::size_type pos = 0;
  std::string::size_type found = 0;
  auto length = s.length();

  while (found != std::string::npos) {
    pos = found;
    found = s.find_first_of(fmsys::PATH_SEP, found);
    if (found != std::string::npos) {
      if (found > pos) {
        ret.push_back(s.substr(pos, found - pos));
      } else {
        ret.push_back(std::string(""));
      }
      found++;
    }
  }
  if (length > pos) {
    ret.push_back(s.substr(pos, length - pos));
  } else {
    ret.push_back(std::string(""));
  }

  return ret;
}

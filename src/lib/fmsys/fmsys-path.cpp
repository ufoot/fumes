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

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

std::string fmsys::path_join(const std::vector<std::string>& v) {
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

std::vector<std::string> fmsys::path_split(const std::string& s) {
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

bool fmsys::file_exists(const std::string& filename) {
  int ret = false;
  FILE* f = nullptr;

  f = ::fopen(filename.c_str(), "r");
  if (f) {
    ::fclose(f);
    ret = true;
  }

  return ret;
}

bool fmsys::dir_exists(const std::string& dirname) {
  bool ret = false;
  DIR* d = nullptr;

  d = ::opendir(dirname.c_str());
  if (d) {
    ::closedir(d);
    ret = true;
  }

  return ret;
}

bool fmsys::touch(const std::string& filename) {
  FILE* f = nullptr;

  f = ::fopen(filename.c_str(), "a");
  if (f) {
    ::fclose(f);
  } else {
    return false;
  }

  return fmsys::file_exists(filename);
  ;
}

bool fmsys::mkdir(const std::string& dirname) {
  if (fmsys::dir_exists(dirname)) {
    return true;
  }
  if (::mkdir(dirname.c_str(),
              S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP) != 0) {
    return false;
  }

  return fmsys::dir_exists(dirname);
}

bool fmsys::unlink(const std::string& filename) {
  if (::unlink(filename.c_str()) == 0) {
    return true;
  }

  return !fmsys::file_exists(filename);
  ;
}

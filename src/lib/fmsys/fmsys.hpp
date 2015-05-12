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
#include <memory>
#include <vector>

namespace fmsys {
std::string program_home(std::string program);

enum class log_priority { CRIT, ERROR, WARNING, NOTICE, INFO, DEBUG };

class log_backend {
  std::string file_name;
  std::unique_ptr<std::ofstream> file_handler;

 public:
  log_backend(std::string filename);
  std::ostream* get();
};

class log_proxy : public std::ofstream {
  log_backend& proxy_backend;
  log_priority proxy_priority;

 public:
  log_proxy(log_backend& backend, log_priority priority);
  template <typename T>
  std::ostream& operator<<(T val) {
    return (*proxy_backend.get()) << "todo! " << val << "\n";
  }
};

extern log_proxy log_crit;
extern log_proxy log_error;
extern log_proxy log_warning;
extern log_proxy log_notice;
extern log_proxy log_info;
extern log_proxy log_debug;

constexpr char PATH_DOT[] = ".";
constexpr char PATH_SEP[] = "/";

std::string path_join(std::vector<std::string> v);
std::vector<std::string> path_split(std::string s);
}

#endif  // FMSYS_HPP

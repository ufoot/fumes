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

#include "../fmbuild/fmbuild.hpp"

namespace fmsys {
std::string program_home(const std::string& program);

enum class log_priority { CRIT, ERROR, WARNING, NOTICE, INFO, DEBUG };

constexpr char LOG_SEP_MAJOR[] = ": ";
constexpr char LOG_SEP_MINOR[] = " ";
std::string log_time();
std::string log_chomp(const char* str);

std::string log_setup(const std::string& program);
class log_file {
  const std::string file_name;
  std::unique_ptr<std::ofstream> file_handler;

 public:
  log_file(const std::string& filename);
  const std::string file_prefix;
  std::ostream* get_ostream();
};

class log_proxy : public std::ofstream {
  log_file& proxy_file;
  log_priority proxy_priority;

 public:
  log_proxy(log_file& file, log_priority priority);
  template <typename T>
  std::ostream& operator<<(T val) {
    return (*proxy_file.get_ostream()) << proxy_file.file_prefix
                                       << LOG_SEP_MAJOR << log_time()
                                       << LOG_SEP_MINOR << val << "\n";
  }
};

extern log_proxy log_crit;
extern log_proxy log_error;
extern log_proxy log_warning;
extern log_proxy log_notice;
extern log_proxy log_info;
extern log_proxy log_debug;

#define LOG_WARNING                                                        \
  fmsys::log_warning << __FILE__ << ":" << std::to_string(__LINE__) << " " \
                     << __FUNCTION__ << "()" << fmsys::LOG_SEP_MAJOR

constexpr char PATH_DOT[] = ".";
constexpr char PATH_SEP[] = "/";

std::string path_join(const std::vector<std::string>& v);
std::vector<std::string> path_split(const std::string& s);
bool file_exists(const std::string& filename);
bool dir_exists(const std::string& dirname);
bool touch(const std::string& dirname);
bool mkdir(const std::string& dirname);
bool unlink(const std::string& dirname);
}

#endif  // FMSYS_HPP

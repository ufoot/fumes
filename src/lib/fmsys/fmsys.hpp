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
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>

#include "../fmbuild/fmbuild.hpp"

namespace fmsys {
std::string program_home(const std::string& program);

enum class log_priority { CRIT, ERROR, WARNING, NOTICE, INFO, DEBUG };

constexpr char LOG_SEP_MAJOR[] = ": ";
constexpr char LOG_SEP_MINOR[] = " ";
constexpr char LOG_EOL = '\n';
std::string log_time();

std::string log_setup(const std::string& program);
class log_file {
  const std::string file_name;
  std::shared_ptr<std::ofstream> file_handler;

 public:
  log_file(const std::string& filename);
  log_file(const log_file& other);
  const std::string file_prefix;
  std::ostream* get_ostream();
};

class log_proxy : public std::ofstream {
  log_file& proxy_file;
  log_priority proxy_priority;
  const char* proxy_source_file;
  int proxy_source_line;
  std::shared_ptr<std::ostringstream> message;
  void process_output();

 public:
  log_proxy(log_file& file, log_priority priority);
  log_proxy(log_file& file, log_priority priority, const char* source_file,
            int source_line);
  log_proxy(log_proxy&& other);
  template <typename T>
  std::ofstream& operator<<(T val) {
    (*message.get()) << (val);
    process_output();

    return *this;
  }
};

log_proxy log_crit();
log_proxy log_crit(const char* source_file, int source_line);
log_proxy log_error();
log_proxy log_error(const char* source_file, int source_line);
log_proxy log_warning();
log_proxy log_warning(const char* source_file, int source_line);
log_proxy log_notice();
log_proxy log_notice(const char* source_file, int source_line);
log_proxy log_info();
log_proxy log_info(const char* source_file, int source_line);
log_proxy log_debug();
log_proxy log_debug(const char* source_file, int source_line);

#define LOG_CRIT fmsys::log_crit(__FILE__, __LINE__)
#define LOG_ERROR fmsys::log_error(__FILE__, __LINE__)
#define LOG_WARNING fmsys::log_warning(__FILE__, __LINE__)
#define LOG_NOTICE fmsys::log_notice(__FILE__, __LINE__)
#define LOG_INFO fmsys::log_info(__FILE__, __LINE__)
#define LOG_DEBUG fmsys::log_debug(__FILE__, __LINE__)

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

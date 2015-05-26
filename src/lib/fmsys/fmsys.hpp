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

#include <syslog.h>

#include "../fmbuild/fmbuild.hpp"

namespace fmsys {
std::string program_home(const std::string& program);

enum class log_priority : int {
  CRIT = LOG_CRIT,
  ERROR = LOG_ERR,
  WARNING = LOG_WARNING,
  NOTICE = LOG_NOTICE,
  INFO = LOG_INFO,
  DEBUG = LOG_DEBUG
};

constexpr char LOG_SEP_MAJOR[] = ": ";
constexpr char LOG_SEP_MINOR[] = " ";
constexpr char LOG_EOL = '\n';
std::string log_time(bool full);
std::string log_priority_string(log_priority priority);

std::string log_setup(const std::string& program);
class log_file {
  const std::string file_name;
  std::shared_ptr<std::ofstream> file_handler;

 public:
  log_file(const std::string& filename);
  log_file() = delete;
  log_file(const log_file& other) = default;
  log_file(log_file&& other) = default;
  log_file& operator=(const log_file& other) = default;
  log_file& operator=(log_file&& other) = default;
  ~log_file() = default;
  const std::string file_prefix;
  std::ostream& get_ostream();
};

class log_syslog {
 public:
  log_syslog(const std::string& program);
  /// No default constructor.
  log_syslog() = delete;
  /// No copy constructor.
  log_syslog(const log_syslog& other) = delete;
  /// No move constructor.
  log_syslog(log_syslog&& other) = delete;
  /// No copy assignment.
  log_syslog& operator=(const log_syslog& other) = delete;
  /// No move assignment.
  log_syslog& operator=(log_syslog&& other) = delete;
  /// Destructor.
  ~log_syslog();
};

class log_proxy {
  log_file& proxy_file;
  log_priority proxy_priority;
  const char* proxy_source_file;
  int proxy_source_line;
  std::shared_ptr<std::ostringstream> message;
  void process_output();

 public:
  /// Creates a log_proxy object, ready to log, with the given priority.
  log_proxy(log_file& file, log_priority priority);
  /// Creates a log_proxy object, ready to log, with the given priority.
  /// Call in with FILE and LINE standard C macro and
  /// it will report the file:line of the caller.
  log_proxy(log_file& file, log_priority priority, const char* source_file,
            int source_line);
  log_proxy() = delete;
  /// Default copy constructor.
  log_proxy(const log_proxy& other) = default;
  /// Default move constructor.
  log_proxy(log_proxy&& other) = default;
  log_proxy& operator=(const log_proxy& other) = default;
  log_proxy& operator=(log_proxy&& other) = default;
  ~log_proxy() = default;
  /// Main operator used to log stuff. This is probably the only usefull
  /// stuff in the whole object, the idea is to use the object the way
  /// one would use std::cout, just pile up << operators to the right of
  /// it. Do not forget to append a final '\n' (EOL) else content is never
  /// flushed and never logged at all.
  template <typename T>
  log_proxy& operator<<(T val) {
    (*message) << (val);
    process_output();

    return *this;
  }
};

/// Creates a log_proxy object, ready to log in critical mode.
log_proxy log_crit();
/// Creates a log_proxy object, ready to log in critical mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_crit(const char* source_file, int source_line);
/// Creates a log_proxy object, ready to log in error mode.
log_proxy log_error();
/// Creates a log_proxy object, ready to log in error mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_error(const char* source_file, int source_line);
/// Creates a log_proxy object, ready to log in warning mode.
log_proxy log_warning();
/// Creates a log_proxy object, ready to log in warning mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_warning(const char* source_file, int source_line);
/// Creates a log_proxy object, ready to log in notice mode.
log_proxy log_notice();
/// Creates a log_proxy object, ready to log in notice mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_notice(const char* source_file, int source_line);
/// Creates a log_proxy object, ready to log in info mode.
log_proxy log_info();
/// Creates a log_proxy object, ready to log in info mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_info(const char* source_file, int source_line);
/// Creates a log_proxy object, ready to log in debug mode.
log_proxy log_debug();
/// Creates a log_proxy object, ready to log in debug mode.
/// Call in with FILE and LINE standard C macro and
/// it will report the file:line of the caller.
log_proxy log_debug(const char* source_file, int source_line);

#define FMSYS_LOG_CRIT fmsys::log_crit(__FILE__, __LINE__)
#define FMSYS_LOG_ERROR fmsys::log_error(__FILE__, __LINE__)
#define FMSYS_LOG_WARNING fmsys::log_warning(__FILE__, __LINE__)
#define FMSYS_LOG_NOTICE fmsys::log_notice(__FILE__, __LINE__)
#define FMSYS_LOG_INFO fmsys::log_info(__FILE__, __LINE__)
#define FMSYS_LOG_DEBUG fmsys::log_debug(__FILE__, __LINE__)

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

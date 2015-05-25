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

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>

namespace fmsys {
constexpr char LOG_HEADER[] = "DATE;MESSAGE;...\n";
constexpr char LOG_FILENAME[] = "log.txt";
constexpr size_t BUFTIME_SIZE = 100;
constexpr char BUFTIME_FORMAT_FULL[] = "%Y/%m/%d %H:%M:%S.";
constexpr char BUFTIME_FORMAT_LIGHT[] = "%H:%M:%S";
constexpr size_t BUFMICRO_SIZE = 20;
constexpr char BUFMICRO_FORMAT[] = "%06d";
constexpr int BUFMICRO_MODULO = 1000000;
constexpr char LOG_SOURCE_FILE_UNDEF[] = "?.cpp";
constexpr int LOG_SOURCE_LINE_UNDEF = 0;

constexpr char STR_CRIT[] = "CRIT";
constexpr char STR_ERROR[] = "ERROR";
constexpr char STR_WARNING[] = "WARNING";
constexpr char STR_NOTICE[] = "NOTICE";
constexpr char STR_INFO[] = "INFO";
constexpr char STR_DEBUG[] = "DEBUG";
constexpr char STR_UNKNOWN[] = "UNKNOWN";

constexpr log_priority CERR_PRIORITY = log_priority::NOTICE;
constexpr log_priority PROBLEM_PRIORITY = log_priority::WARNING;
constexpr log_priority FILE_PRIORITY = log_priority::DEBUG;
constexpr log_priority SYSLOG_PRIORITY = log_priority::WARNING;
constexpr log_priority FLUSH_PRIORITY = log_priority::NOTICE;

static log_file global_log_file(fmbuild::get_package_tarname());
static log_syslog global_log_syslog(fmbuild::get_package_tarname());
}

std::string fmsys::log_setup(const std::string& program) {
  std::string dir = fmsys::program_home(program);
  std::string file = std::string(LOG_FILENAME);

  if (fmsys::mkdir(dir)) {
    file = dir + PATH_SEP + LOG_FILENAME;
    fmsys::touch(file);
  }

  return file;
}

fmsys::log_file::log_file(const std::string& program)
    : file_name{fmsys::log_setup(program)},
      file_handler{std::shared_ptr<std::ofstream>(
          new std::ofstream(file_name, std::ofstream::out))},
      file_prefix{program} {
  (*file_handler) << fmsys::LOG_HEADER;
}

std::ostream& fmsys::log_file::get_ostream() { return *file_handler; }

fmsys::log_syslog::log_syslog(const std::string& program) {
  ::openlog(program.c_str(), LOG_PID, 0);
}

fmsys::log_syslog::~log_syslog() { ::closelog(); }

fmsys::log_proxy::log_proxy(fmsys::log_file& file, fmsys::log_priority priority)
    : proxy_file{file},
      proxy_priority{priority},
      proxy_source_file{fmsys::LOG_SOURCE_FILE_UNDEF},
      proxy_source_line{fmsys::LOG_SOURCE_LINE_UNDEF},
      message{std::shared_ptr<std::ostringstream>(new std::ostringstream())} {}

fmsys::log_proxy::log_proxy(fmsys::log_file& file, fmsys::log_priority priority,
                            const char* source_file, int source_line)
    : proxy_file{file},
      proxy_priority{priority},
      proxy_source_file{source_file},
      proxy_source_line(source_line),
      message{std::shared_ptr<std::ostringstream>(new std::ostringstream())} {}

void fmsys::log_proxy::process_output() {
  auto eol = (*message).str().find(LOG_EOL);

  if (eol != std::string::npos) {
    auto output = (*message).str().substr(0, eol + 1);
    auto ps = log_priority_string(proxy_priority);
    if (proxy_priority <= fmsys::FILE_PRIORITY) {
      proxy_file.get_ostream() << proxy_file.file_prefix << ": "
                               << log_time(true) << " " << proxy_source_file
                               << ":" << proxy_source_line << ": " << ps
                               << " - " << output;
    }
    if (proxy_priority <= fmsys::CERR_PRIORITY) {
      std::cerr << proxy_file.file_prefix << " " << log_time(false) << ":"
                << (proxy_priority <= fmsys::PROBLEM_PRIORITY ? " " + ps : "")
                << " - " << output;
    }
    if (proxy_priority <= fmsys::SYSLOG_PRIORITY) {
      ::syslog(int(proxy_priority), "%s:%d: %s - %s", proxy_source_file,
               proxy_source_line, ps.c_str(), output.c_str());
    }
    if (proxy_priority <= fmsys::FLUSH_PRIORITY) {
      proxy_file.get_ostream().flush();
      std::cerr.flush();
    }
    (*message).str((*message).str().substr(eol + 1, std::string::npos));
    process_output();
  }
}

fmsys::log_proxy fmsys::log_crit() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::CRIT);
}

fmsys::log_proxy fmsys::log_crit(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::CRIT,
                          source_file, source_line);
}

fmsys::log_proxy fmsys::log_error() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::ERROR);
}

fmsys::log_proxy fmsys::log_error(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::ERROR,
                          source_file, source_line);
}

fmsys::log_proxy fmsys::log_warning() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::WARNING);
}

fmsys::log_proxy fmsys::log_warning(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::WARNING,
                          source_file, source_line);
}

fmsys::log_proxy fmsys::log_notice() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::NOTICE);
}

fmsys::log_proxy fmsys::log_notice(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::NOTICE,
                          source_file, source_line);
}

fmsys::log_proxy fmsys::log_info() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::INFO);
}

fmsys::log_proxy fmsys::log_info(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::INFO,
                          source_file, source_line);
}

fmsys::log_proxy fmsys::log_debug() {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::DEBUG);
}

fmsys::log_proxy fmsys::log_debug(const char* source_file, int source_line) {
  return fmsys::log_proxy(fmsys::global_log_file, fmsys::log_priority::DEBUG,
                          source_file, source_line);
}

std::string fmsys::log_time(bool full) {
  time_t rawtime_sec = 0;
  struct tm* timeinfo = nullptr;
  char buftime[BUFTIME_SIZE];
  char bufmicro[BUFMICRO_SIZE];
  int rawtime_micro;
  auto tp = std::chrono::system_clock::now();

  buftime[BUFTIME_SIZE - 1] = buftime[0] = '\0';
  bufmicro[BUFMICRO_SIZE - 1] = bufmicro[0] = '\0';

  rawtime_sec = (time_t)std::chrono::duration_cast<std::chrono::seconds>(
                    tp.time_since_epoch()).count();
  timeinfo = ::localtime(&rawtime_sec);
  if (timeinfo != nullptr) {
    ::strftime(buftime, BUFTIME_SIZE - 1,
               full ? BUFTIME_FORMAT_FULL : BUFTIME_FORMAT_LIGHT, timeinfo);
  }

  if (full) {
    rawtime_micro = std::chrono::duration_cast<std::chrono::microseconds>(
                        tp.time_since_epoch()).count() %
                    BUFMICRO_MODULO;
    ::snprintf(bufmicro, BUFMICRO_SIZE - 1, BUFMICRO_FORMAT, rawtime_micro);
  }

  return std::string(buftime) + std::string(bufmicro);
  ;
}

std::string fmsys::log_priority_string(fmsys::log_priority priority) {
  switch (priority) {
    case fmsys::log_priority::CRIT:
      return std::string(fmsys::STR_CRIT);
    case fmsys::log_priority::ERROR:
      return std::string(fmsys::STR_ERROR);
    case fmsys::log_priority::WARNING:
      return std::string(fmsys::STR_WARNING);
    case fmsys::log_priority::NOTICE:
      return std::string(fmsys::STR_NOTICE);
    case fmsys::log_priority::INFO:
      return std::string(fmsys::STR_INFO);
    case fmsys::log_priority::DEBUG:
      return std::string(fmsys::STR_DEBUG);
  }
  return std::string(fmsys::STR_UNKNOWN);
}

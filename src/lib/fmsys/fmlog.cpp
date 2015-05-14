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
constexpr char BUFTIME_FORMAT[] = "%Y/%m/%d %H:%M:%S.";
constexpr size_t BUFMICRO_SIZE = 20;
constexpr char BUFMICRO_FORMAT[] = "%06d";
constexpr int BUFMICRO_MODULO = 1000000;

static log_file global_log_file(fmbuild::get_package_tarname());
log_proxy log_crit(global_log_file, log_priority::CRIT);
log_proxy log_error(global_log_file, log_priority::ERROR);
log_proxy log_warning(global_log_file, log_priority::WARNING);
log_proxy log_notice(global_log_file, log_priority::NOTICE);
log_proxy log_info(global_log_file, log_priority::INFO);
log_proxy log_debug(global_log_file, log_priority::DEBUG);
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
      file_handler{std::unique_ptr<std::ofstream>(
          new std::ofstream(file_name, std::ofstream::out))},
      file_prefix{program} {
  (*file_handler.get()) << fmsys::LOG_HEADER;
}

std::ostream* fmsys::log_file::get_ostream() { return file_handler.get(); }

fmsys::log_proxy::log_proxy(log_file& file, log_priority priority)
    : std::ofstream(), proxy_file{file}, proxy_priority{priority} {}

std::string fmsys::log_time() {
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
    ::strftime(buftime, BUFTIME_SIZE - 1, BUFTIME_FORMAT, timeinfo);
  }

  rawtime_micro = std::chrono::duration_cast<std::chrono::microseconds>(
                      tp.time_since_epoch()).count() %
                  BUFMICRO_MODULO;
  ::snprintf(bufmicro, BUFMICRO_SIZE - 1, BUFMICRO_FORMAT, rawtime_micro);

  return std::string(buftime) + std::string(bufmicro);
  ;
}

std::string fmsys::log_chomp(const char* str) {
  size_t l = strlen(str);
  char buf[l + 1];

  for (l--; l > 0 && str[l] == '\n'; l--) {
  }
  ::strncpy(buf, str, l);
  buf[l] = '\0';  // paranoid ? ;)

  return std::string(buf);
}

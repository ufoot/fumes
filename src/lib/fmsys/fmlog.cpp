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
#include "../fmbuild/fmbuild.hpp"

#include <iostream>

namespace fmsys {
constexpr char LOG_HEADER[] = "DATE;MESSAGE;...\n";
constexpr char LOG_FILENAME[] = "log.txt";
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

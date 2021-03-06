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

#ifndef FMSYS_TEST_HPP
#define FMSYS_TEST_HPP

#include "fmsys.hpp"

#include <cppunit/TestCase.h>

namespace fmsys {
class home_test : public CppUnit::TestCase {
 public:
  home_test(std::string name);

  void runTest();
};

class log_test : public CppUnit::TestCase {
 public:
  log_test(std::string name);

  void runTest();
};

class path_test : public CppUnit::TestCase {
 public:
  path_test(std::string name);

  void runTest();
};
}

#endif  // FMSYS_TEST_HPP

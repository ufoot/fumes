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

#ifndef FMBUILD_TEST_HPP
#define FMBUILD_TEST_HPP

#include "fmbuild.hpp"

#include <cppunit/TestCase.h>

namespace fmbuild {
  class package_test : public CppUnit::TestCase {
  public:
    package_test(std::string name);
    
  void runTest();
  };

  class version_test : public CppUnit::TestCase {
  public:
    version_test(std::string name);
    
  void runTest();
  };
}

#endif  // FMBUILD_TEST_HPP

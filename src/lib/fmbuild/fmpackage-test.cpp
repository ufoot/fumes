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

#include "fmbuild.hpp"

#include <cppunit/TestCase.h>
#include <cppunit/TestResult.h>
#include <cppunit/ui/text/TestRunner.h>

class package_test : public CppUnit::TestCase {
 public:
  package_test(std::string name) : CppUnit::TestCase(name) {}

  void runTest() {
    CPPUNIT_ASSERT(fmbuild::get_package_tarname().length() > 0);
    CPPUNIT_ASSERT(fmbuild::get_package_name().length() > 0);
    CPPUNIT_ASSERT(fmbuild::get_package_email().length() > 0);
    CPPUNIT_ASSERT(fmbuild::get_package_url().length() > 0);
  }
};

int main(int argc, char *argv[]) {
  CppUnit::TextUi::TestRunner runner;
  package_test *test1 = new package_test(std::string("fmbuild::package"));

  runner.addTest(test1);
  runner.run();

  return 0;
}

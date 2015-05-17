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

#include "fmbuild-test.hpp"

#include <cppunit/TestResult.h>
#include <cppunit/ui/text/TestRunner.h>

fmbuild::version_test::version_test(std::string name)
    : CppUnit::TestCase(name) {}

void fmbuild::version_test::runTest() {
  CPPUNIT_ASSERT(fmbuild::get_version_major() >= 0);
  CPPUNIT_ASSERT(fmbuild::get_version_minor() > 0);
  CPPUNIT_ASSERT(fmbuild::get_version_stamp().length() > 0);
}

int main(int argc, char *argv[]) {
  CppUnit::TextUi::TestRunner runner;
  fmbuild::version_test *test1 =
      new fmbuild::version_test(std::string("fmbuild::version"));

  runner.addTest(test1);
  runner.run();

  return 0;
}

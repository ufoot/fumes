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

#include "fmsys-test.hpp"

#include <cppunit/TestResult.h>
#include <cppunit/ui/text/TestRunner.h>

fmsys::path_test::path_test(std::string name) : CppUnit::TestCase(name) {}

void fmsys::path_test::runTest() {
  std::string s1 = std::string("/foo/bar/hey");
  std::vector<std::string> v = fmsys::path_split(s1);
  std::string tmpfile = std::string("tmpfile.txt");
  std::string tmpdir = std::string("/tmp/tmpdir");

  CPPUNIT_ASSERT(v.size() == 4);
  std::string s2 = fmsys::path_join(v);
  CPPUNIT_ASSERT(s1 == s2);
  auto touch = fmsys::touch(tmpfile);
  CPPUNIT_ASSERT(touch);
  CPPUNIT_ASSERT(fmsys::file_exists(tmpfile));
  auto unlink = fmsys::unlink(tmpfile);
  CPPUNIT_ASSERT(unlink);
  CPPUNIT_ASSERT(!(fmsys::file_exists(tmpfile)));
  auto mkdir = fmsys::mkdir(tmpdir);
  CPPUNIT_ASSERT(mkdir);
  CPPUNIT_ASSERT(fmsys::dir_exists(tmpdir));
}

int main(int argc, char *argv[]) {
  CppUnit::TextUi::TestRunner runner;
  fmsys::path_test *test1 = new fmsys::path_test(std::string("fmsys::path"));

  runner.addTest(test1);
  runner.run();

  return 0;
}

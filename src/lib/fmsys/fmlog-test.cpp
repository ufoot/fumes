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

namespace fmsys {
constexpr char TEST_LOG_WORD1[] = "foo";
constexpr char TEST_LOG_WORD2[] = ",bar\n";
constexpr char TEST_LOG_MULTILINE[] = "hello\nworld\n";
}

fmsys::log_test::log_test(std::string name) : CppUnit::TestCase(name) {}

void fmsys::log_test::runTest() {
  fmsys::log_crit() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_CRIT << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_crit() << TEST_LOG_MULTILINE;
  LOG_CRIT << TEST_LOG_MULTILINE;
  fmsys::log_error() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_ERROR << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_error() << TEST_LOG_MULTILINE;
  LOG_ERROR << TEST_LOG_MULTILINE;
  fmsys::log_warning() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_WARNING << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_warning() << TEST_LOG_MULTILINE;
  LOG_WARNING << TEST_LOG_MULTILINE;
  fmsys::log_notice() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_NOTICE << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_notice() << TEST_LOG_MULTILINE;
  LOG_NOTICE << TEST_LOG_MULTILINE;
  fmsys::log_info() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_INFO << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_info() << TEST_LOG_MULTILINE;
  LOG_INFO << TEST_LOG_MULTILINE;
  fmsys::log_debug() << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  LOG_DEBUG << TEST_LOG_WORD1 << TEST_LOG_WORD2;
  fmsys::log_debug() << TEST_LOG_MULTILINE;
  LOG_DEBUG << TEST_LOG_MULTILINE;

  CPPUNIT_ASSERT(1 == 1);
}

int main(int argc, char *argv[]) {
  CppUnit::TextUi::TestRunner runner;
  fmsys::log_test *test1 = new fmsys::log_test(std::string("fmsys::log"));

  runner.addTest(test1);
  runner.run();

  return 0;
}

#include <algorithm>
#include <numeric>
#include <string>
#include <boost/test/unit_test.hpp>

#include <strtox/strtox/strtox.h>

namespace { struct Fixture { Fixture() { ::setlocale(LC_ALL, "C"); } }; }

BOOST_FIXTURE_TEST_SUITE(strtof_Tests, Fixture)

BOOST_AUTO_TEST_CASE(examples_tests)
{
  std::vector<std::string> test_values = {"1.0", "-0.333", "-INF", "+INFINITY",
    //"-NAN", // TODO: fails
    "+10.89e-1"};

  for (const auto& test : test_values)
  {
    BOOST_CHECK_EQUAL(std::stof(test), strtox::to_float(test));
  }
}

BOOST_AUTO_TEST_SUITE_END()

#include "2sum.h"
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(find_distinct_pair)
{
    SUMCompute Test(4);
    Test.inputNumbers.insert({5, 5});
    BOOST_CHECK_EQUAL(Test.findPairs(10), false);
    Test.inputNumbers.insert({4, 4});
    Test.inputNumbers.insert({6, 6});
    BOOST_CHECK_EQUAL(Test.findPairs(10), true);
    BOOST_CHECK_EQUAL(Test.findPairs(11), true);
    BOOST_CHECK_EQUAL(Test.findPairs(12), false);
    BOOST_CHECK_EQUAL(Test.findPairs(13), false);
    BOOST_CHECK_EQUAL(Test.findPairs(3), false);
    BOOST_CHECK_EQUAL(Test.findPairs(4), false);
    BOOST_CHECK_EQUAL(Test.findPairs(5), false);
    Test.inputNumbers.insert({-1, -1});
    BOOST_CHECK_EQUAL(Test.findPairs(3), true);
    BOOST_CHECK_EQUAL(Test.findPairs(4), true);
    BOOST_CHECK_EQUAL(Test.findPairs(5), true);
}

BOOST_AUTO_TEST_CASE(find_number_of_sums)
{
    SUMCompute Test(4);
    Test.inputNumbers.insert({5, 5});
    Test.inputNumbers.insert({4, 4});
    Test.inputNumbers.insert({6, 6});
    BOOST_CHECK_EQUAL(Test.numSums(1, 15), 3);
    Test.inputNumbers.insert({4, 4});
    BOOST_CHECK_EQUAL(Test.numSums(1, 15), 3);
    Test.inputNumbers.insert({-1, -1});
    BOOST_CHECK_EQUAL(Test.numSums(-3, 15), 6);
}

BOOST_AUTO_TEST_CASE(test_file_input)
{
    SUMCompute Test(1e6);
    Test.buildFromFile("algo1-programming_prob-2sum.txt");
    BOOST_CHECK(Test.inputNumbers.count(68037543430) > 0);
    BOOST_CHECK(Test.inputNumbers.count(-60012933873) > 0);
    BOOST_CHECK(Test.inputNumbers.count(0) == 0);
    BOOST_CHECK(Test.inputNumbers.count(1) == 0);
}

#if defined(RUN_ALL_TESTS)
#endif

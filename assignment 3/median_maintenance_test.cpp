 #include "median_maintenance.h"
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_priority_queues)
{
    MedianCompute Test(4);
    Test.highHeap.push(5);
    Test.highHeap.push(10);
    Test.highHeap.push(1);
    Test.highHeap.push(20);
    BOOST_CHECK_EQUAL(Test.highHeap.top(), 1);
    Test.highHeap.pop();
    BOOST_CHECK_EQUAL(Test.highHeap.top(), 5);
    Test.highHeap.push(2);
    BOOST_CHECK_EQUAL(Test.highHeap.top(), 2);
    Test.highHeap.pop();
    Test.highHeap.pop();
    BOOST_CHECK_EQUAL(Test.highHeap.top(), 10);
    Test.lowHeap.push(5);
    Test.lowHeap.push(10);
    Test.lowHeap.push(1);
    Test.lowHeap.push(20);
    BOOST_CHECK_EQUAL(Test.lowHeap.top(), 20);
    Test.lowHeap.pop();
    BOOST_CHECK_EQUAL(Test.lowHeap.top(), 10);
    Test.lowHeap.push(15);
    BOOST_CHECK_EQUAL(Test.lowHeap.top(), 15);
    Test.lowHeap.pop();
    Test.lowHeap.pop();
    BOOST_CHECK_EQUAL(Test.lowHeap.top(), 5);
}

BOOST_AUTO_TEST_CASE(test_helper_functions)
{
    MedianCompute Test(8);
    Test.highHeap.push(5);
    Test.highHeap.push(10);
    Test.highHeap.push(1);
    Test.highHeap.push(20);
    Test.lowHeap.push(5);
    Test.lowHeap.push(10);
    Test.lowHeap.push(1);
    Test.lowHeap.push(20);
    BOOST_CHECK_EQUAL(Test.returnMedian(), 20);
    Test.highHeap.pop();
    BOOST_CHECK_EQUAL(Test.returnMedian(), 20);
    Test.highHeap.pop();
    BOOST_CHECK_EQUAL(Test.returnMedian(), 0);
    Test.balanceHeaps();
    BOOST_CHECK_EQUAL(Test.returnMedian(), 10);
    Test.balanceHeaps();
    BOOST_CHECK_EQUAL(Test.returnMedian(), 10);
    Test.lowHeap.pop();
    BOOST_CHECK_EQUAL(Test.returnMedian(), 10);
    Test.lowHeap.pop();
    Test.balanceHeaps();
}

BOOST_AUTO_TEST_CASE(test_median_compute)
{
    MedianCompute Test(8);
    Test.inputNumbers = {1, 10, 3, 5, 7, 8, 9, 2};
    BOOST_CHECK_EQUAL(Test.inputNumbers[0], 1);
    BOOST_CHECK_EQUAL(Test.inputNumbers[1], 10);
    Test.computeMedians();
    BOOST_CHECK_EQUAL(Test.medians[0], 1);
    BOOST_CHECK_EQUAL(Test.medians[1], 1);
    BOOST_CHECK_EQUAL(Test.medians[2], 3);
    BOOST_CHECK_EQUAL(Test.medians[3], 3);
    BOOST_CHECK_EQUAL(Test.medians[4], 5);
    BOOST_CHECK_EQUAL(Test.medians[5], 5);
    BOOST_CHECK_EQUAL(Test.medians[6], 7);
    BOOST_CHECK_EQUAL(Test.medians[7], 5);
}

BOOST_AUTO_TEST_CASE(test_file_input)
{
    MedianCompute Test(10000);
    Test.buildFromFile("Median.txt", 10000);
    BOOST_CHECK_EQUAL(Test.inputNumbers[0], 6331);
    BOOST_CHECK_EQUAL(Test.inputNumbers[9999], 5940);
    Test.computeMedians();
    BOOST_CHECK_EQUAL(Test.medians[0], 6331);
    BOOST_CHECK_EQUAL(Test.medians[1], 2793);
    BOOST_CHECK_EQUAL(Test.medians[2], 2793);
    BOOST_CHECK_EQUAL(Test.medians[9999], 5000);
}
#if defined(RUN_ALL_TESTS)
#endif

#include "SCC.h"
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(add_node)
{
    Graph Test(3);
    Test.addNode(1, 2);
    Test.addNode(1, 3);
    BOOST_CHECK_EQUAL(Test.edges[0][0], 1);
    BOOST_CHECK_EQUAL(Test.edges[0][1], 2);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][0], 0);
}

BOOST_AUTO_TEST_CASE(test_discovered)
{
    Graph Test(3);
    for (int i = 0; i < 3; i++)
    {
        BOOST_CHECK(!Test.discovered[i]);
    }
}

BOOST_AUTO_TEST_CASE(test_file_input)
{
    Graph Test(3);
    Test.buildFromFile("testInput.txt", 3);
    BOOST_CHECK_EQUAL(Test.edges[0][0], 1);
    BOOST_CHECK_EQUAL(Test.edges[0][1], 2);
    BOOST_CHECK_EQUAL(Test.edges[1][0], 2);
    BOOST_CHECK_EQUAL(Test.edges[2][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[0][0], 2);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][1], 1);
}

BOOST_AUTO_TEST_CASE(test_simple_DFS)
{
    Graph Test(3);
    Test.addNode(1, 2);
    Test.addNode(2, 3);
    BOOST_CHECK_EQUAL(Test.edges[0][0], 1);
    BOOST_CHECK_EQUAL(Test.edges[1][0], 2);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][0], 1);
    Test.DFS_1(2, Test.edges);
}

BOOST_AUTO_TEST_CASE(test_finishing_times)
{
    Graph Test(4);
    Test.buildFromFile("testInput2.txt", 4);
    BOOST_CHECK_EQUAL(Test.edges[0][0], 1);
    BOOST_CHECK_EQUAL(Test.edges[0][1], 3);
    BOOST_CHECK_EQUAL(Test.edges[1][0], 2);
    BOOST_CHECK_EQUAL(Test.edges[2][0], 0);
    BOOST_CHECK_EQUAL(Test.edges[3][0], 1);

    BOOST_CHECK_EQUAL(Test.reverseEdges[3][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][1], 3);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][0], 1);
    BOOST_CHECK_EQUAL(Test.reverseEdges[0][0], 2);
    Test.DFS_1(0, Test.edges);
    BOOST_CHECK_EQUAL(Test.finishingTimes[0], 2);
    BOOST_CHECK_EQUAL(Test.finishingTimes[1], 1);
    BOOST_CHECK_EQUAL(Test.finishingTimes[2], 3);
    BOOST_CHECK_EQUAL(Test.finishingTimes[3], 0);
}

BOOST_AUTO_TEST_CASE(test_finishing_times_2)
{
    Graph Test(4);
    Test.buildFromFile("testInput2.txt", 4);
    Test.DFS_over_nodes_1(Test.edges);
    BOOST_CHECK_EQUAL(Test.finishingTimes[0], 2);
    BOOST_CHECK_EQUAL(Test.finishingTimes[1], 1);
    BOOST_CHECK_EQUAL(Test.finishingTimes[2], 3);
    BOOST_CHECK_EQUAL(Test.finishingTimes[3], 0);
}

BOOST_AUTO_TEST_CASE(test_file_real_input)
{
    Graph Test(875714);
    Test.buildFromFile("SCC.txt", 875714);
    BOOST_CHECK_EQUAL(Test.edges[0][0], 1 - 1);
    BOOST_CHECK_EQUAL(Test.edges[0][1], 2 - 1);
    BOOST_CHECK_EQUAL(Test.edges[0][7], 4 - 1);
    BOOST_CHECK_EQUAL(Test.edges[1][0], 47646 - 1);
    BOOST_CHECK_EQUAL(Test.reverseEdges[0][0], 1 - 1);
    BOOST_CHECK_EQUAL(Test.reverseEdges[1][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[2][0], 0);
    BOOST_CHECK_EQUAL(Test.reverseEdges[47646 - 1][0], 2 - 1);
    BOOST_CHECK_EQUAL(Test.discovered[0], false);
    BOOST_CHECK_EQUAL(Test.discovered[875714 - 1], false);
}

BOOST_AUTO_TEST_CASE(test_file_SCC_results_1)
{
    Graph Test(9);
    Test.kosaraju("testInput3.txt", 9);
    BOOST_CHECK_EQUAL(Test.maxSCC[4], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[3], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[2], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[1], 1);
    BOOST_CHECK_EQUAL(Test.maxSCC[0], 1);
}

BOOST_AUTO_TEST_CASE(test_file_SCC_results_2)
{
    Graph Test(13);
    Test.kosaraju("testInput4.txt", 13);
    BOOST_CHECK_EQUAL(Test.maxSCC[4], 4);
    BOOST_CHECK_EQUAL(Test.maxSCC[3], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[2], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[1], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[0], 1);
}

BOOST_AUTO_TEST_CASE(test_file_SCC_results_3)
{
    Graph Test(20);
    Test.kosaraju("testInput5.txt", 20);
    BOOST_CHECK_EQUAL(Test.maxSCC[4], 4);
    BOOST_CHECK_EQUAL(Test.maxSCC[3], 4);
    BOOST_CHECK_EQUAL(Test.maxSCC[2], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[1], 3);
    BOOST_CHECK_EQUAL(Test.maxSCC[0], 3);
}
#if defined(RUN_ALL_TESTS)
#endif

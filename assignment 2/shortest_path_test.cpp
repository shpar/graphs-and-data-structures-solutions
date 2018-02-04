#include "shortest_path.h"
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(constructor)
{
    Graph Test(10);
    BOOST_CHECK_EQUAL(Test.vertices.size(), 10);
}

BOOST_AUTO_TEST_CASE(test_input)
{
    Graph Test(4);
    Test.buildFromFile("testInput.txt", 4);
    BOOST_CHECK_EQUAL(Test.edges[0], 1);
    BOOST_CHECK_EQUAL(Test.weights[0], 1);
    BOOST_CHECK_EQUAL(Test.edges[1], 2);
    BOOST_CHECK_EQUAL(Test.weights[1], 4);
    BOOST_CHECK_EQUAL(Test.edges[2], 2);
    BOOST_CHECK_EQUAL(Test.weights[2], 2);
    BOOST_CHECK_EQUAL(Test.edges[3], 3);
    BOOST_CHECK_EQUAL(Test.weights[3], 6);
    BOOST_CHECK_EQUAL(Test.edges[4], 3);
    BOOST_CHECK_EQUAL(Test.weights[4], 3);
    
    BOOST_CHECK_EQUAL(Test.vertices[0][0], 0);
    BOOST_CHECK_EQUAL(Test.vertices[0][1], 1);
    BOOST_CHECK_EQUAL(Test.vertices[1][0], 2);
    BOOST_CHECK_EQUAL(Test.vertices[1][1], 3);
    BOOST_CHECK_MESSAGE(Test.vertices[1][1] == 3, "vertice[1][1] =" << Test.vertices[1][1]);
    BOOST_CHECK_MESSAGE(Test.edges.back() == 3, "edges.last" << Test.edges.back());
    BOOST_CHECK_MESSAGE(Test.weights.back() == 3, "weights.last" << Test.weights.back());

}

BOOST_AUTO_TEST_CASE(test_given_input)
{
    Graph Test(200);
    Test.buildFromFile("dijkstraData.txt", 200);
    BOOST_CHECK_EQUAL(Test.edges[0], 79);
    BOOST_CHECK_EQUAL(Test.weights[0], 982);
    BOOST_CHECK_EQUAL(Test.edges[1], 162);
    BOOST_CHECK_EQUAL(Test.weights[1], 8164);
    BOOST_CHECK_EQUAL(Test.edges[2], 169);
    BOOST_CHECK_EQUAL(Test.weights[2], 2620);
    BOOST_CHECK_EQUAL(Test.edges[3], 144);
    BOOST_CHECK_EQUAL(Test.weights[3], 648);
    
    BOOST_CHECK_MESSAGE(Test.edges.back() == 53, "edges.last" << Test.edges.back());
    BOOST_CHECK_MESSAGE(Test.edges.size() == 3734, "edges.size" << Test.edges.size());
    BOOST_CHECK_MESSAGE(Test.weights.back() == 4899, "weights.last" << Test.weights.back());
    BOOST_CHECK_MESSAGE(Test.vertices[199][24] == 3733, "vertice[1][1] =" << Test.vertices[199][24]);
}

BOOST_AUTO_TEST_CASE(test_one_step)
{
    Graph Test(4);
    Test.buildFromFile("testInput.txt", 4);
    Test.visitedVertices.push_back(0);
    Test.shortestDistance[0] = 0;
    BOOST_CHECK_EQUAL(Test.shortestOneStep(), true);
    BOOST_CHECK_EQUAL(Test.currentNode, 1);
    BOOST_CHECK_EQUAL(Test.currentShortestPath, 1);
}

BOOST_AUTO_TEST_CASE(test_dijkstra_1)
{
    Graph Test(4);
    Test.buildFromFile("testInput.txt", 4);
    Test.primitiveDijkstra(0);
    BOOST_CHECK_EQUAL(Test.shortestDistance[0], 0);
    BOOST_CHECK_EQUAL(Test.shortestDistance[1], 1);
    BOOST_CHECK_EQUAL(Test.shortestDistance[2], 3);
    BOOST_CHECK_EQUAL(Test.shortestDistance[3], 6);
}

BOOST_AUTO_TEST_CASE(test_dijkstra_2)
{
    Graph Test(5);
    Test.buildFromFile("testInput2.txt", 5);
    Test.primitiveDijkstra(0);
    BOOST_CHECK_EQUAL(Test.shortestDistance[0], 0);
    BOOST_CHECK_EQUAL(Test.shortestDistance[1], 1);
    BOOST_CHECK_EQUAL(Test.shortestDistance[2], 3);
    BOOST_CHECK_EQUAL(Test.shortestDistance[3], 6);
    BOOST_CHECK_EQUAL(Test.shortestDistance[4], 1000);
}

#if defined(RUN_ALL_TESTS)
#endif

/*!
 * @file
 * This file defines unit tests for `boost::mpl::adjacent_vertices_of`.
 */

#include <boost/mpl/reachable_set.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_equal.hpp>
#include <boost/mpl/vector.hpp>


using namespace boost::mpl;

template <typename ...Neighbors>
struct vertex {
    using open_neighborhood = vector<Neighbors...>;
};

template <typename ...Vertices>
struct graph {
    using vertices = vector<Vertices...>;
};

struct dummy_graph;

struct v0 : vertex<> { };
struct v1 : vertex<> { };
struct g0 : graph<v0, v1> { };

struct v2 : vertex<g0> { };
struct v3 : vertex<g0, v0> { };
struct v4 : vertex<v1, v2> { };
struct g1 : graph<v2, v3, v4> { };

static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, v0>::type, set<>
>::value, "");
static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, v1>::type, set<>
>::value, "");
static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, v2>::type, set<v0, v1>
>::value, "");
static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, v3>::type, set<v0, v1>
>::value, "");
static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, v4>::type, set<v1, v2>
>::value, "");


struct vertex_and_graph : vertex<v3, graph<v2, v1, v0>> { };
static_assert(set_equal<
    adjacent_vertices_of<dummy_graph, vertex_and_graph>::type,
    set<v3, v2, v1, v0>
>::value, "");


int main() { }

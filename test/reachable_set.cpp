/*!
 * @file
 * This file defines unit tests for `boost::mpl::reachable_set`.
 */

#include <boost/mpl/reachable_set.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_equal.hpp>
#include <boost/mpl/vector.hpp>


using namespace boost::mpl;

template <typename ...AdjacentVertices>
struct vertex {
    using open_neighborhood = vector<AdjacentVertices...>;
};

namespace test_cyclic_graph {
    // cycle: u0 -> u2 -> u1 -> u0
    struct u0 : vertex<struct u2> { };
    struct u1 : vertex<u0> { };
    struct u2 : vertex<u1> { };

    static_assert(set_equal<
        reachable_set<u0>::type, set<u0, u2, u1>
    >::value, "");

    static_assert(set_equal<
        reachable_set<u1>::type, set<u1, u0, u2>
    >::value, "");

    static_assert(set_equal<
        reachable_set<u2>::type, set<u2, u1, u0>
    >::value, "");
}

namespace test_acyclic_graph {
    struct v0 : vertex<> { };
    struct v1 : vertex<v0> { };
    struct v2 : vertex<v0, v1> { };
    struct v3 : vertex<v1> { };

    static_assert(set_equal<
        reachable_set<v0>::type, set<v0>
    >::value, "");

    static_assert(set_equal<
        reachable_set<v1>::type, set<v1, v0>
    >::value, "");

    static_assert(set_equal<
        reachable_set<v2>::type, set<v2, v0, v1>
    >::value, "");

    static_assert(set_equal<
        reachable_set<v3>::type, set<v3, v1, v0>
    >::value, "");
}


int main() { }

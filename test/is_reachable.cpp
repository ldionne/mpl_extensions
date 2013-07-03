/*!
 * @file
 * This file defines unit tests for `boost::mpl::is_reachable`.
 */

#include <boost/mpl/is_reachable.hpp>
#include <boost/mpl/vector.hpp>


using namespace boost::mpl;

template <typename ...AdjacentVertices>
struct vertex {
    using adjacent_vertices = vector<AdjacentVertices...>;
};

namespace test_graph_with_cycle {
    // cycle: u0 -> u4 -> u1 -> u0
    struct u0 : vertex<struct u4> { };
    struct u1 : vertex<u0> { };
    struct u2 : vertex<> { };
    struct u3 : vertex<u2> { };
    struct u4 : vertex<u1, u3> { };

    static_assert(is_reachable<u0, u2>::value, "");
}

namespace test_acyclic_graph {
    struct v0 : vertex<struct v3> { };
    struct v1 : vertex<v0> { };
    struct v2 : vertex<v1> { };
    struct v3 : vertex<> { };
    struct v4 : vertex<v3, v2> { };

    static_assert(is_reachable<v0, v0>::value, "");
    static_assert(!is_reachable<v0, v1>::value, "");
    static_assert(!is_reachable<v0, v2>::value, "");
    static_assert(is_reachable<v0, v3>::value, "");
    static_assert(!is_reachable<v0, v4>::value, "");

    static_assert(is_reachable<v1, v0>::value, "");
    static_assert(is_reachable<v1, v1>::value, "");
    static_assert(!is_reachable<v1, v2>::value, "");
    static_assert(is_reachable<v1, v3>::value, "");
    static_assert(!is_reachable<v1, v4>::value, "");

    static_assert(is_reachable<v2, v0>::value, "");
    static_assert(is_reachable<v2, v1>::value, "");
    static_assert(is_reachable<v2, v2>::value, "");
    static_assert(is_reachable<v2, v3>::value, "");
    static_assert(!is_reachable<v2, v4>::value, "");

    static_assert(!is_reachable<v3, v0>::value, "");
    static_assert(!is_reachable<v3, v1>::value, "");
    static_assert(!is_reachable<v3, v2>::value, "");
    static_assert(is_reachable<v3, v3>::value, "");
    static_assert(!is_reachable<v3, v4>::value, "");

    static_assert(is_reachable<v4, v0>::value, "");
    static_assert(is_reachable<v4, v1>::value, "");
    static_assert(is_reachable<v4, v2>::value, "");
    static_assert(is_reachable<v4, v3>::value, "");
    static_assert(is_reachable<v4, v4>::value, "");
}


int main() { }

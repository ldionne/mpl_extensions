/*!
 * @file
 * This file defines unit tests for `boost::mpl::is_adjacent`.
 */

#include <boost/mpl/is_adjacent.hpp>
#include <boost/mpl/vector.hpp>


using namespace boost::mpl;

template <typename ...AdjacentVertices>
struct vertex {
    using open_neighborhood = vector<AdjacentVertices...>;
};

namespace test_acyclic_graph {
    struct v0 : vertex<> { };
    struct v1 : vertex<v0> { };
    struct v2 : vertex<v0> { };
    struct v3 : vertex<v1, v2> { };

    static_assert(!is_adjacent<v0, v0>::value, "");
    static_assert(!is_adjacent<v0, v1>::value, "");
    static_assert(!is_adjacent<v0, v2>::value, "");
    static_assert(!is_adjacent<v0, v3>::value, "");

    static_assert(is_adjacent<v1, v0>::value, "");
    static_assert(!is_adjacent<v1, v1>::value, "");
    static_assert(!is_adjacent<v1, v2>::value, "");
    static_assert(!is_adjacent<v1, v3>::value, "");

    static_assert(is_adjacent<v2, v0>::value, "");
    static_assert(!is_adjacent<v2, v1>::value, "");
    static_assert(!is_adjacent<v2, v2>::value, "");
    static_assert(!is_adjacent<v2, v3>::value, "");

    static_assert(!is_adjacent<v3, v0>::value, "");
    static_assert(is_adjacent<v3, v1>::value, "");
    static_assert(is_adjacent<v3, v2>::value, "");
    static_assert(!is_adjacent<v3, v3>::value, "");
}


int main() { }

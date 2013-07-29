/*!
 * @file
 * This file defines unit tests for `boost::mpl::topological_sort`.
 */

#include <boost/mpl/topological_sort.hpp>
#include <boost/mpl/any_of.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::mpl;

template <typename Sequence, typename Element>
struct contains_equal
    : any_of<Sequence, equal<Element, _1, quote2<boost::is_same>>>
{ };

template <typename ...AdjacentVertices>
struct vertex {
    using open_neighborhood = typename vector<AdjacentVertices...>::type;
};

template <typename ...Vertices>
struct graph {
    using vertices = typename set<Vertices...>::type;
};

namespace test_trivial {
    static_assert(equal<
        vector<>,
        topological_sort<graph<>>::type
    >::value, "");

    static_assert(equal<
        vector<vertex<>>,
        topological_sort<graph<vertex<>>>::type
    >::value, "");
}

namespace test_linear {
    struct v0 : vertex<> { };
    struct v1 : vertex<v0> { };
    struct v2 : vertex<v1> { };

    static_assert(equal<
        vector<v0, v1, v2>,
        topological_sort<graph<v0, v1, v2>>::type
    >::value, "");
}

namespace test_multiple_valid_orderings {
    struct v0 : vertex<> { };
    struct v1 : vertex<v0> { };
    struct v2 : vertex<v0> { };
    struct v3 : vertex<v1, v2> { };

    static_assert(contains_equal<
        vector<
            vector<v0, v1, v2, v3>,
            vector<v0, v2, v1, v3>
        >,
        topological_sort<graph<v0, v1, v2, v3>>::type
    >::value, "");
}


int main() { }

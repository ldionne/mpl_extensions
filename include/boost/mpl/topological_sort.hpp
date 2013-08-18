/*!
 * @file
 * This file defines `boost::mpl::topological_sort`.
 */

#ifndef BOOST_MPL_TOPOLOGICAL_SORT_HPP
#define BOOST_MPL_TOPOLOGICAL_SORT_HPP

#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/graph_intrinsics.hpp>
#include <boost/mpl/is_cyclic.hpp>
#include <boost/mpl/is_reachable.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/vector.hpp>


namespace boost { namespace mpl {
    template <typename U, typename V>
    using edge = pair<U, V>;

    template <typename Graph>
    struct impl {
        using Vertices = typename vertices_of<Graph>::type;
        using AdjacentVertices = typename make_index_of<
            Vertices,
            _1,
            adjacent_vertices_of<_1, Graph>
        >::type;

        template <typename U>
        struct out_edges {
            using type = transform_view<
                typename adjacent_vertices_of<U, Graph>::type,
                pair<U, _1>
            >;
        };

        using OutEdges = typename make_index_of<
            Vertices,
            _1,
            out_edges<_1>
        >::type;

        template <typename Map, typename U>
        struct insert_in_edges {
            using Updates = typename fold<
                typename adjacent_vertices_of<U, Graph>::type,
                set<>,
            >::type;
            using type = ;
        };

        using InEdges = typename fold<
            Vertices,
            map<>,
            insert_in_edges<_1, _2>
        >::type;
    };

    template <typename Graph>
    struct topological_sort {
        using L = vector<>;
        using Q = typename set_insert_range<set<>,
            filter_view<
                typename vertices_of<Graph>::type,
                has_no_incoming_edges<_1>
            >
        >::type;

        template <typename Cond, typename Lambda>
        using until = while_<not_<Cond>, Lambda>;

        template <typename Q>
        struct x {
            using n = typename pop_front<Q>::type;
            using L = typename push_back<L, n>::type;
            typename adjacent_vertices_of<n>::type

        };

        using type = typename until<empty<_1>,
            x<_1>
        >::type;




        // L ← Empty list where we put the sorted elements
        // Q ← Set of all nodes with no incoming edges
        // while Q is non-empty do
        //     remove a node n from Q
        //     insert n into L
        //     for each node m with an edge e from n to m do
        //         remove edge e from the graph
        //         if m has no other incoming edges then
        //             insert m into Q
        // if graph has edges then
        //     output error message (graph has a cycle)
        // else
        //     output message (proposed topologically sorted order: L)
    };

    //! Return a valid topological ordering of the vertices of a graph.
    template <typename Graph>
    struct topological_sort
        : sort<typename vertices_of<Graph>::type,
            is_reachable<Graph, _1, _2>,
            front_inserter<vector<>>
        >
    {
        static_assert(!is_cyclic<Graph>::value,
            "it is impossible to find a valid topological "
            "ordering in a cyclic graph");
    };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_TOPOLOGICAL_SORT_HPP

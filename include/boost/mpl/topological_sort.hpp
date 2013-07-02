/*!
 * @file
 * This file defines `boost::mpl::topological_sort`.
 */

#ifndef BOOST_MPL_TOPOLOGICAL_SORT_HPP
#define BOOST_MPL_TOPOLOGICAL_SORT_HPP

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/graph_intrinsics.hpp>
#include <boost/mpl/is_reachable.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/vector.hpp>


namespace boost { namespace mpl {
    //! Return a valid topological ordering of the vertices of a graph.
    template <typename Graph>
    struct topological_sort
        : sort<typename vertices_of<Graph>::type,
            is_reachable<_1, _2>,
            back_inserter<vector<>>
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_TOPOLOGICAL_SORT_HPP

/*!
 * @file
 * This file defines `boost::mpl::adjacent_vertices_of`.
 */

#ifndef BOOST_MPL_ADJACENT_VERTICES_OF_HPP
#define BOOST_MPL_ADJACENT_VERTICES_OF_HPP

#include <boost/mpl/fold.hpp>
#include <boost/mpl/graph_intrinsics.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_insert_range.hpp>


namespace boost { namespace mpl {
    //! Return the set of vertices in the open neighborhood of a `Vertex`.
    template <typename Vertex>
    struct adjacent_vertices_of
        : fold<typename open_neighborhood_of<Vertex>::type,
            set<>,
            if_<
                is_graph<_2>,
                set_insert_range<
                    if_<is_vertex<_2>, insert<_1, _2>, _1>,
                    vertices_of<_2>
                >,
                insert<_1, _2>
            >
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_ADJACENT_VERTICES_OF_HPP

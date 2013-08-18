/*!
 * @file
 * This file defines `boost::mpl::is_cyclic`.
 */

#ifndef BOOST_MPL_IS_CYCLIC_HPP
#define BOOST_MPL_IS_CYCLIC_HPP

#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/graph_intrinsics.hpp>
#include <boost/mpl/is_cyclic.hpp>
#include <boost/mpl/is_reachable.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/vector.hpp>


namespace boost { namespace mpl {
    namespace is_cyclic_detail {
        template <typename Graph>
        struct impl {
            template <typename Vertex, typename Visited>
            struct apply
                : or_<
                    has_key<Visited, Vertex>,
                    any_of<adjacent_vertices_of<Graph, Vertex>,


            { };

        };
    }

    //! Return whether a graph contains a cycle in it.
    template <typename Graph>
    struct is_cyclic
        :
    {

    };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_IS_CYCLIC_HPP

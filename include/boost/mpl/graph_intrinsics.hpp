/*!
 * @file
 * This file defines intrinsic operations on MPL graphs.
 */

#ifndef BOOST_MPL_GRAPH_INTRINSICS_HPP
#define BOOST_MPL_GRAPH_INTRINSICS_HPP

#include <boost/mpl/has_xxx.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace mpl {
    namespace graph_intrinsics_detail {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(open_neighborhood)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(vertices)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(type)

        template <typename Vertex>
        struct open_neighborhood_of {
            using type = typename Vertex::open_neighborhood;
        };

        template <typename Graph>
        struct vertices_of {
            using type = typename Graph::vertices;
        };
    } // end namespace graph_intrinsics_detail

    //! Return the set of vertices and graphs in the open neighborhood
    //! of a `Vertex`.
    template <typename Vertex, typename Enable = void>
    struct open_neighborhood_of
        : lazy_enable_if<
            graph_intrinsics_detail::has_open_neighborhood<Vertex>,
            graph_intrinsics_detail::open_neighborhood_of<Vertex>
        >
    { };

    //! Return the set of all the vertices of a graph.
    template <typename Graph, typename Enable = void>
    struct vertices_of
        : lazy_enable_if<
            graph_intrinsics_detail::has_vertices<Graph>,
            graph_intrinsics_detail::vertices_of<Graph>
        >
    { };

    //! Return whether a type is an MPL `Vertex`.
    template <typename T, typename Enable = void>
    struct is_vertex
        : graph_intrinsics_detail::has_type<open_neighborhood_of<T>>::type
    { };

    //! Return whether a type is an MPL `Graph`.
    template <typename T, typename Enable = void>
    struct is_graph
        : graph_intrinsics_detail::has_type<vertices_of<T>>::type
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_GRAPH_INTRINSICS_HPP

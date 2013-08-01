/*!
 * @file
 * This file defines intrinsic operations on MPL graphs.
 */

#ifndef BOOST_MPL_GRAPH_INTRINSICS_HPP
#define BOOST_MPL_GRAPH_INTRINSICS_HPP

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/tag_of.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace mpl {
namespace graph_intrinsics_detail {
    BOOST_MPL_HAS_XXX_TRAIT_DEF(open_neighborhood)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(vertices)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(type)

    template <typename Vertex>
    struct nested_open_neighborhood {
        using type = typename Vertex::open_neighborhood;
    };

    template <typename Graph>
    struct nested_vertices {
        using type = typename Graph::vertices;
    };
} // end namespace graph_intrinsics_detail

namespace extension {
    template <typename Tag, typename Enable = void>
    struct open_neighborhood_of_impl {
        template <typename Graph, typename Vertex>
        struct apply
            : lazy_enable_if<
                graph_intrinsics_detail::has_open_neighborhood<Vertex>,
                graph_intrinsics_detail::nested_open_neighborhood<Vertex>
            >
        { };
    };

    template <typename Tag, typename Enable = void>
    struct vertices_of_impl {
        template <typename Graph>
        struct apply
            : lazy_enable_if<
                graph_intrinsics_detail::has_vertices<Graph>,
                graph_intrinsics_detail::nested_vertices<Graph>
            >
        { };
    };
} // end namespace extension

//! Return the set of vertices and graphs in the open neighborhood
//! of a `Vertex` in a `Graph`.
template <typename Graph, typename Vertex>
struct open_neighborhood_of
    : extension::open_neighborhood_of_impl<
        typename tag_of<Graph>::type
    >::template apply<Graph, Vertex>
{ };

//! Return the set of all the vertices of a `Graph`.
template <typename Graph>
struct vertices_of
    : extension::vertices_of_impl<
        typename tag_of<Graph>::type
    >::template apply<Graph>
{ };

//! Return whether a type is an MPL `Vertex`.
template <typename Graph, typename T, typename Enable = void>
struct is_vertex
    : graph_intrinsics_detail::has_type<open_neighborhood_of<Graph, T>>::type
{ };

//! Return whether a type is an MPL `Graph`.
template <typename T, typename Enable = void>
struct is_graph
    : graph_intrinsics_detail::has_type<vertices_of<T>>::type
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_GRAPH_INTRINSICS_HPP

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
    BOOST_MPL_HAS_XXX_TRAIT_DEF(type)
    template <typename Graph, typename VertexOrEdge>
    using fetch_in_vertex_or_edge = VertexOrEdge;

    template <typename Graph>
    using fetch_in_graph = Graph;
}

#define BOOST_MPL11_I_DEFINE_INTRINSIC(RETRIEVE_ARG, INTRINSIC, NESTED_NAME)\
    namespace graph_intrinsics_detail {                                     \
        BOOST_MPL_HAS_XXX_TRAIT_DEF(NESTED_NAME)                            \
                                                                            \
        template <typename T>                                               \
        struct nested_##NESTED_NAME {                                       \
            using type = typename T::NESTED_NAME;                           \
        };                                                                  \
    }                                                                       \
                                                                            \
    namespace extension {                                                   \
        template <typename Tag, typename Enable = void>                     \
        struct INTRINSIC##_impl {                                           \
            template <typename ...Args>                                     \
            struct apply                                                    \
                : lazy_enable_if<                                           \
                    has_##NESTED_NAME<                                      \
                        graph_intrinsics_detail::RETRIEVE_ARG<Args...>      \
                    >,                                                      \
                    nested_##NESTED_NAME<                                   \
                        graph_intrinsics_detail::RETRIEVE_ARG<Args...>      \
                    >                                                       \
                >                                                           \
            { };                                                            \
        };                                                                  \
    }                                                                       \
/**/

BOOST_MPL11_I_DEFINE_INTRINSIC(
    fetch_in_vertex_or_edge, open_neighborhood_of, open_neighborhood
)
BOOST_MPL11_I_DEFINE_INTRINSIC(fetch_in_graph, vertices_of, vertices)
BOOST_MPL11_I_DEFINE_INTRINSIC(fetch_in_vertex_or_edge, source, source)
BOOST_MPL11_I_DEFINE_INTRINSIC(fetch_in_vertex_or_edge, target, target)

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

//! Return the source vertex of an `Edge`.
template <typename Graph, typename Edge>
struct source
    : extension::source_impl<
        typename tag_of<Graph>::type
    >::template apply<Graph, Edge>
{ };

//! Return the target vertex of an `Edge`.
template <typename Graph, typename Edge>
struct target
    : extension::target_impl<
        typename tag_of<Graph>::type
    >::template apply<Graph, Edge>
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

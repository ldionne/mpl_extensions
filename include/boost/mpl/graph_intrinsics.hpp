/*!
 * @file
 * This file defines intrinsic operations on MPL graphs.
 */

#ifndef BOOST_MPL_GRAPH_INTRINSICS_HPP
#define BOOST_MPL_GRAPH_INTRINSICS_HPP

namespace boost { namespace mpl {
    //! Return the set of vertices in the open neighborhood of a `Vertex`.
    template <typename Vertex>
    struct adjacent_vertices_of {
        using type = typename Vertex::adjacent_vertices;
    };

    //! Return the set of all the vertices of a graph.
    template <typename Graph>
    struct vertices_of {
        using type = typename Graph::vertices;
    };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_GRAPH_INTRINSICS_HPP

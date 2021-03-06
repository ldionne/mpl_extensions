/*!
 * @file
 * This file defines `boost::mpl::is_adjacent`.
 */

#ifndef BOOST_MPL_IS_ADJACENT_HPP
#define BOOST_MPL_IS_ADJACENT_HPP

#include <boost/mpl/adjacent_vertices_of.hpp>
#include <boost/mpl/contains.hpp>


namespace boost { namespace mpl {
    //! Return whether `V` is in the open neighborhood of `U`.
    template <typename Graph, typename U, typename V>
    struct is_adjacent
        : contains<typename adjacent_vertices_of<Graph, U>::type, V>
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_IS_ADJACENT_HPP

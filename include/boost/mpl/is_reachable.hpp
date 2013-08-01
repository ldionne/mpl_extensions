/*!
 * @file
 * This file defines `boost::mpl::is_reachable`.
 */

#ifndef BOOST_MPL_IS_REACHABLE_HPP
#define BOOST_MPL_IS_REACHABLE_HPP

#include <boost/mpl/adjacent_vertices_of.hpp>
#include <boost/mpl/any_of.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/is_adjacent.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/set.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace mpl {
    namespace is_reachable_detail {
        template <typename Graph, typename U, typename V, typename Seen>
        struct is_reachable_not_same;

        template <typename Graph, typename U, typename V, typename Seen>
        struct is_reachable_impl
            : or_<
                is_same<U, V>,
                is_adjacent<Graph, U, V>,
                is_reachable_not_same<Graph, U, V, Seen>
            >
        { };

        template <typename Graph, typename U, typename V, typename Seen>
        struct is_reachable_not_same {
            using NewSeen = typename insert<Seen, U>::type;

            using UnseenAdjacentVertices = filter_view<
                typename adjacent_vertices_of<Graph, U>::type,
                not_<has_key<NewSeen, _1>>
            >;

            using type = typename any_of<
                UnseenAdjacentVertices,
                is_reachable_impl<Graph, _1, V, NewSeen>
            >::type;
        };
    }

    //! Return whether `V` is reachable from `U`. A vertex is considered
    //! reachable from itself.
    template <typename Graph, typename U, typename V>
    struct is_reachable
        : is_reachable_detail::is_reachable_impl<Graph, U, V, set<>>
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_IS_REACHABLE_HPP

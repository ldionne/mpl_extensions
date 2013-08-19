/*!
 * @file
 * This file defines `boost::mpl::reachable_set`.
 */

#ifndef BOOST_MPL_REACHABLE_SET_HPP
#define BOOST_MPL_REACHABLE_SET_HPP

#include <boost/mpl/adjacent_vertices_of.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>


namespace boost { namespace mpl {
namespace reachable_set_detail {
    template <typename Graph>
    struct impl {
        template <typename Vertex, typename Seen>
        struct unseen_adjacent_vertices {
            using type = filter_view<
                typename adjacent_vertices_of<Graph, Vertex>::type,
                not_<has_key<Seen, _1>>
            >;
        };

        template <typename Seen, typename ToVisit, bool=empty<ToVisit>::value>
        struct apply {
            using Vertex = typename front<ToVisit>::type;

            using NewToVisit = typename pop_front<ToVisit>::type;
            using NewSeen = typename insert<Seen, Vertex>::type;

            using type = typename apply<
                NewSeen,
                typename insert_range<
                    NewToVisit,
                    typename end<NewToVisit>::type,
                    typename unseen_adjacent_vertices<Vertex, NewSeen>::type
                >::type
            >::type;
        };

        template <typename Seen, typename ToVisit>
        struct apply<Seen, ToVisit, true> {
            using type = Seen;
        };
    };
} // end namespace reachable_set_detail

//! Return the set of all the vertices that are reachable from a `Vertex`.
template <typename Graph, typename Vertex>
struct reachable_set
    : reachable_set_detail::impl<
        Graph
    >::template apply<typename set<>::type, typename vector<Vertex>::type>
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_REACHABLE_SET_HPP

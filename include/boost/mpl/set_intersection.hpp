/*!
 * @file
 * This file defines `boost::mpl::set_intersection`.
 */

#ifndef BOOST_MPL_SET_INTERSECTION_HPP
#define BOOST_MPL_SET_INTERSECTION_HPP

#include <boost/mpl/clear.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>


namespace boost { namespace mpl {
    template <typename Set1, typename Set2, typename ...Setn>
    struct set_intersection
        : set_intersection<
            typename set_intersection<Set1, Set2>::type,
            Setn...
        >
    { };

    template <typename Set1, typename Set2>
    struct set_intersection<Set1, Set2>
        : fold<
            Set1,
            typename clear<Set1>::type,
            if_<has_key<Set2, _2>, insert<_1, _2>, _1>
        >
    { };
}}

#endif // !BOOST_MPL_SET_INTERSECTION_HPP

/*!
 * @file
 * This file defines `boost::mpl::set_union`.
 */

#ifndef BOOST_MPL_SET_UNION_HPP
#define BOOST_MPL_SET_UNION_HPP

#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>


namespace boost { namespace mpl {
    template <typename Set1, typename Set2, typename ...Setn>
    struct set_union
        : set_union<
            typename set_union<Set1, Set2>::type,
            Setn...
        >
    { };

    template <typename Set1, typename Set2>
    struct set_union<Set1, Set2>
        : fold<Set1, Set2, insert<_1, _2>>
    { };
}}

#endif // !BOOST_MPL_SET_UNION_HPP

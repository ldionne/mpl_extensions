/*!
 * @file
 * This file defines `boost::mpl::set_insert_range`.
 */

#ifndef BOOST_MPL_SET_INSERT_RANGE_HPP
#define BOOST_MPL_SET_INSERT_RANGE_HPP

#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/placeholders.hpp>


namespace boost { namespace mpl {
    template <typename Set, typename Range>
    struct set_insert_range
        : fold<Range, Set, insert<_1, _2>>
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_SET_INSERT_RANGE_HPP

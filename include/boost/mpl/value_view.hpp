/*!
 * @file
 * This file defines `boost::mpl::value_view`.
 */

#ifndef BOOST_MPL_VALUE_VIEW_HPP
#define BOOST_MPL_VALUE_VIEW_HPP

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/value_type.hpp>


namespace boost { namespace mpl {
    template <typename AssociativeSequence>
    struct value_view
        : transform_view<
            AssociativeSequence,
            value_type<AssociativeSequence, _1>
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_VALUE_VIEW_HPP

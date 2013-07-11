/*!
 * @file
 * This file defines `boost::mpl::key_view`.
 */

#ifndef BOOST_MPL_KEY_VIEW_HPP
#define BOOST_MPL_KEY_VIEW_HPP

#include <boost/mpl/key_type.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>


namespace boost { namespace mpl {
    template <typename AssociativeSequence>
    struct key_view
        : transform_view<
            AssociativeSequence,
            key_type<AssociativeSequence, _1>
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_KEY_VIEW_HPP

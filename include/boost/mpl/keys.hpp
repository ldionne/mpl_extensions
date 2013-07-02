/*!
 * @file
 * This file defines `boost::mpl::keys`.
 */

#ifndef BOOST_MPL_KEYS_HPP
#define BOOST_MPL_KEYS_HPP

#include <boost/mpl/key_type.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>


namespace boost { namespace mpl {
template <typename AssociativeSequence>
struct keys
    : transform_view<
        AssociativeSequence,
        key_type<AssociativeSequence, _1>
    >
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_KEYS_HPP

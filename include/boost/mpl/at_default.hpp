/*!
 * @file
 * This file defines `boost::mpl::at_default`.
 */

#ifndef BOOST_MPL_AT_DEFAULT_HPP
#define BOOST_MPL_AT_DEFAULT_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/identity.hpp>


namespace boost { namespace mpl {
template <typename Map, typename Key, typename Default>
struct lazy_at_default
    : eval_if<
        has_key<Map, Key>,
        at<Map, Key>,
        Default
    >
{ };

template <typename Map, typename Key, typename Default>
struct at_default
    : lazy_at_default<Map, Key, identity<Default>>
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_AT_DEFAULT_HPP

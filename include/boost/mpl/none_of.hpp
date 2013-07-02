/*!
 * @file
 * This file defines `boost::mpl::none_of`.
 */

#ifndef BOOST_MPL_NONE_OF_HPP
#define BOOST_MPL_NONE_OF_HPP

#include <boost/mpl/end.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace mpl {
template <typename Sequence, typename Pred>
struct none_of
    : is_same<
        typename end<Sequence>::type,
        typename find_if<Sequence, Pred>::type
    >
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_NONE_OF_HPP

/*!
 * @file
 * This file defines `boost::mpl::any_of`.
 */

#ifndef DYNO_DETAIL_MPL_ANY_OF_HPP
#define DYNO_DETAIL_MPL_ANY_OF_HPP

#include <boost/mpl/none_of.hpp>
#include <boost/mpl/not.hpp>


namespace boost { namespace mpl {
template <typename Sequence, typename Pred>
struct any_of
    : not_<
        none_of<Sequence, Pred>
    >
{ };
}} // end namespace boost::mpl

#endif // !DYNO_DETAIL_MPL_ANY_OF_HPP

/*!
 * @file
 * This file defines `boost::mpl::all_of`.
 */

#ifndef BOOST_MPL_ALL_OF_HPP
#define BOOST_MPL_ALL_OF_HPP

#include <boost/mpl/bind.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/none_of.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>


namespace boost { namespace mpl {
template <typename Sequence, typename Pred>
struct all_of
    : none_of<
        Sequence,
        bind<
            typename lambda<not_<_1> >::type,
            bind<typename lambda<Pred>::type, _1>
        >
    >
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_ALL_OF_HPP

/*!
 * @file
 * This file defines `boost::mpl::set_equal`.
 */

#ifndef BOOST_MPL_SET_EQUAL_HPP
#define BOOST_MPL_SET_EQUAL_HPP

#include <boost/mpl/all_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/any_of.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/size.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace mpl {
namespace set_equal_detail {
    template <typename FirstArg, typename Sequence, typename Pred>
    struct curry_any_of
        : any_of<
            Sequence, bind<Pred, FirstArg, _1>
        >
    { };
}

template <typename Set1, typename Set2, typename Pred = quote2<is_same> >
struct set_equal
    : and_<
        is_same<typename size<Set1>::type, typename size<Set2>::type>,
        all_of<
            Set1,
            set_equal_detail::curry_any_of<
                _1, Set2, typename lambda<Pred>::type
            >
        >
    >
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_SET_EQUAL_HPP

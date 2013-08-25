/*!
 * @file
 * This file defines `boost::mpl::is_eplaceholder`.
 */

#ifndef BOOST_MPL_IS_EPLACEHOLDER_HPP
#define BOOST_MPL_IS_EPLACEHOLDER_HPP

#include <boost/mpl/any_of.hpp>
#include <boost/mpl/equote.hpp>
#include <boost/mpl/is_placeholder.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/vector.hpp>


namespace boost { namespace mpl {
    template <typename T>
    struct is_eplaceholder
        : is_placeholder<T>
    { };

    template <typename F>
    struct is_eplaceholder_expression
        : is_eplaceholder<F>
    { };

    template <template <typename ...> class F, typename ...T>
    struct is_eplaceholder_expression<F<T...>>
        : or_<
            is_eplaceholder<F<T...>>,
            any_of<
                typename vector<T...>::type,
                equote<is_eplaceholder_expression>
            >
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_IS_EPLACEHOLDER_HPP

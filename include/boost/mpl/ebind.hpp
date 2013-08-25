/*!
 * @file
 * This file defines `boost::mpl::ebind`.
 */

#ifndef BOOST_MPL_EBIND_HPP
#define BOOST_MPL_EBIND_HPP

#include <boost/mpl/bind.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eapply_wrap.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_eplaceholder.hpp>


namespace boost { namespace mpl {
template <typename F, typename ...Placeholders>
struct ebind;

namespace ebind_detail {
    template <typename T>
    struct is_ebind_expression_or_eplaceholder
        : is_eplaceholder<T>
    { };

    template <typename F, typename ...Placeholders>
    struct is_ebind_expression_or_eplaceholder<ebind<F, Placeholders...>>
        : true_
    { };

    template <typename F, typename ...Placeholders>
    struct is_ebind_expression_or_eplaceholder<bind<F, Placeholders...>>
        : true_
    { };
} // end namespace ebind_detail

template <typename F, typename ...Placeholders>
struct ebind {
    template <typename ...Args>
    struct apply {
        template <typename X>
        using substitute = typename eval_if<
            ebind_detail::is_ebind_expression_or_eplaceholder<X>,
            eapply_wrap<X, Args...>,
            identity<X>
        >::type;

        using type = typename eapply_wrap<
            substitute<F>, substitute<Placeholders>...
        >::type;
    };
};
}} // end namespace boost::mpl

#endif // !BOOST_MPL_EBIND_HPP

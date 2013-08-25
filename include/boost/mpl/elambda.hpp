/*!
 * @file
 * This file defines `boost::mpl::elambda`.
 */

#ifndef BOOST_MPL_ELAMBDA_HPP
#define BOOST_MPL_ELAMBDA_HPP

#include <boost/mpl/ebind.hpp>
#include <boost/mpl/equote.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/is_eplaceholder.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/protect.hpp>


namespace boost { namespace mpl {
template <typename F>
struct elambda {
    using type = F;
};

namespace elambda_detail {
    template <template <typename ...> class F, typename ...T>
    struct lazy_protect_bind_quote {
        using type = protect<ebind<equote<F>, typename elambda<T>::type...>>;
    };
}

template <template <typename ...> class F, typename ...T>
struct elambda<F<T...>>
    : eval_if<or_<is_eplaceholder<F<T...>>,
                  not_<is_eplaceholder_expression<F<T...>>>>,
        identity<F<T...>>,
        elambda_detail::lazy_protect_bind_quote<F, T...>
    >
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_ELAMBDA_HPP

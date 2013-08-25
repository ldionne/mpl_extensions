/*!
 * @file
 * This file defines `boost::mpl::equote`.
 */

#ifndef BOOST_MPL_EQUOTE_HPP
#define BOOST_MPL_EQUOTE_HPP

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>


namespace boost { namespace mpl {
    namespace equote_detail { BOOST_MPL_HAS_XXX_TRAIT_DEF(type) }

    template <template <typename ...> class F>
    struct equote {
        template <typename ...Args>
        struct apply
            : eval_if<equote_detail::has_type<F<Args...>>,
                F<Args...>,
                identity<F<Args...>>
            >
        { };
    };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_EQUOTE_HPP

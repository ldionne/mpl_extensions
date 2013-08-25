/*!
 * @file
 * This file defines `boost::mpl::eapply_wrap`.
 */

#ifndef BOOST_MPL_EAPPLY_WRAP_HPP
#define BOOST_MPL_EAPPLY_WRAP_HPP

#include <boost/mpl/deferred_apply.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace mpl {
    namespace eapply_wrap_detail { BOOST_MPL_HAS_XXX_TRAIT_DEF(type) }

    template <typename F, typename ...Args>
    struct eapply_wrap
        : lazy_enable_if<
            eapply_wrap_detail::has_type<deferred_apply_wrap<F, Args...>>,
            deferred_apply_wrap<F, Args...>
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_EAPPLY_WRAP_HPP

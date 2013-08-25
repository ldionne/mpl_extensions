/*!
 * @file
 * This file defines `boost::mpl::eapply`.
 */

#ifndef BOOST_MPL_EAPPLY_HPP
#define BOOST_MPL_EAPPLY_HPP

#include <boost/mpl/eapply_wrap.hpp>
#include <boost/mpl/elambda.hpp>


namespace boost { namespace mpl {
    template <typename F, typename ...Args>
    struct eapply
        : eapply_wrap<typename elambda<F>::type, Args...>
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_EAPPLY_HPP

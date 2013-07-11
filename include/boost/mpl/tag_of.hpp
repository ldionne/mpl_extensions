/*!
 * @file
 * This file defines `boost::mpl::tag_of`.
 */

#ifndef BOOST_MPL_TAG_OF_HPP
#define BOOST_MPL_TAG_OF_HPP

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>


namespace boost { namespace mpl {
    namespace tag_of_detail {
        BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_mpl_tag, mpl::tag, false)

        template <typename T>
        struct tag_of {
            using type = typename T::mpl::tag;
        };
    }

    template <typename T>
    struct tag_of
        : eval_if<tag_of_detail::has_mpl_tag<T>,
            tag_of_detail::tag_of<T>,
            identity<T>
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_TAG_OF_HPP

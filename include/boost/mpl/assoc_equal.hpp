/*!
 * @file
 * This file defines `boost::mpl::set_equal`.
 */

#ifndef BOOST_MPL_SET_EQUAL_HPP
#define BOOST_MPL_SET_EQUAL_HPP

#include <boost/mpl/all_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/key_view.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_insert_range.hpp>
#include <boost/mpl/set_union.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace mpl {
namespace assoc_equal_detail {
    template <typename Sequence>
    using as_set = typename set_insert_range<
        typename set<>::type, Sequence
    >::type;

    template <typename Map1, typename Map2, typename Pred>
    struct make_assoc_equal {
        using Keys = typename set_union<
            as_set<key_view<Map1>>, as_set<key_view<Map2>>
        >::type;

        using type = all_of<
            Keys,
            and_<
                has_key<Map1, _1>,
                has_key<Map2, _1>,
                apply_wrap2<
                    typename lambda<Pred>::type,
                    at<Map1, _1>,
                    at<Map2, _1>
                >
            >
        >;
    };
} // end namespace assoc_equal_detail

template <typename Map1, typename Map2, typename Pred = quote2<is_same>>
struct assoc_equal
    : assoc_equal_detail::make_assoc_equal<Map1, Map2, Pred>::type
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_SET_EQUAL_HPP

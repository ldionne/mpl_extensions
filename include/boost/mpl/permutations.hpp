/*!
 * @file
 * Defines `boost::mpl::permutations`.
 */

#ifndef BOOST_MPL_PERMUTATIONS_HPP
#define BOOST_MPL_PERMUTATIONS_HPP

#include <boost/mpl/copy.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform.hpp>


namespace boost { namespace mpl {
namespace permutations_detail {
    template <typename Element, typename Sequence>
    struct helper;

    template <typename Sequence, unsigned long Size = size<Sequence>::value>
    struct permutations
        : fold<
            Sequence,
            list0<>,
            copy<helper<_2, Sequence>, front_inserter<_1>>
        >
    { };

    template <typename Sequence>
    struct permutations<Sequence, 1> {
        using type = list1<Sequence>;
    };

    template <typename Element, typename Sequence>
    struct helper
        : transform<
            typename permutations<
                typename remove<Sequence, Element>::type
            >::type,
            push_front<_1, Element>
        >
    { };
} // end namespace permutations_detail

/*!
 * Metafunction returning a sequence containing all the permutations of a
 * `Sequence`.
 *
 * @internal
 * We dispatch to `permutations_detail::permutations` to avoid exposing
 * the `Size` parameter in the interface.
 */
template <typename Sequence>
struct permutations
    : permutations_detail::permutations<Sequence>
{ };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_PERMUTATIONS_HPP
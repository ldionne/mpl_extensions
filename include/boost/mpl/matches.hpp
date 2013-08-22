/*!
 * @file
 * This file defines `boost::mpl::matches`.
 */

#ifndef BOOST_MPL_MATCHES_HPP
#define BOOST_MPL_MATCHES_HPP

#include <boost/mpl/any_of.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace mpl {
namespace match {
    //! Matches anything.
    struct any;

    // Matches iff any of the patterns match.
    template <typename ...Patterns>
    struct any_of;

    //! Matches iff the pattern does not match.
    template <typename Pattern>
    struct not_;

    //! Matches iff the `LambdaExpression` returns true.
    template <typename LambdaExpression>
    struct if_;
} // end namespace match

/*!
 * Metafunction returning whether a type matches a given pattern.
 *
 * By default, a type matches a pattern if they are the same. Two template
 * types match if their template parameters match side by side.
 *
 *
 * @internal
 * We use `is_same` because specializing `matches<T, T>` makes it an ambiguous
 * specialization with the `Node<...>` specialization when `Children1` is the
 * same as `Children2`.
 */
template <typename T, typename Pattern>
struct matches
    : is_same<T, Pattern>
{ };

template <template <typename ...> class Node,
          typename ...Children1,
          typename ...Children2>
struct matches<Node<Children1...>, Node<Children2...>>
    : equal<
        typename vector<Children1...>::type,
        typename vector<Children2...>::type,
        matches<_1, _2>
    >
{ };

template <typename T>
struct matches<T, match::any>
    : true_
{ };

template <typename T, typename ...Patterns>
struct matches<T, match::any_of<Patterns...>>
    : any_of<
        typename vector<Patterns...>::type,
        matches<T, _1>
    >
{ };

template <typename T, typename Pattern>
struct matches<T, match::not_<Pattern>>
    : not_<matches<T, Pattern>>
{ };

template <typename T, typename LambdaExpression>
struct matches<T, match::if_<LambdaExpression>>
    : bool_<apply<LambdaExpression, T>::type::value>
{ };

namespace matches_detail {
    template <typename FuncDecl>
    struct assert_matches_impl;

    template <typename Ret, typename T, typename Pattern>
    struct assert_matches_impl<Ret (T, Pattern)>
        : matches<T, Pattern>
    { };
} // end namespace matches_detail

#define BOOST_MPL_ASSERT_MATCHES(FuncParams)                                \
    static_assert(                                                          \
        ::boost::mpl::matches_detail::assert_matches_impl<                  \
            void FuncParams                                                 \
        >::value,                                                           \
        #FuncParams                                                         \
    )                                                                       \
/**/

#define BOOST_MPL_ASSERT_MATCHES_NOT(FuncParams)                            \
    static_assert(                                                          \
      ! ::boost::mpl::matches_detail::assert_matches_impl<                  \
            void FuncParams                                                 \
        >::value,                                                           \
        #FuncParams                                                         \
    )                                                                       \
/**/
}} // end namespace boost::mpl

#endif // !BOOST_MPL_MATCHES_HPP

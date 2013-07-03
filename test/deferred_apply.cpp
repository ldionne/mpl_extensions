/*!
 * @file
 * This file contains unit tests for `boost::mpl::deferred_apply` and
 * `boost::mpl::deferred_apply_wrap`.
 */

#include <boost/mpl/deferred_apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost;

struct non_template_apply { struct apply; };
struct template_apply { template <typename ...> struct apply; };

// deferred_apply_wrap
static_assert(is_same<
    mpl::deferred_apply_wrap<non_template_apply>::type,
    non_template_apply::apply
>::value, "");

static_assert(is_same<
    mpl::deferred_apply_wrap<template_apply>::type,
    template_apply::apply<>
>::value, "");

static_assert(is_same<
    mpl::deferred_apply_wrap<template_apply, struct a0>::type,
    template_apply::apply<struct a0>
>::value, "");

static_assert(is_same<
    mpl::deferred_apply_wrap<template_apply, struct a0, struct a1>::type,
    template_apply::apply<struct a0, struct a1>
>::value, "");

// deferred_apply
// note: We need to use vectorN because the MPL does not support variadic
//       lambda expressions.
static_assert(is_same<
    mpl::deferred_apply<mpl::vector1<mpl::_1>, int>::type::type,
    mpl::vector1<int>
>::value, "");

static_assert(is_same<
    mpl::deferred_apply<
        mpl::vector3<mpl::_1, mpl::_2, mpl::_3>, int, float, char
    >::type::type,
    mpl::vector3<int, float, char>
>::value, "");


int main() { }

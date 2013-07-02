/*!
 * @file
 * This file contains an adaptation of the Boost.Fusion pair for use within
 * the Boost.MPL.
 */

#ifndef DYNO_DETAIL_MPL_FUSION_PAIR_HPP
#define DYNO_DETAIL_MPL_FUSION_PAIR_HPP

#include <boost/fusion/include/pair.hpp>
#include <boost/mpl/pair.hpp>


namespace boost { namespace mpl {
    template <typename First, typename Second>
    struct first<fusion::pair<First, Second> >
        : fusion::result_of::first<fusion::pair<First, Second> >
    { };

    template <typename First, typename Second>
    struct first<fusion::pair<First, Second> const>
        : fusion::result_of::first<fusion::pair<First, Second> const>
    { };

    template <typename First, typename Second>
    struct second<fusion::pair<First, Second> >
        : fusion::result_of::second<fusion::pair<First, Second> >
    { };

    template <typename First, typename Second>
    struct second<fusion::pair<First, Second> const>
        : fusion::result_of::second<fusion::pair<First, Second> const>
    { };
}}

#endif // !DYNO_DETAIL_MPL_FUSION_PAIR_HPP

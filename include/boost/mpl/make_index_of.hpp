/*!
 * @file
 * This file defines `boost::mpl::make_index_of`.
 */

#ifndef BOOST_MPL_MAKE_INDEX_OF_HPP
#define BOOST_MPL_MAKE_INDEX_OF_HPP

#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>


namespace boost { namespace mpl {
    template <typename Sequence,
              typename MakeKey = quote1<identity>,
              typename MakeValue = quote1<identity>>
    struct make_index_of
        : fold<
            Sequence,
            map<>,
            insert<_1,
                pair<
                    apply_wrap1<typename lambda<MakeKey>::type, _2>,
                    apply_wrap1<typename lambda<MakeValue>::type, _2>
                >
            >
        >
    { };
}} // end namespace boost::mpl

#endif // !BOOST_MPL_MAKE_INDEX_OF_HPP

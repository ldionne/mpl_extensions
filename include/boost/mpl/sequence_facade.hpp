/*!
 * @file
 * This file defines `boost::mpl::sequence_facade`.
 */

#ifndef BOOST_MPL_SEQUENCE_FACADE_HPP
#define BOOST_MPL_SEQUENCE_FACADE_HPP

#include <boost/mpl/at.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {
    struct sequence_facade {
        struct tag;
    };

    namespace sequence_facade_detail {
        struct unspecialized_tag;

        template <template <typename ...> class Intrinsic, typename ...Args>
        struct use_default
            : Intrinsic<unspecialized_tag>::template apply<Args...>
        { };
    } // end namespace sequence_facade_detail

#define BOOST_I_MPL_FORWARD_INTRINSIC(intrinsic)                            \
    template <>                                                             \
    struct BOOST_PP_CAT(intrinsic, _impl)<sequence_facade::tag> {           \
    private:                                                                \
        template <typename Sequence, typename ...Args>                      \
        static typename Sequence::template intrinsic<Args...> pick(int);    \
                                                                            \
        template <typename Sequence>                                        \
        static typename Sequence::intrinsic pick(int);                      \
                                                                            \
        template <typename Sequence, typename ...Args>                      \
        static sequence_facade_detail::use_default<                         \
            mpl::BOOST_PP_CAT(intrinsic, _impl), Sequence, Args...          \
        > pick(...);                                                        \
                                                                            \
    public:                                                                 \
        template <typename Sequence, typename ...Args>                      \
        struct apply                                                        \
            : decltype(pick<Sequence, Args...>(int{}))                      \
        { };                                                                \
    };                                                                      \
/**/
    BOOST_I_MPL_FORWARD_INTRINSIC(at)
    BOOST_I_MPL_FORWARD_INTRINSIC(back)
    BOOST_I_MPL_FORWARD_INTRINSIC(begin)
    BOOST_I_MPL_FORWARD_INTRINSIC(clear)
    BOOST_I_MPL_FORWARD_INTRINSIC(empty)
    BOOST_I_MPL_FORWARD_INTRINSIC(end)
    BOOST_I_MPL_FORWARD_INTRINSIC(erase)
    BOOST_I_MPL_FORWARD_INTRINSIC(erase_key)
    BOOST_I_MPL_FORWARD_INTRINSIC(front)
    BOOST_I_MPL_FORWARD_INTRINSIC(has_key)
    BOOST_I_MPL_FORWARD_INTRINSIC(insert)
    BOOST_I_MPL_FORWARD_INTRINSIC(insert_range)
    BOOST_I_MPL_FORWARD_INTRINSIC(key_type)
    BOOST_I_MPL_FORWARD_INTRINSIC(order)
    BOOST_I_MPL_FORWARD_INTRINSIC(pop_back)
    BOOST_I_MPL_FORWARD_INTRINSIC(pop_front)
    BOOST_I_MPL_FORWARD_INTRINSIC(push_back)
    BOOST_I_MPL_FORWARD_INTRINSIC(push_front)
    BOOST_I_MPL_FORWARD_INTRINSIC(size)
    BOOST_I_MPL_FORWARD_INTRINSIC(value_type)
#undef BOOST_I_MPL_FORWARD_INTRINSIC
}} // end namespace boost::mpl

#endif // !BOOST_MPL_SEQUENCE_FACADE_HPP

/*!
 * @file
 * This file contains unit tests for `boost::mpl::sequence_facade`.
 */

#include <boost/mpl/sequence_facade.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost;

template <typename ...T>
struct forward_sequence : mpl::sequence_facade {
    struct begin : mpl::begin<typename mpl::vector<T...>::type> { };
    struct end : mpl::end<typename mpl::vector<T...>::type> { };
};


static_assert(mpl::size<forward_sequence<int, float>>::value == 2, "");

static_assert(is_same<
    mpl::front<forward_sequence<int, float>>::type, int
>::value, "");

static_assert(!mpl::empty<forward_sequence<int, float>>::value, "");
static_assert(mpl::empty<forward_sequence<>>::value, "");


int main() { }

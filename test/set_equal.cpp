/*!
 * @file
 * This file contains unit tests for `boost::mpl::set_equal`.
 */

#include <boost/mpl/set_equal.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost;
using namespace boost::mpl;

static_assert(set_equal<set<>, set<>>::value, "");
static_assert(!set_equal<set<char>, set<>>::value, "");
static_assert(!set_equal<set<>, set<char>>::value, "");

static_assert(set_equal<set<char>, set<char>>::value, "");
static_assert(!set_equal<set<char, float>, set<char>>::value, "");
static_assert(!set_equal<set<char>, set<float, char>>::value, "");

static_assert(set_equal<
    set<int, float, char>, set<float, int, char>
>::value, "");
static_assert(!set_equal<
    set<int, float>, set<float, int, char>
>::value, "");

static_assert(set_equal<
    set<vector<int, float>, vector<double, void>>,
    set<list<double, void>, list<int, float>>,
    equal<_1, _2, quote2<is_same>>
>::value, "");


int main() { }

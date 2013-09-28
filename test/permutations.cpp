/*!
 * @file
 * Contains unit tests for `boost::mpl::permutations`.
 */

#include <boost/mpl/permutations.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/set_equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


template <typename Sequence, typename Permutations>
struct assert_permutations {
    BOOST_MPL_ASSERT((boost::mpl::set_equal<
        typename boost::mpl::permutations<Sequence>::type,
        Permutations,
        boost::mpl::equal<
            boost::mpl::_1, boost::mpl::_2,
            boost::mpl::quote2<boost::is_same>
        >
    >));
};

using namespace boost::mpl;
template <int> struct t;

// empty
template struct assert_permutations<
    vector<>,
    set<>
>;

// 1 element
template struct assert_permutations<
    vector<t<0> >,
    set<
        vector<t<0> >
    >
>;

// 2 elements
template struct assert_permutations<
    vector<t<0>, t<1> >,
    set<
        vector<t<0>, t<1> >,
        vector<t<1>, t<0> >
    >
>;

// 3 elements
template struct assert_permutations<
    vector<t<0>, t<1>, t<2> >,
    set<
        vector<t<0>, t<1>, t<2> >,
        vector<t<0>, t<2>, t<1> >,

        vector<t<1>, t<0>, t<2> >,
        vector<t<1>, t<2>, t<0> >,

        vector<t<2>, t<0>, t<1> >,
        vector<t<2>, t<1>, t<0> >
    >
>;


int main() { }

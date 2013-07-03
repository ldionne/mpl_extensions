/*!
 * @file
 * This file contains unit tests for `boost::mpl::matches`.
 */

#include <boost/mpl/matches.hpp>


using namespace boost::mpl;

struct Leaf;
template <typename...> struct Node;

BOOST_MPL_ASSERT_MATCHES((Leaf, Leaf));
BOOST_MPL_ASSERT_MATCHES_NOT((Leaf, struct some_other_type));
BOOST_MPL_ASSERT_MATCHES((Leaf, match_any));

BOOST_MPL_ASSERT_MATCHES((Node<Leaf>, Node<Leaf>));
BOOST_MPL_ASSERT_MATCHES((Node<Leaf>, Node<match_any>));
BOOST_MPL_ASSERT_MATCHES_NOT((Node<>, Node<match_any>));

BOOST_MPL_ASSERT_MATCHES((
    Node<Node<Leaf>, Node<>, Node<Leaf>>,
    Node<Node<match_any>, Node<>, Node<Leaf>>
));

BOOST_MPL_ASSERT_MATCHES_NOT((
    Node<Node<>, Node<>>,
    Node<Node<Leaf>, Node<>>
));

BOOST_MPL_ASSERT_MATCHES_NOT((
    struct some_type,
    match_all_of<struct another_type, struct some_type>
));

BOOST_MPL_ASSERT_MATCHES((
    Node<struct leaf2, struct leaf0, struct leaf1>,
    Node<match_all_of<struct leaf0, struct leaf1, struct leaf2>>
));


int main() { }

/*!
 * @file
 * This file contains unit tests for `boost::mpl::matches`.
 */

#include <boost/mpl/matches.hpp>


using namespace boost::mpl;

struct Leaf;
template <typename ...> struct Node;

// Pattern matching with non-template types
BOOST_MPL_ASSERT_MATCHES((Leaf, Leaf));
BOOST_MPL_ASSERT_MATCHES_NOT((Leaf, struct some_other_type));

// Pattern matching with template types
BOOST_MPL_ASSERT_MATCHES((Node<Leaf>, Node<Leaf>));
BOOST_MPL_ASSERT_MATCHES_NOT((Node<Leaf>, Node<struct other>));
BOOST_MPL_ASSERT_MATCHES((
    Node<Node<Leaf>, struct X>,
    Node<Node<Leaf>, struct X>
));
BOOST_MPL_ASSERT_MATCHES_NOT((
    Node<Node<Leaf>, struct X>,
    Node<Node<Leaf>, struct Y>
));
BOOST_MPL_ASSERT_MATCHES_NOT((
    Node<Node<>, Node<>>,
    Node<Node<Leaf>, Node<>>
));

// Pattern matching with the `match::any` keyword.
BOOST_MPL_ASSERT_MATCHES((Leaf, match::any));
BOOST_MPL_ASSERT_MATCHES((Node<>, match::any));
BOOST_MPL_ASSERT_MATCHES((Node<Leaf>, match::any));
// note: the `match::any` on the left should not be considered as a keyword.
BOOST_MPL_ASSERT_MATCHES((Node<match::any>, match::any));
BOOST_MPL_ASSERT_MATCHES((Node<Leaf>, Node<match::any>));
BOOST_MPL_ASSERT_MATCHES_NOT((Node<>, Node<match::any>));
BOOST_MPL_ASSERT_MATCHES((
    Node<Node<Leaf>, Node<>, Node<Leaf>>,
    Node<Node<match::any>, Node<>, Node<Leaf>>
));


int main() { }

/*!
 * @file
 * This file defines unit tests for `boost::mpl::make_index_of`.
 */

#include <boost/mpl/make_index_of.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>


using namespace boost::mpl;

namespace population_scenario {
    template <typename Person>
    struct name_of {
        using type = typename Person::name;
    };

    template <typename Person>
    struct phone_of {
        using type = typename Person::phone;
    };

    template <typename Name, typename Phone>
    struct person {
        using name = Name;
        using phone = Phone;
    };

    using Population = vector<
        person<struct John, struct _123>,
        person<struct Joe, struct _456>,
        person<struct Jane, struct _789>
    >;

    using PhoneBook = make_index_of<
        Population, name_of<_1>, phone_of<_1>
    >::type;

    static_assert(boost::is_same<
        at<PhoneBook, struct John>::type,
        struct _123
    >::value, "");
    static_assert(boost::is_same<
        at<PhoneBook, struct Joe>::type,
        struct _456
    >::value, "");
    static_assert(boost::is_same<
        at<PhoneBook, struct Jane>::type,
        struct _789
    >::value, "");
}


int main() { }

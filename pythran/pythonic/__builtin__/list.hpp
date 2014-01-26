#ifndef PYTHONIC_BUILTIN_LIST_HPP
#define PYTHONIC_BUILTIN_LIST_HPP

#include "pythonic/types/list.hpp"

#include "pythonic/utils/proxy.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace __builtin__ {

        types::empty_list list() {
            return types::empty_list();
        }
        types::empty_list list(types::empty_list) {
            return types::empty_list();
        }

        template <class Iterable>
            types::list<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::value_type> list(Iterable && t) {
                return types::list<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::value_type>(t.begin(), t.end());
            } 

        /*
           template <class... Types>
           types::list<typename std::tuple_element<0,std::tuple<Types...>>::type>
           list(std::tuple<Types...> const & other) {
           auto res =  types::list<typename std::tuple_element<0,std::tuple<Types...>>::type > (std::tuple_size<std::tuple<Types...>>::value);
           tuple_dump(other, res, ::pythonic::int_<sizeof...(Types)-1>());
           return res;
           }
           */

        PROXY(pythonic::__builtin__,list);

    }

}

#endif

#ifndef PYTHONIC_BUILTIN_LIST_HPP
#define PYTHONIC_BUILTIN_LIST_HPP

#include "pythonic/include/__builtin__/list.hpp"

#include "pythonic/types/list.hpp"
#include "pythonic/utils/proxy.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace __builtin__ {

        namespace anonymous {

            inline types::empty_list list()
            {
                return types::empty_list();
            }

            inline types::empty_list list(types::empty_list)
            {
                return types::empty_list();
            }

            template <class Iterable>
                types::list<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::value_type>
                list(Iterable && t)
                {
                    return types::list<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::value_type>(t.begin(), t.end());
                } 

        }

        PROXY_IMPL(pythonic::__builtin__::anonymous, list);

    }

}

#endif

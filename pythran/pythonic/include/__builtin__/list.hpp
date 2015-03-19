#ifndef PYTHONIC_INCLUDE_BUILTIN_LIST_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LIST_HPP

#include "pythonic/types/list.hpp"

#include "pythonic/utils/proxy.hpp"

#include <iterator>
#include <type_traits>

namespace pythonic {

    namespace __builtin__ {

        namespace {

            inline types::empty_list list();
            inline types::empty_list list(types::empty_list);

            template <class Iterable>
                types::list<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::value_type>
                list(Iterable && t);

        }

        PROXY_DECL(pythonic::__builtin__,list);

    }

}

#endif

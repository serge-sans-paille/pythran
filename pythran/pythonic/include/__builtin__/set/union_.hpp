#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_UNION_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_UNION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace set {

            template<typename T, typename... Types>
                auto union_(types::set<T> const& set, Types const&... others)
                -> decltype(set.union_(others...));

            template<typename... Types>
                auto union_(types::empty_set const& init, Types const&... others)
                -> decltype(union_(others...));

            template<typename T>
                types::set<T>
                union_(types::set<T> const& set);

            template<typename T>
                typename __combined<types::empty_set, T>::type
                union_(T const& set);

            template<typename T>
                types::set<T>
                union_(types::set<T> && set);

            types::empty_set
            union_(types::empty_set const& init);

            PROXY_DECL(pythonic::__builtin__::set, union_);

        }

    }

}
#endif 

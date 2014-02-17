#ifndef PYTHONIC_SET_UNION_HPP
#define PYTHONIC_SET_UNION_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/set.hpp"

namespace pythonic {

    namespace __set__ {
        template<typename T, typename... Types>
            auto union_(types::set<T> const& set, Types const&... others) -> decltype(set.union_(others...))
            {
                return set.union_(others...);
            }
        template<typename... Types>
            auto union_(types::empty_set const& init, Types const&... others) -> decltype(union_(others...))
            {
                return union_(others...);
            }
        template<typename T>
            types::set<T> union_(types::set<T> const& set){
                return set;
            }
        template<typename T>
            typename __combined<types::empty_set, T>::type union_(T const& set){
                return typename __combined<types::empty_set, T>::type(set);
            }
        template<typename T>
            types::set<T> union_(types::set<T> && set){
                return std::forward(set);
            }
        types::empty_set union_(types::empty_set const& init){
            return types::empty_set();
        }
        PROXY(pythonic::__set__, union_);

    }

}

#endif


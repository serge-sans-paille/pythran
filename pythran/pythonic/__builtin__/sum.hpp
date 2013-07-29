#ifndef PYTHONIC_BUILTIN_SUM_HPP
#define PYTHONIC_BUILTIN_SUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"

#include <utility>
#include <algorithm>

namespace pythonic {

    namespace __builtin__ {

        template<class Iterable, class T>
            auto sum(Iterable s, T start) -> decltype(start+std::declval<typename Iterable::iterator::value_type>())
            {
                return std::accumulate(s.begin(), s.end(), (decltype(start+*s.begin()))start);
            }
        template<class Iterable>
            typename Iterable::iterator::value_type sum(Iterable s)
            {
                return sum(s,0L);
            }

        template<class Tuple>
            auto tuple_sum(Tuple const& t, utils::int_<0>) -> decltype(std::get<0>(t)) {
                return std::get<0>(t);
            }

        template<class Tuple, size_t I>
            auto tuple_sum(Tuple const& t, utils::int_<I>) -> typename std::remove_reference<decltype(std::get<I>(t))>::type {
                return std::get<I>(t) + tuple_sum(t, utils::int_<I-1>());
            }


        template<class... Types>
            auto sum(std::tuple<Types...> const & t) -> decltype(tuple_sum(t, utils::int_<sizeof...(Types)-1>())) {
                return tuple_sum(t, utils::int_<sizeof...(Types)-1>());
            }

        PROXY(pythonic::__builtin__, sum);

    }

}


#endif

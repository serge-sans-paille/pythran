#ifndef PYTHONIC_BUILTIN_SUM_HPP
#define PYTHONIC_BUILTIN_SUM_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/assignable.hpp"
#include "pythonic/utils/int_.hpp"

#include <utility>
#include <algorithm>

namespace pythonic {

    namespace __builtin__ {

        template<class Iterable, class T>
            auto sum(Iterable s, T start) -> decltype(std::accumulate(s.begin(), s.end(), static_cast<typename assignable<decltype(start+*s.begin())>::type>(start)))
            {
                return std::accumulate(s.begin(), s.end(), static_cast<typename assignable<decltype(start+*s.begin())>::type>(start));
            }

        template<class Iterable>
            auto sum(Iterable s) -> decltype(sum(s, 0L))
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

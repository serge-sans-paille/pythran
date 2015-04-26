#ifndef PYTHONIC_BUILTIN_MAX_HPP
#define PYTHONIC_BUILTIN_MAX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/max.hpp"

#include <utility>
#include <algorithm>

namespace pythonic {

    namespace __builtin__ {

        template <class T0>
            typename _max<true, T0>::result_type
            _max<true, T0>::operator()(T0 && t)
            {
                return *std::max_element(t.begin(), t.end());
            }

        template<class T0>
            typename _max<false, T0>::result_type
            _max<false, T0>::operator()( T0 const & t )
            {
                return t;
            }

        template <class T0, class T1>
            typename _max<false, T0, T1>::result_type
            _max<false, T0, T1>::operator()(T0 const & t0, T1 const& t1)
            {
                return t0 > t1? t0: t1;
            }

        template <class T0, class... Types>
            typename _max<false, T0, Types...>::result_type
            _max<false, T0, Types...>::operator()(T0 const & t0, Types const&... values)
            {
                auto t1 = _max<false, Types...>()(values...);
                return t0 > t1 ? t0 : t1;
            }

        template <class... Types>
            typename _max<  sizeof...(Types) == 1, Types...>::result_type
            max(Types &&... values)
            {
                return _max< sizeof...(Types) ==1, Types...>()(std::forward<Types>(values)...);
            }

        PROXY_IMPL(pythonic::__builtin__,max);
    }

}

#endif

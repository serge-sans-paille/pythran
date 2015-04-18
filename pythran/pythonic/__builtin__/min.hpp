#ifndef PYTHONIC_BUILTIN_MIN_HPP
#define PYTHONIC_BUILTIN_MIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/include/__builtin__/min.hpp"

#include <utility>
#include <algorithm>

namespace pythonic {

    namespace __builtin__ {

        template <class T0>
            typename _min<true, T0>::result_type
            _min<true, T0>::operator()(T0 && t)
            {
                return *std::min_element(t.begin(), t.end());
            }

        template<class T0>
            typename _min<false, T0>::result_type
            _min<false, T0>::operator()(T0 const & t)
            {
                return t;
            }

        template <class T0, class T1>
            typename _min<false, T0, T1>::result_type
            _min<false, T0, T1>::operator()(T0 const & t0, T1 const& t1)
            {
                return t0<t1? t0: t1;
            }

        template <class T0, class... Types>
            typename _min<false, T0, Types...>::result_type
            _min<false, T0, Types...>::operator()(T0 const & t0, Types const&... values)
            {
                auto t1 = _min<false, Types...>()(values...);
                return t0 < t1 ? t0 : t1;
            }

        template <class... Types>
            typename _min<  sizeof...(Types) == 1, Types...>::result_type
            min(Types &&... values)
            {
                return _min< sizeof...(Types) ==1, Types...>()(std::forward<Types>(values)...);
            }

        PROXY_IMPL(pythonic::__builtin__,min);

    }

}

#endif

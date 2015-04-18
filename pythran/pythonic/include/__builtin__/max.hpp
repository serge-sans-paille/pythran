#ifndef PYTHONIC_INCLUDE_BUILTIN_MAX_HPP
#define PYTHONIC_INCLUDE_BUILTIN_MAX_HPP

#include "pythonic/utils/proxy.hpp"

#include <utility>

namespace pythonic {

    namespace __builtin__ {
        template <bool n, class... Types>
            struct _max;

        template <class T0>
            struct _max<true, T0>
            {
                using result_type = typename std::remove_reference<T0>::type::iterator::value_type;
                result_type operator()(T0 && t);
            };

        template<class T0>
            struct _max<false, T0>
            {
                using result_type = T0;
                result_type operator()(T0 const & t);
            };

        template <class T0, class T1>
            struct _max<false, T0, T1>
            {
                using result_type = typename std::remove_cv<typename std::remove_reference<typename __combined<T0, T1>::type>::type>::type;
                result_type operator()(T0 const & t0, T1 const& t1);
            };

        template <class T0, class... Types>
            struct _max<false, T0, Types...>
            {
                using result_type = typename _max<false, T0, typename _max<false, Types...>::result_type>::result_type;
                result_type operator()(T0 const & t0, Types const&... values);
            };

        template <class... Types>
            typename _max<  sizeof...(Types) == 1, Types...>::result_type
            max(Types &&... values);

        PROXY_DECL(pythonic::__builtin__, max);

    }

}

#endif

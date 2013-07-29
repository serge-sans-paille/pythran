#ifndef PYTHONIC_BUILTIN_MAX_HPP
#define PYTHONIC_BUILTIN_MAX_HPP

#include "pythonic/utils/proxy.hpp"

#include <utility>

namespace pythonic {

    namespace __builtin__ {
        template <int n, class... Types>
            struct _max;

        template <class T0>
            struct _max<true, T0> {
                typedef typename std::remove_reference<T0>::type::iterator::value_type result_type;
                result_type operator()(T0 && t) {
                    return *std::max_element(t.begin(), t.end());
                }
            };

        template<class T0>
            struct _max<false, T0> {
                typedef T0 result_type;
                result_type operator()( T0 const & t ) {
                    return t;
                }
            };

        template <class T0, class T1>
            struct _max<false, T0, T1> {
                typedef decltype(std::declval<T0>() + std::declval<T1>()) result_type;
                result_type operator()(T0 const & t0, T1 const& t1) {
                    return t0 > t1? t0: t1;
                }

            };

        template <class T0, class... Types>
            struct _max<false, T0, Types...> {

                typedef typename _max<false, T0, typename _max<false, Types...>::result_type>::result_type result_type;

                result_type operator()(T0 const & t0, Types const&... values)
                {
                    auto t1 = _max<false, Types...>()(values...);
                    return t0 > t1 ? t0 : t1;
                }
            };

        template <class... Types>
            typename _max<  sizeof...(Types) == 1, Types...>::result_type max(Types &&... values) {
                return _max< sizeof...(Types) ==1, Types...>()(std::forward<Types>(values)...);
            }
        PROXY(pythonic::__builtin__,max);

    }

}

#endif


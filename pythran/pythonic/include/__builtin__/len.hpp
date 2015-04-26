#ifndef PYTHONIC_INCLUDE_BUILTIN_LEN_HPP
#define PYTHONIC_INCLUDE_BUILTIN_LEN_HPP

#include "pythonic/types/traits.hpp"
#include "pythonic/utils/proxy.hpp"

#include <iterator>

namespace pythonic {

    namespace __builtin__ {

        template <class T, class I, bool F>
            struct _len
            {
                long operator()(T const &t);
            };

        template <class T>
            struct _len<T, std::random_access_iterator_tag, false>
            {
                long operator()(T const &t);
            };

        template <class T, class F>
            struct _len<T, F, true>
            {
                long operator()(T const &t);
            };

        template <class... Types>
            long len(std::tuple<Types...> const&);

        long len(char);

        template <class T>
            long len(T const &t);

        PROXY_DECL(pythonic::__builtin__,len);

    }

}
#endif

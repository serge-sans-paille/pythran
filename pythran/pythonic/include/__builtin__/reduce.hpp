#ifndef PYTHONIC_INCLUDE_BUILTIN_REDUCE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_REDUCE_HPP

#include "pythonic/utils/proxy.hpp"

#include <algorithm>
#include <utility>

namespace pythonic {

    namespace __builtin__ {

        template<class Iterable, class Operator>
            auto reduce(Operator op, Iterable s)
            -> decltype(op(std::declval< typename Iterable::iterator::value_type >(), std::declval< typename Iterable::iterator::value_type >()));

        template<class Iterable, class Operator, class T>
            auto reduce(Operator op, Iterable s, T const & init)
            -> decltype(std::accumulate(s.begin(), s.end(), static_cast<decltype(op(init,std::declval<typename Iterable::iterator::value_type>()))>(init), op));

        PROXY_DECL(pythonic::__builtin__,reduce);

    }

}

#endif

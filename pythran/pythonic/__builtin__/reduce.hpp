#ifndef PYTHONIC_BUILTIN_REDUCE_HPP
#define PYTHONIC_BUILTIN_REDUCE_HPP

#include "pythonic/utils/proxy.hpp"

#include <utility>
#include <algorithm>

namespace pythonic {

    namespace __builtin__ {

        template<class Iterable, class Operator>
            auto reduce(Operator op, Iterable s)
            -> decltype( op( std::declval< typename Iterable::iterator::value_type >(), std::declval< typename Iterable::iterator::value_type >() ) )
            {
                auto iter = s.begin();
                auto r = *iter;
                ++iter;
                if(iter!=s.end())
                    return  std::accumulate(iter, s.end(), r, op);
                else
                    return r;
            }
        template<class Iterable, class Operator, class T>
            auto reduce(Operator op, Iterable s, T const & init)
            -> decltype( std::accumulate(s.begin(), s.end(), static_cast<decltype(op(init,std::declval<typename Iterable::iterator::value_type>()))>(init), op) )
            {
                return std::accumulate(s.begin(), s.end(), static_cast<decltype(op(init,std::declval<typename Iterable::iterator::value_type>()))>(init), op);
            }
        PROXY(pythonic::__builtin__,reduce);

    }

}

#endif

#ifndef PYTHONIC_FUNCTOOLS_PARTIAL_HPP
#define PYTHONIC_FUNCTOOLS_PARTIAL_HPP

#include "pythonic/include/functools/partial.hpp"
#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/seq.hpp"

#include <utility>

namespace pythonic {

    namespace functools {

        namespace {

            template<typename... ClosureTypes>
                task<ClosureTypes...>::task() :
                    closure()
                {}

            template<typename... ClosureTypes>
                task<ClosureTypes...>::task(ClosureTypes... types) :
                    closure(types...)
                {}

            template<typename... ClosureTypes>
            template<int...S, typename... Types>
                auto task<ClosureTypes...>::call(utils::seq<S...>, Types &&... types) const
                -> decltype(std::get<0>(closure)(std::get<S>(closure)..., std::forward<Types>(types)...))
                {
                    return std::get<0>(closure)(std::get<S>(closure)..., std::forward<Types>(types)...);
                }

            template<typename... ClosureTypes>
            template<typename... Types>
                auto task<ClosureTypes...>::operator()(Types &&... types) const
                -> decltype(this->call(typename utils::gens<sizeof...(ClosureTypes)>::type(), std::forward<Types>(types)...))
                {
                    return call(typename utils::gens<sizeof...(ClosureTypes)>::type(), std::forward<Types>(types)...);
                }
        }

        template<typename... Types>
            // remove references as closure capture the env by copy
            task<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...>
            partial(Types &&... types)
            {
                return task<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...>(std::forward<Types>(types)...);
            }

        PROXY_IMPL(pythonic::functools, partial);

    }

}

#endif

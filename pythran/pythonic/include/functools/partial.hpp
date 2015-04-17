#ifndef PYTHONIC_INCLUDE_FUNCTOOLS_PARTIAL_HPP
#define PYTHONIC_INCLUDE_FUNCTOOLS_PARTIAL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/seq.hpp"

#include <utility>

namespace pythonic {

    namespace functools {

        namespace {

            /* a task that captures its environnment for later call */
            template<typename... ClosureTypes>
                struct task
                {

                    mutable std::tuple<ClosureTypes...> closure; // closure associated to the task, mutable because pythran assumes all function calls are const

                    task();
                    task(ClosureTypes... types);

                    template<int...S, typename... Types>
                        auto call(utils::seq<S...>, Types &&... types) const
                        -> decltype(std::get<0>(closure)(std::get<S+1>(closure)..., std::forward<Types>(types)...));

                    template<typename... Types>
                        auto operator()(Types &&... types) const
                        -> decltype(this->call(typename utils::gens<sizeof...(ClosureTypes)-1>::type(), std::forward<Types>(types)...));
                };
        }

        template<typename... Types>
            // remove references as closure capture the env by copy
            task<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...>
            partial(Types &&... types);

        PROXY_DECL(pythonic::functools, partial);

    }

}

#endif

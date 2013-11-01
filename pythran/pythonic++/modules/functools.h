#ifndef PYTHONIC_MODULE_FUNCTOOLS_H
#define PYTHONIC_MODULE_FUNCTOOLS_H
namespace pythonic {

    namespace functools {

        namespace {

            template<int ...>
                struct seq { };

            template<int N, int ...S>
                struct gens : gens<N-1, N-1, S...> { };

            template<int ...S>
                struct gens<1, S...> {
                    typedef seq<S...> type;
                };


            /* a task that captures its environnment for later call */
            template<typename... ClosureTypes>
                struct task {

                    mutable std::tuple<ClosureTypes...> closure; // closure associated to the task, mutable because pythran assumes all function calls are const

                    task() : closure()
                    {
                    }

                    task(ClosureTypes... types) : closure(types...)
                    {
                    }

                    template<int...S, typename... Types>
                        auto call(seq<S...>, Types &&... types) const
                        -> decltype(std::get<0>(closure)(std::get<S>(closure)..., std::forward<Types>(types)...))
                        {
                            return std::get<0>(closure)(std::get<S>(closure)..., std::forward<Types>(types)...);
                        }

                    template<typename... Types>
                        auto operator()(Types &&... types) const
                        -> decltype(this->call(typename gens<sizeof...(ClosureTypes)>::type(), std::forward<Types>(types)...))
                        {
                            return call(typename gens<sizeof...(ClosureTypes)>::type(), std::forward<Types>(types)...);
                        }
                };
        }

        template<typename... Types>
            // remove references as closure capture the env by copy
            task<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...> partial(Types &&... types) {
                return task<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...>(std::forward<Types>(types)...);
            }

        PROXY(pythonic::functools, partial);
    }
}
#endif

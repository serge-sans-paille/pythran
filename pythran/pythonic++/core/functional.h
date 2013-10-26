#ifndef PYTHONIC_FUNCTIONAL_H
#define PYTHONIC_FUNCTIONAL_H
#include <utility>
#include <tuple>

namespace pythonic {
    template<class T>
    /* a class to wrap other functor instances
     * it assumes the functor have a copy operator
     */
    class function {
        char mem[sizeof(T)];
    public:
        typedef void callable;
        T* ptr; //SG: I fail to understand why gcc requires this to be public

        function() :
                ptr(nullptr)
        {
        }
        function(T const & t) :
                ptr(new (mem) T(t))
        {
        }

        template<class ... Types>
        auto operator()(Types&&... args) const -> decltype((*ptr)(std::forward<Types>(args)...))
        {
            return (*ptr)(std::forward<Types>(args)...);
        }

        template<class F>
        function<T>& operator=(F&& f)
        {
            ptr = new (mem) F(f);
        }
    };

    template<class ... Types>
    struct variant {
    };

    template<class Type>
    struct variant<Type> {
        char mem[sizeof(Type)];
        Type* t;

        variant() :
                t(nullptr)
        {
        }
        variant(Type const& t) :
                t(new (mem) Type(t))
        {
        }
        variant(variant<Type> const& t) :
                t(t.t ? new (mem) Type(*t.t) : t.t)
        {
        }
        template<class OtherType>
        variant(variant<OtherType> const& t) :
                t(nullptr)
        {
        }

        template<class ... Args>
        auto operator()(Args&&... args) -> decltype( std::declval<Type>()(std::forward<Args>(args)...) )
        {
            return (*t)(std::forward<Args>(args)...);
        }

    };

    template<class Type, class ... Types>
    struct variant<Type, Types...> {
        typedef void callable;
        char mem[sizeof(Type)];
        Type* t;
        variant<Types...> ot;

        variant() :
                t(nullptr), ot()
        {
        }
        variant(Type const& t) :
                t(new (mem) Type(t)), ot()
        {
        }
        template<class T>
        variant(T const& t) :
                t(nullptr), ot(t)
        {
        }

        // the below constructor handle case when Types and OtherTypes are not exactly the same
        // or are in a different order
        template<class OtherType, class ... OtherTypes>
        variant(variant<OtherType, OtherTypes...> const& t) :
                t(nullptr), ot(t.ot)
        {
        }

        template<class ... OtherTypes>
        variant(variant<Type, OtherTypes...> const& t) :
                t(t.t ? new (mem) Type(*t.t) : t.t), ot(t.ot)
        {
        }

        template<class ... Args>
        auto operator()(Args&&... args) -> decltype( std::declval<Type>()(args...))
        {
            if (t)
                return (*t)(args...);
            else
                return ot(args...);
        }
    };

    /* wrapper used by generated code to simulate closures { */
    namespace __builtin__ {
        namespace proxy {

            template<int...>
            struct seq {};

            template<int N, int ...S>
            struct gens: gens<N - 1, N - 1, S...> {
            };

            template<int ...S>
            struct gens<1, S...> {
                typedef seq<S...> type;
            };

            namespace {
                template<typename ... BoundedTypes>
                struct bounded {

                    mutable std::tuple<BoundedTypes...> params; // mutable because pythran assumes all function calls are const

                    bounded() :
                            params()
                    {
                    }

                    bounded(BoundedTypes ... types) :
                            params(types...)
                    {
                    }

                    template<int ...S, typename ... Types>
                    auto call(seq<S...>,
                            Types &&... types) const -> decltype(std::get<0>(params)(std::get<S>(params)..., std::forward<Types>(types)...))
                    {
                        return std::get<0>(params)(std::get<S>(params)..., std::forward<Types>(types)...);
                    }

                    template<typename ... Types>
                    auto operator()(
                            Types &&... types) const -> decltype(this->call(typename gens<sizeof...(BoundedTypes)>::type(), std::forward<Types>(types)...))
                    {
                        return call(typename gens<sizeof...(BoundedTypes)>::type(), std::forward<Types>(types)...);
                    }
                };
            }

            struct bind {
                // remove references as closure capture the env by copy
                template<typename ... Types>
                bounded<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...> operator()(Types &&... types)
                {
                    return bounded<typename std::remove_cv<typename std::remove_reference<Types>::type>::type...>(std::forward<Types>(types)...);
                }
            };
        }
    }
}
#endif

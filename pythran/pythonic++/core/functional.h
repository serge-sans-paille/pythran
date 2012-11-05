#ifndef PYTHONIC_FUNCTIONAL_H
#define PYTHONIC_FUNCTIONAL_H
#include <utility>

namespace pythonic {
    template <class T>
        /* a class to wrap other functor instances
         * it assumes the functor have a copy operator
         */
        class function {
            char mem[sizeof(T)];
            public:
            T* ptr; //SG: I fail to understand why gcc requires this to be public

            function() : ptr(nullptr) {}
            function(T const & t) : ptr(new (mem) T(t)) {}

            template<class... Types>
                auto operator()(Types&&... args) const -> decltype((*ptr)(args...)) { return (*ptr)(args...); }

            template<class F>
                function<T>& operator=(F&& f) { ptr = new(mem) F(f); }
        };

    template <class... Types>
        struct variant {};

    template <class Type>
        struct variant<Type> {
            char mem[sizeof(Type)];
            Type* t;

            variant() : t(nullptr) {}
            variant(Type const& t) : t(new (mem) Type(t)) {}

            template <class... Args>
                auto operator()(Args&&... args) -> decltype( std::declval<Type>()(args...)){
                    return (*t)(args...);
                }

        };

    template<class Type, class... Types>
        struct variant<Type, Types...> {
            char mem[sizeof(Type)];
            Type* t;
            variant<Types...> ot;

            variant() : t(nullptr), ot() {}
            variant(Type const& t) : t(new (mem) Type(t)), ot() {}
            template<class T>
                variant(T const& t) : t(nullptr), ot(t) {}

            template <class... Args>
                auto operator()(Args&&... args) -> decltype( std::declval<Type>()(args...)){
                    if(t) return (*t)(args...);
                    else return ot(args...);
                }
        };
}
#endif

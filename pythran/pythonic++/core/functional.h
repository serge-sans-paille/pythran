#ifndef PYTHONIC_FUNCTIONAL_H
#define PYTHONIC_FUNCTIONAL_H

namespace pythonic {
    template <class T>
        /* a class to wrap other functor instances
         * it assumes the functor have a copy operator
         */
        class function {
            char mem[sizeof(T)];
            T* ptr;
            public:
            function() : ptr(nullptr) {}
            function(T const & t) : ptr(new (mem) T(t)) {}
            template<class... Types>
                auto operator()(Types&&... args) -> decltype((*ptr)(args...)) { return (*ptr)(args...); }

            template<class F>
                function<T>& operator=(F&& f) { ptr = new(mem) F(f); }
        };
}
#endif

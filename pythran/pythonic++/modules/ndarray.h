#ifndef PYTHONIC_MODULE_NDARRAY_H
#define PYTHONIC_MODULE_NDARRAY_H

namespace pythonic {
    namespace __ndarray__ {

        template<class E, class F>
            none_type fill(E&& e, F f) {
                std::fill(e.buffer, e.buffer + e.size(), f);
                return None;
            }

        PROXY(pythonic::__ndarray__, fill);

        template<class T, size_t N>
            core::ndarray<T, 1>
            flatten(core::ndarray<T,N> const& a) {
                long n = a.size();
                T *buffer = new T[n];
                std::copy(a.buffer, a.buffer + n, buffer);
                long shape[1] = {n};
                return core::ndarray<T, 1>(buffer, shape, shape[0]);
            }

        PROXY(pythonic::__ndarray__, flatten);
        template<class E>
            auto item(E&& expr, long i) -> decltype(expr.at(i))
            {
                return expr.at(i);
            }
        template<class E, size_t N>
            auto item(E&& expr, core::ltuple<long, N> const& i) -> decltype(expr[i])
            {
                return expr[i];
            }
        PROXY(pythonic::__ndarray__, item);

                
    }
}
#endif

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

        template<class T, size_t N>
            core::string tostring(core::ndarray<T,N> const& expr)
            {
                return core::string(reinterpret_cast<const char*>(expr.buffer), expr.size() * sizeof(T));
            }
        NUMPY_EXPR_TO_NDARRAY0(tostring);
        PROXY(pythonic::__ndarray__, tostring);

        template<class T, size_t N>
            struct tolist_type
            {
                typedef core::list<typename tolist_type<T, N-1>::type> type;
            };

        template<class T>
            struct tolist_type<T, 1>
            {
                typedef core::list<T> type;
            };

        template<class T>
            core::list<T> tolist(core::ndarray<T,1> const& expr)
            {
                return core::list<T>(expr.buffer, expr.buffer + expr.size());
            }

        template<class T, size_t N>
            typename tolist_type<T, N>::type tolist(core::ndarray<T,N> const& expr)
            {
                typename tolist_type<T, N>::type out(0);
                for(core::ndarray<T,N-1> const& elts: expr)
                    out.push_back(tolist(elts));
                return out;
            }
        NUMPY_EXPR_TO_NDARRAY0(tolist);
        PROXY(pythonic::__ndarray__, tolist);
    }
}
#endif

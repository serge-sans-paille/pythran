#ifndef PYTHONIC_NUMPY_UNIQUE_HPP
#define PYTHONIC_NUMPY_UNIQUE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"

namespace pythonic {

    namespace numpy {
        template<class I, class O>
            void _unique1(I begin, I end, O& out, utils::int_<1>)
            {
                    out.insert(begin, end);
            }
        template<class I, class O, size_t N>
            void _unique1(I begin, I end, O& out, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _unique1((*begin).begin(), (*begin).end(), out, utils::int_<N - 1>());
            }

        template<class E>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1> unique(E const& expr) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                _unique1(expr.begin(), expr.end(), res, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res);
            }

        template<class I, class O0, class O1>
            void _unique2(I begin, I end, O0& out0, O1& out1, long & i, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++i) {
                    auto pair = out0.insert(*begin);
                    if(pair.second)
                        out1.push_back(i);
                }
            }
        template<class I, class O0, class O1, size_t N>
            void _unique2(I begin, I end, O0& out0, O1& out1, long & i, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _unique2((*begin).begin(), (*begin).end(), out0, out1, i, utils::int_<N - 1>());
            }

        template<class E>
            std::tuple<types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>, types::ndarray<long, 1>> unique(E const& expr, bool return_index) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                std::vector<long> return_index_res;
                long i = 0;
                _unique2(expr.begin(), expr.end(), res, return_index_res, i, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return std::make_tuple(types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res), types::ndarray<long, 1>(return_index_res));
            }


        template<class I, class O0, class O1, class O2>
            void _unique3(I begin, I end, O0& out0, O1& out1, O2& out2, long & i, utils::int_<1>)
            {
                for(; begin != end; ++begin, ++i) {
                    auto pair = out0.insert(*begin);
                    out2[i] = std::distance(out0.begin(), pair.first);
                    if(pair.second)
                        out1.push_back(i);
                }
            }
        template<class I, class O0, class O1, class O2, size_t N>
            void _unique3(I begin, I end, O0& out0, O1& out1, O2& out2, long & i, utils::int_<N>)
            {
                for(; begin != end; ++begin)
                    _unique3((*begin).begin(), (*begin).end(), out0, out1, out2, i, utils::int_<N - 1>());
            }
        template<class E>
            std::tuple<types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>, types::ndarray<long, 1>, types::ndarray<long, 1>> unique(E const& expr, bool return_index, bool return_inverse) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                std::vector<long> return_index_res;
                types::ndarray<long, 1> return_inverse_res(types::array<long,1>{{expr.size()}}, __builtin__::None);
                long i = 0;
                _unique3(expr.begin(), expr.end(), res, return_index_res, return_inverse_res, i, utils::int_<types::numpy_expr_to_ndarray<E>::N>());
                return std::make_tuple(types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res), types::ndarray<long, 1>(return_index_res), return_inverse_res);
            }

        PROXY(pythonic::numpy, unique)

    }

}

#endif


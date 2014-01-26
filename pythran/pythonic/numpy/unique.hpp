#ifndef PYTHONIC_NUMPY_UNIQUE_HPP
#define PYTHONIC_NUMPY_UNIQUE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1> unique(E const& expr) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                for(size_t i=0; i<expr.size(); ++i)
                    res.insert(expr.at(i));
                return types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res);
            }

        template<class E>
            std::tuple<types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>, types::ndarray<long, 1>> unique(E const& expr, bool return_index) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                std::vector<long> return_index_res;
                for(size_t i=0; i<expr.size(); ++i)
                {
                    std::pair<typename std::set<typename types::numpy_expr_to_ndarray<E>::T>::iterator, bool> pair = res.insert(expr.at(i));
                    if(pair.second)
                        return_index_res.push_back(i);
                }
                return std::make_tuple(types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res), types::ndarray<long, 1>(return_index_res));
            }

        template<class E>
            std::tuple<types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>, types::ndarray<long, 1>, types::ndarray<long, 1>> unique(E const& expr, bool return_index, bool return_inverse) {
                std::set<typename types::numpy_expr_to_ndarray<E>::T> res;
                std::vector<long> return_index_res;
                types::ndarray<long, 1> return_inverse_res(types::array<long,1>{{expr.size()}}, __builtin__::None);
                for(int i=0; i<expr.size(); ++i)
                {
                    auto pair = res.insert(expr.at(i));
                    return_inverse_res[i] = std::distance(res.begin(), pair.first);
                    if(pair.second)
                        return_index_res.push_back(i);
                }
                return std::make_tuple(types::ndarray<typename types::numpy_expr_to_ndarray<E>::T, 1>(res), types::ndarray<long, 1>(return_index_res), return_inverse_res);
            }

        PROXY(pythonic::numpy, unique)

    }

}

#endif


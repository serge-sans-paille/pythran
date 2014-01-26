#ifndef PYTHONIC_NUMPY_SORT_HPP
#define PYTHONIC_NUMPY_SORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::ndarray<T,N> sort(types::ndarray<T,N> const& expr, long axis=-1)
            {
                while(axis<0)
                    axis += N;
                axis = axis%N;
                types::ndarray<T,N> out(expr.shape, __builtin__::None);
                std::copy(expr.buffer, expr.buffer + expr.size(), out.buffer);
                long step = std::accumulate(expr.shape.begin() + axis, expr.shape.end(), 1L, std::multiplies<long>());
                for(size_t i=0; i<expr.size()/expr.shape[axis]*step; i+=step)
                {
                    std::vector<T> to_sort;
                    T* iter = out.buffer + (i%expr.size() + i/expr.size());
                    while(iter!=out.buffer + (i%expr.size() + i/expr.size()) + step)
                    {
                        to_sort.push_back(*iter);
                        iter+=step/expr.shape[axis];
                    }
                    std::sort(to_sort.begin(), to_sort.end());
                    iter = out.buffer + (i%expr.size() + i/expr.size());
                    for(auto val: to_sort)
                    {
                        *iter = val;
                        iter += step/expr.shape[axis];
                    }
                }
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(sort)
            PROXY(pythonic::numpy, sort);

    }

}

#endif


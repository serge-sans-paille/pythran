#ifndef PYTHONIC_NUMPY_MIN_HPP
#define PYTHONIC_NUMPY_MIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class E>
            auto min(E&& expr) -> typename std::remove_reference<decltype(expr.at(0))>::type {
                long sz = expr.size();
                if(not sz) 
                    throw types::ValueError("empty sequence");
                auto res = expr.at(0);
                for(long i = 1; i< sz ; ++i) {
                    auto e_i = expr.at(i);
                    if(e_i< res)
                        res = e_i;
                }
                return res;
            }
        template<class T>
            T min(types::ndarray<T,1> const& array, long axis) {
                if(axis!=0)
                    throw types::ValueError("axis out of bounds");
                return min(array);
            }
        template<class T, size_t N>
            typename types::ndarray<T,N>::value_type min(types::ndarray<T,N> const& array, long axis)
            {
                if(axis<0 || axis >=long(N))
                    throw types::ValueError("axis out of bounds");
                auto shape = array.shape;
                if(axis==0)
                {
                    types::array<long, N-1> shp;
                    size_t size = 1;
                    for(auto i= shape.begin() + 1, j = shp.begin(); i<shape.end(); ++i, ++j)
                        size*=(*j = *i);
                    types::ndarray<T,N-1> a(shp, __builtin__::None);
                    auto a_iter = a.buffer;
                    std::copy(array.buffer, array.buffer + size, a_iter);
                    for(auto i = array.begin() + 1; i<array.end(); ++i)
                    {
                        auto next_subarray = *i;  //we need this variable to keep this ndarray alive while iter is used
                        auto iter = next_subarray.buffer,
                             iter_end = next_subarray.buffer + next_subarray.size();
                        auto k = a_iter;
                        for(auto j = iter; j<iter_end; ++j, ++k)
                            *k=std::min(*k,*j);
                    }
                    return a;
                }
                else
                {
                    types::array<long, N-1> shp;
                    std::copy(shape.begin(), shape.end() - 1, shp.begin());
                    types::ndarray<T,N-1> miny(shp, __builtin__::None);
                    std::transform(array.begin(), array.end(), miny.begin(), [=](types::ndarray<T,N-1> const& other) {return min(other, axis-1);});
                    return miny;
                }
            }
        PROXY(pythonic::numpy, min);

    }

}

#endif


#ifndef PYTHONIC_NUMPY_SORTCOMPLEX_HPP
#define PYTHONIC_NUMPY_SORTCOMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        bool comp_complex(std::complex<double> const& i, std::complex<double> const& j)
        {
            if(std::real(i) == std::real(j))
                return std::imag(i) < std::imag(j);
            else
                return std::real(i) < std::real(j);
        }

        template<class T, size_t N>
            types::ndarray<std::complex<double>,N> sort_complex(types::ndarray<T,N> const& expr)
            {
                types::ndarray<std::complex<double>,N> out(expr.shape, __builtin__::None);
                std::copy(expr.buffer, expr.buffer + expr.size(), out.buffer);
                for(int i=0; i<expr.size()/expr.shape[N-1]; ++i)
                    std::sort(out.buffer + i * expr.shape[N-1], out.buffer + (i+1) * expr.shape[N-1], comp_complex);
                return out;
            }

        NUMPY_EXPR_TO_NDARRAY0(sort_complex)
            PROXY(pythonic::numpy, sort_complex);

    }

}

#endif


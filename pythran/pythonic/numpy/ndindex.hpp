#ifndef PYTHONIC_NUMPY_NDINDEX_HPP
#define PYTHONIC_NUMPY_NDINDEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/numpy_type.hpp"

#include <numeric>

namespace pythonic {

    namespace numpy {
        template<size_t N>
            struct ndindex_iterator : std::iterator<std::random_access_iterator_tag,
                                                    types::array<long, N>,
                                                    ptrdiff_t,
                                                    types::array<long, N>*,
                                                    types::array<long, N> /* reference_type, but no reference is possible*/  > {
                long index;
                types::array<long, N> shape;
                ndindex_iterator(){}
                ndindex_iterator(types::array<long, N> const& shape, long first) : index(first), shape(shape) {
                }
                types::array<long, N> operator*() {
                    types::array<long, N> out;
                    long mult = 1;
                    for(long j=N-1; j>0; j--) {
                        out[j] = (index/mult)%shape[j];
                        mult*=shape[j];
                    }
                    out[0] = index/mult;
                    return out;
                }
                ndindex_iterator& operator++() { ++index; return *this; }
                ndindex_iterator& operator+=(long n) { index+=n; return *this; }
                bool operator!=(ndindex_iterator const& other) { return index != other.index; }
                bool operator<(ndindex_iterator const& other) { return index < other.index; }
                long operator-(ndindex_iterator const& other) { return index - other.index; }

            };

        template<size_t N>
            struct _ndindex : ndindex_iterator<N> {
                typedef ndindex_iterator<N> iterator;
                types::array<long, N> shape; 
                iterator end_iter;

                _ndindex() {}
                _ndindex( types::array<long, N> const& shape) :  ndindex_iterator<N>(shape, 0), shape(shape), end_iter(shape, std::accumulate(shape.begin(), shape.end(), 1L, std::multiplies<long>())) {
                }
                iterator & begin() { return *this; }
                iterator const & begin() const { return *this; }
                iterator end() const { return end_iter; }
            };

        template<class... Types>
            _ndindex<sizeof...(Types)> ndindex(Types... args) {
                return _ndindex<sizeof...(Types)>(types::make_tuple(args...));
            }
        template<size_t N>
            _ndindex<N> ndindex(types::array<long, N> const& args) {
                return _ndindex<N>(args);
            }

        PROXY(pythonic::numpy, ndindex);

    }

}

#endif


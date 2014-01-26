#ifndef PYTHONIC_NUMPY_ARRAYSPLIT_HPP
#define PYTHONIC_NUMPY_ARRAYSPLIT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class T, size_t N>
            types::list<types::ndarray<T,N>> array_split(types::ndarray<T,N> const& a, long nb_split) {
                long sz = std::distance(a.begin(), a.end());
                long n = (sz + nb_split -1 ) / nb_split;
                long end = n * nb_split;
                long nb_full_split = nb_split;
                if(end != sz) nb_full_split -= (end -sz);
                types::list<types::ndarray<T,N>> out(nb_split);
                long index = 0;
                for(long i=0;i<nb_full_split; ++i, index+=n)
                    out[i] = a[types::slice(index, index+n)];
                for(long i=nb_full_split;i<nb_split; ++i, index+=(n-1))
                    out[i] = a[types::slice(index, index + n - 1)];

                return out;
            }

        template<class T, size_t N, class I>
            typename std::enable_if<types::is_iterable<I>::value, types::list<types::ndarray<T,N>>>::type
            array_split(types::ndarray<T,N> const& a, I const& split_mask) {
                long sz = std::distance(a.begin(), a.end());
                types::list<types::ndarray<T,N>> out(1+split_mask.size());
                long index = 0;
                auto inserter = out.begin();
                for(auto next_index: split_mask) {
                    *inserter++ = a[types::slice(index, next_index)];
                    index = next_index;
                }
                *inserter = a[types::slice(index, sz)];
                return out;
            }

        PROXY(pythonic::numpy, array_split);

    }

}

#endif


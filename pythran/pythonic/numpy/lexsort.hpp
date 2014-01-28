#ifndef PYTHONIC_NUMPY_LEXSORT_HPP
#define PYTHONIC_NUMPY_LEXSORT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class K>
            struct lexcmp {
                K const& keys;
                lexcmp(K const& keys) : keys(keys) {
                }
                bool operator()(long i0, long i1) {
                    for(long i= keys.size() -1; i>=0; --i)
                        if(keys[i][i0] < keys[i][i1]) return true;
                        else if(keys[i][i0] > keys[i][i1]) return false;
                    return false;
                }
            };

        template<class T, size_t N>
            types::ndarray<long, 1> lexsort(types::array<T, N> const& keys) {
                long n = keys[0].size();
                types::ndarray<long, 1> out(types::make_tuple(n), __builtin__::None);
                // fill with the original indices
                std::iota(out.buffer, out.buffer + n, 0L);
                // then sort using keys as the comparator
                std::sort(out.buffer, out.buffer +n, lexcmp<types::array<T, N>>(keys));
                return out;
            }
        PROXY(pythonic::numpy, lexsort)

    }

}

#endif


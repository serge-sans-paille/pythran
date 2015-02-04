#ifndef PYTHONIC_NUMPY_SELECT_HPP
#define PYTHONIC_NUMPY_SELECT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"

namespace pythonic {

    namespace numpy {

        //TODO It could certainly be represent as a numpy_***_expr as each elements
        // is computed without information from neighbor.
        //
        template<class Ichoice, class Icond, class Iout, class Isel>
            long _select(Ichoice ibegin, Ichoice iend, Iout obegin, Isel sbegin, Icond cbegin, long size, utils::int_<1>)
            {
                for(; ibegin != iend and size != 0 ; ibegin++, obegin++, sbegin++, cbegin++)
                {
                    // If elements it not already selected and condition match, copy it!
                    if(!*sbegin and *cbegin)
                    {
                        *obegin = *ibegin;
                        *sbegin = true;
                        size--;
                    }
                }
                return size;
            }

        template<class Ichoice, class Icond, class Iout, class Isel, size_t N>
            long _select(Ichoice ibegin, Ichoice iend, Iout obegin, Isel sbegin, Icond cbegin, long size, utils::int_<N>)
            {
                for(; ibegin != iend and size != 0 ; ibegin++, obegin++, sbegin++, cbegin++)
                    size = _select((*ibegin).begin(), (*ibegin).end(),
                                   (*obegin).begin(), (*sbegin).begin(),
                                   (*cbegin).begin(), size, utils::int_<N - 1>());
                return size;
            }

        template<class T, class U>
            typename types::numpy_expr_to_ndarray<U>::type select(types::list<T> const& condlist, types::list<U> const& choicelist, typename types::numpy_expr_to_ndarray<U>::T _default=0)
            {
                constexpr size_t N = types::numpy_expr_to_ndarray<U>::N;
                types::ndarray<T,N> out(choicelist[0].shape, _default);
                types::ndarray<T,N> selected(choicelist[0].shape, false);
                long size = selected.flat_size();
                for(long i=0; i<condlist.size() && size != 0; i++)
                    size = _select(choicelist[i].begin(), choicelist[i].end(), out.begin(), selected.begin(), condlist.begin(), size, utils::int_<N>());
                return out; 
            }

        template<class T, size_t N, class U>
            types::ndarray<T,N> select(types::list<types::ndarray<U,N>> const& condlist, types::list<types::ndarray<T,N>> const& choicelist, T _default = 0)
            {
                types::ndarray<T,N> out(choicelist[0].shape, _default);
                for(long i=0; i<out.flat_size(); ++i)
                {
                    for(long j=0; j<condlist.size(); ++j)
                    {
                        if(condlist[j].buffer[i])
                        {
                            out.buffer[i] = choicelist[j].buffer[i];
                            break;
                        }
                    }
                }
                return out;
            }

            PROXY(pythonic::numpy, select);
    }
}

#endif


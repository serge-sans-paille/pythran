#ifndef PYTHONIC_INCLUDE_NUMPY_SELECT_HPP
#define PYTHONIC_INCLUDE_NUMPY_SELECT_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"

namespace pythonic {

    namespace numpy {

        //TODO It could certainly be represent as a numpy_***_expr as each elements
        // is computed without information from neighbor.
        //
        template<class Ichoice, class Icond, class Iout, class Isel>
            long _select(Ichoice ibegin, Ichoice iend, Iout obegin, Isel sbegin, Icond cbegin, long size, utils::int_<1>);

        template<class Ichoice, class Icond, class Iout, class Isel, size_t N>
            long _select(Ichoice ibegin, Ichoice iend, Iout obegin, Isel sbegin, Icond cbegin, long size, utils::int_<N>);

        template<class T, class U>
            typename types::numpy_expr_to_ndarray<U>::type select(types::list<T> const& condlist, types::list<U> const& choicelist, typename types::numpy_expr_to_ndarray<U>::T _default=0);

        template<class T, size_t N, class U>
            types::ndarray<T,N> select(types::list<types::ndarray<U,N>> const& condlist, types::list<types::ndarray<T,N>> const& choicelist, T _default = 0);

            PROXY_DECL(pythonic::numpy, select);
    }
}

#endif

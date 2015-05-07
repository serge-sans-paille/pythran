#ifndef PYTHONIC_INCLUDE_NUMPY_FROMITER_HPP
#define PYTHONIC_INCLUDE_NUMPY_FROMITER_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
        template<class Iterable, class dtype=double>
            types::ndarray<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type::value_type, 1>
            fromiter(Iterable&& iterable, dtype d=dtype(), long count=-1);

        PROXY_DECL(pythonic::numpy, fromiter);

    }

}

#endif

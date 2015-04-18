#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP

#include "pythonic/__builtin__/None.hpp"
#include "pythonic/itertools/imap.hpp"

namespace pythonic {

    namespace itertools {

        template <typename... Iter>
            auto izip(Iter &&... iters)
            -> decltype(imap(__builtin__::None, std::forward<Iter>(iters)...));

        PROXY_DECL(pythonic::itertools, izip);

    }

}

#endif

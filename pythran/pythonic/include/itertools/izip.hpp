#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP

#include "pythonic/include/__builtin__/None.hpp"
#include "pythonic/include/itertools/imap.hpp"

namespace pythonic
{

  namespace itertools
  {

    template <typename... Iter>
    auto izip(Iter &&... iters)
        -> decltype(imap(__builtin__::None, std::forward<Iter>(iters)...));

    DECLARE_FUNCTOR(pythonic::itertools, izip);
  }
}

#endif

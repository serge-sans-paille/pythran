#ifndef PYTHONIC_ITERTOOLS_IZIP_HPP
#define PYTHONIC_ITERTOOLS_IZIP_HPP

#include "pythonic/include/itertools/izip.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/itertools/imap.hpp"

namespace pythonic
{

  namespace itertools
  {

    template <typename... Iter>
    auto izip(Iter &&... iters)
        -> decltype(imap(__builtin__::None, std::forward<Iter>(iters)...))
    {
      return imap(__builtin__::None, std::forward<Iter>(iters)...);
    }

    DEFINE_FUNCTOR(pythonic::itertools, izip);
  }
}

#endif

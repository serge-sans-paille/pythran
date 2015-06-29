#ifndef PYTHONIC_ITERTOOLS_IZIP_HPP
#define PYTHONIC_ITERTOOLS_IZIP_HPP

#include "pythonic/include/itertools/izip.hpp"
#include "pythonic/builtins/None.hpp"
#include "pythonic/itertools/imap.hpp"

namespace pythonic
{

  namespace itertools
  {

    template <typename... Iter>
    auto izip(Iter &&... iters)
        -> decltype(imap(builtins::None, std::forward<Iter>(iters)...))
    {
      return imap(builtins::None, std::forward<Iter>(iters)...);
    }

    PROXY_IMPL(pythonic::itertools, izip);
  }
}

#endif

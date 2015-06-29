#ifndef PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP
#define PYTHONIC_INCLUDE_ITERTOOLS_IZIP_HPP

#include "pythonic/builtins/None.hpp"
#include "pythonic/itertools/imap.hpp"

namespace pythonic
{

  namespace itertools
  {

    template <typename... Iter>
    auto izip(Iter &&... iters)
        -> decltype(imap(builtins::None, std::forward<Iter>(iters)...));

    PROXY_DECL(pythonic::itertools, izip);
  }
}

#endif

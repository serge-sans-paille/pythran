#ifndef PYTHONIC_BUILTIN_ZIP_HPP
#define PYTHONIC_BUILTIN_ZIP_HPP

#include "pythonic/include/builtins/zip.hpp"

#include "pythonic/builtins/len.hpp"
#include "pythonic/builtins/min.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/fwd.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace details
    {
      template <class Iterator0, class... Iterators>
      auto zip(size_t n, Iterator0 first, Iterators... iters)
          -> types::list<decltype(types::make_tuple(*first, *iters...))>
      {
        types::list<decltype(types::make_tuple(*first, *iters...))> out =
            types::empty_list();
        out.reserve(n);
        for (size_t i = 0; i < n; ++i, ++first, utils::fwd(++iters...))
          out.push_back(types::make_tuple(*first, *iters...));
        return out;
      }
    }

    template <class List0, class... Lists>
    auto zip(List0 &&s0, Lists &&... lists)
        -> types::list<decltype(types::make_tuple(*s0.begin(),
                                                  *lists.begin()...))>
    {
      size_t n =
          min(len(std::forward<List0>(s0)), len(std::forward<Lists>(lists))...);
      return details::zip(n, s0.begin(), lists.begin()...);
    }

    types::empty_list zip()
    {
      return types::empty_list();
    }

    PROXY_IMPL(pythonic::builtins, zip);
  }
}

#endif

#ifndef PYTHONIC_BUILTIN_ZIP_HPP
#define PYTHONIC_BUILTIN_ZIP_HPP

#include "pythonic/include/__builtin__/zip.hpp"

#include "pythonic/__builtin__/len.hpp"
#include "pythonic/__builtin__/min.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/fwd.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace details
  {
    template <class... Iterators>
    auto zip(size_t n, Iterators... iters)
        -> types::list<decltype(types::make_tuple(*iters...))>
    {
      types::list<decltype(types::make_tuple(*iters...))> out =
          types::empty_list();
      out.reserve(n);
      for (size_t i = 0; i < n; ++i, utils::fwd(++iters...))
        out.push_back(types::make_tuple(*iters...));
      return out;
    }
  }

  template <class... Lists>
  auto zip(Lists &&... lists)
      -> types::list<decltype(types::make_tuple(*lists.begin()...))>
  {
    size_t n = min(len(std::forward<Lists>(lists))...);
    return details::zip(n, lists.begin()...);
  }

  types::empty_list zip()
  {
    return types::empty_list();
  }

  DEFINE_FUNCTOR(pythonic::__builtin__, zip);
}
PYTHONIC_NS_END

#endif

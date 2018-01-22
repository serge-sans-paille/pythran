#ifndef PYTHONIC_BUILTIN_FILE_WRITELINES_HPP
#define PYTHONIC_BUILTIN_FILE_WRITELINES_HPP

#include "pythonic/include/__builtin__/file/writelines.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace file
  {

    template <class F, class T>
    void writelines(F &&f, T const &sequence)
    {
      f.writelines(sequence);
    }

    DEFINE_FUNCTOR(pythonic::__builtin__::file, writelines);
  }
}
PYTHONIC_NS_END
#endif

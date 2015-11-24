#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITELINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITELINES_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace file
    {

      template <class F, class T>
      void writelines(F &&f, T const &sequence);

      DECLARE_FUNCTOR(pythonic::__builtin__::file, writelines);
    }
  }
}
#endif

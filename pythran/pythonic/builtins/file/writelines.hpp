#ifndef PYTHONIC_BUILTIN_FILE_WRITELINES_HPP
#define PYTHONIC_BUILTIN_FILE_WRITELINES_HPP

#include "pythonic/include/builtins/file/writelines.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      template <class F, class T>
      void writelines(F &&f, T const &sequence)
      {
        f.writelines(sequence);
      }

      PROXY_IMPL(pythonic::builtins::file, writelines);
    }
  }
}
#endif

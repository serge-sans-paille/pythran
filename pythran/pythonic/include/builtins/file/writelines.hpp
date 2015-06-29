#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITELINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITELINES_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace file
    {

      template <class F, class T>
      void writelines(F &&f, T const &sequence);

      PROXY_DECL(pythonic::builtins::file, writelines);
    }
  }
}
#endif

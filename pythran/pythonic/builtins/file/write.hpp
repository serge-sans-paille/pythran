#ifndef PYTHONIC_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/builtins/file/write.hpp"

#include "pythonic/types/file.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace builtins
{

  namespace file
  {

    void write(types::file &f, types::str const &str)
    {
      f.write(str);
    }

    void write(types::file &&f, types::str const &str)
    {
      f.write(str);
    }
  }
}
PYTHONIC_NS_END
#endif

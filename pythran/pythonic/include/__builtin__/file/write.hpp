#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_WRITE_HPP

#include "pythonic/include/types/file.hpp"
#include "pythonic/include/types/str.hpp"
#include "pythonic/include/utils/functor.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace file
  {

    void write(types::file &f, types::str const &str);
    void write(types::file &&f, types::str const &str);

    DECLARE_FUNCTOR(pythonic::__builtin__::file, write);
  }
}
PYTHONIC_NS_END
#endif

#ifndef PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP
#define PYTHONIC_INCLUDE_BUILTIN_FILE_READLINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            template<class F>
                types::list<types::str> readlines(F&& f);
            template<class F>
                types::list<types::str> readlines(F&& f, int sizehint);

            PROXY_DECL(pythonic::__builtin__::file, readlines);

        }

    }

}
#endif

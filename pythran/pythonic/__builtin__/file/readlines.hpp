#ifndef PYTHONIC_BUILTIN_FILE_READLINES_HPP
#define PYTHONIC_BUILTIN_FILE_READLINES_HPP

#include "pythonic/include/__builtin__/file/readlines.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            template<class F>
                types::list<types::str> readlines(F&& f)
                {
                    return f.readlines();
                }

            template<class F>
                types::list<types::str> readlines(F&& f, int sizehint)
                {
                    return f.readlines(sizehint);
                }

            PROXY_IMPL(pythonic::__builtin__::file, readlines);

        }

    }

}
#endif

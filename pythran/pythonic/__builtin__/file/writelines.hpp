#ifndef PYTHONIC_BUILTIN_FILE_WRITELINES_HPP
#define PYTHONIC_BUILTIN_FILE_WRITELINES_HPP

#include "pythonic/include/__builtin__/file/writelines.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __builtin__  {

        namespace file {

            template<class F, class T>
                void writelines(F&& f, T const& sequence)
                {
                    f.writelines(sequence);
                }

            PROXY_IMPL(pythonic::__builtin__::file, writelines);
        }

    }

}
#endif

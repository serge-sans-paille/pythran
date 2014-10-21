#ifndef PYTHONIC_FILE_WRITELINES_HPP
#define PYTHONIC_FILE_WRITELINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        template<class F, class T>
            void writelines(F&& f, T const& sequence){
                f.writelines(sequence);
            }
        PROXY(pythonic::__builtin__::file, writelines);

    }

}

}
#endif


#ifndef PYTHONIC_FILE_WRITELINES_HPP
#define PYTHONIC_FILE_WRITELINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        template<class F, class T>
            void writelines(F&& f, T const& sequence){
                f.writelines(sequence);
            }
        PROXY(pythonic::__file__, writelines);

    }

}

#endif


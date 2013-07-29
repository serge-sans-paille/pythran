#ifndef PYTHONIC_FILE_TRUNCATE_HPP
#define PYTHONIC_FILE_TRUNCATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        void truncate(types::file & f){f.truncate();}
        void truncate(types::file && f){f.truncate();}
        void truncate(types::file & f, int size){f.truncate(size);}
        void truncate(types::file && f, int size){f.truncate(size);}
        PROXY(pythonic::__file__, truncate);

    }

}

#endif


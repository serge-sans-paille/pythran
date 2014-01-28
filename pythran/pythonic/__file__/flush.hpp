#ifndef PYTHONIC_FILE_FLUSH_HPP
#define PYTHONIC_FILE_FLUSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        void flush(types::file &f){f.flush();}
        void flush(types::file &&f){f.flush();}
        PROXY(pythonic::__file__, flush);

    }

}

#endif


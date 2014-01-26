#ifndef PYTHONIC_FILE_READLINE_HPP
#define PYTHONIC_FILE_READLINE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        types::str readline(types::file &f, int size = -1){return size < 0 ? f.readline() : f.readline(size);}
        types::str readline(types::file &&f, int size = -1){return size < 0 ? f.readline() : f.readline(size);}
        PROXY(pythonic::__file__, readline);

    }

}

#endif


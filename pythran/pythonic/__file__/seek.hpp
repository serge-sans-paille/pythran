#ifndef PYTHONIC_FILE_SEEK_HPP
#define PYTHONIC_FILE_SEEK_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        void seek(types::file &f, int offset){f.seek(offset);}
        void seek(types::file &&f, int offset){f.seek(offset);}
        void seek(types::file &f, int offset, int whence){f.seek(offset, whence);}
        void seek(types::file &&f, int offset, int whence){f.seek(offset, whence);}
        PROXY(pythonic::__file__, seek);

    }

}

#endif


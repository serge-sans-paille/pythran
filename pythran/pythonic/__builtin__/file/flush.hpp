#ifndef PYTHONIC_FILE_FLUSH_HPP
#define PYTHONIC_FILE_FLUSH_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        void flush(types::file &f){f.flush();}
        void flush(types::file &&f){f.flush();}
        PROXY(pythonic::__builtin__::file, flush);

    }

}

}
#endif


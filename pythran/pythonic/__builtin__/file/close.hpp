#ifndef PYTHONIC_FILE_CLOSE_HPP
#define PYTHONIC_FILE_CLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        void close(types::file &f){f.close();}
        void close(types::file &&f){f.close();}
        PROXY(pythonic::__builtin__::file, close);

    }

}

}
#endif


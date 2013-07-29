#ifndef PYTHONIC_FILE_CLOSE_HPP
#define PYTHONIC_FILE_CLOSE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        void close(types::file &f){f.close();}
        void close(types::file &&f){f.close();}
        PROXY(pythonic::__file__, close);

    }

}

#endif


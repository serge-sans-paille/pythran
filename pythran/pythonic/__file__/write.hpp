#ifndef PYTHONIC_FILE_WRITE_HPP
#define PYTHONIC_FILE_WRITE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        void write(types::file & f, types::str const& str){f.write(str);}
        void write(types::file && f, types::str const& str){f.write(str);}
        PROXY(pythonic::__file__, write);

    }

}

#endif


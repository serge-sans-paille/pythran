#ifndef PYTHONIC_FILE_XREADLINES_HPP
#define PYTHONIC_FILE_XREADLINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        types::file& xreadlines(types::file &f){return f;}
        types::file&& xreadlines(types::file &&f){return std::forward<types::file>(f);}
        PROXY(pythonic::__file__, xreadlines);

    }

}

#endif


#ifndef PYTHONIC_FILE_XREADLINES_HPP
#define PYTHONIC_FILE_XREADLINES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        types::file& xreadlines(types::file &f){return f;}
        types::file&& xreadlines(types::file &&f){return std::forward<types::file>(f);}
        PROXY(pythonic::__builtin__::file, xreadlines);

    }

}

}
#endif


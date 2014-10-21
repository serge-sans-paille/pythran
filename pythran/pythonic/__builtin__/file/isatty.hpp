#ifndef PYTHONIC_FILE_ISATTY_HPP
#define PYTHONIC_FILE_ISATTY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        bool isatty(types::file const& f){return f.isatty();}
        PROXY(pythonic::__builtin__::file, isatty);

    }

}

}
#endif


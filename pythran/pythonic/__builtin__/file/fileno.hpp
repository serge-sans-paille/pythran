#ifndef PYTHONIC_FILE_FILENO_HPP
#define PYTHONIC_FILE_FILENO_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic { namespace __builtin__  {

    namespace file {
        int fileno(types::file const& f){return f.fileno();}
        PROXY(pythonic::__builtin__::file, fileno);

    }

} }
#endif


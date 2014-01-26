#ifndef PYTHONIC_FILE_TELL_HPP
#define PYTHONIC_FILE_TELL_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/file.hpp"

namespace pythonic {

    namespace __file__ {
        int tell(types::file const& f){return f.tell();}
        PROXY(pythonic::__file__, tell);

    }

}

#endif


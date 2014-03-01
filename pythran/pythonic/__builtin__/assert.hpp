#ifndef PYTHONIC_BUILTIN_ASSERT_HPP
#define PYTHONIC_BUILTIN_ASSERT_HPP

#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/AssertionError.hpp"

namespace pythonic {

    void pythran_assert(bool cond, types::str const& what="") {
#ifdef NDEBUG
        if(not cond) throw types::AssertionError(what);
#endif
    }

}

#endif


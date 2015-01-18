#ifndef PYTHONIC_UTILS_TAGS_HPP
#define PYTHONIC_UTILS_TAGS_HPP

#include "pythonic/types/traits.hpp"


namespace pythonic {

    namespace purity {
        struct unknown_tag {};
        struct pure_tag {};
    }

    template<class T> struct purity_of {
      typedef typename std::conditional<types::is_pure<T>::value,
                                        purity::pure_tag,
                                        purity::unknown_tag>::type type;
    };

}

#endif

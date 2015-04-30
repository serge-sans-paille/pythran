#ifndef PYTHONIC_INCLUDE_TYPES_CONTENT_OF_HPP
#define PYTHONIC_INCLUDE_TYPES_CONTENT_OF_HPP

namespace pythonic {

    namespace types {

        template<class T>
            struct content_of
            {
                using type = typename T::value_type;
            };

    }
}

#endif

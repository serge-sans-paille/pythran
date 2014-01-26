#ifndef PYTHONIC_TYPES_CONTENT_OF_HPP
#define PYTHONIC_TYPES_CONTENT_OF_HPP

namespace pythonic {

    namespace types {
        template<class T>
            struct content_of {
                typedef typename T::value_type type;
            };

    }
}



#endif

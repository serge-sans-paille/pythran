#ifndef PYTHONIC_UTILS_RESERVE_HPP
#define PYTHONIC_UTILS_RESERVE_HPP
namespace pythonic {

    namespace utils {

        template <class Container, class From>
            void reserve(Container & , From &) //do nothing unless specialized
            {
            }
    }

}
#endif

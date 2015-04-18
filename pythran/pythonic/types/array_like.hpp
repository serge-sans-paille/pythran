#ifndef PYTHONIC_TYPES_ARRAY_LIKE_HPP
#define PYTHONIC_TYPES_ARRAY_LIKE_HPP

#include "pythonic/types/tuple.hpp"

namespace pythonic {

namespace types {

template<class T, size_t N, bool V, bool S, class VT, class Ref=VT&>
class ArrayLike
{
    public:
        using dtype = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
        using value_type = typename std::remove_cv<typename std::remove_reference<VT>::type>::type;
        using reference = Ref;
        static constexpr size_t value = N;
        static constexpr bool is_vectorizable = V;
        static constexpr bool is_strided = S;

        array<long, value> shape;

        virtual size_t size() const = 0;
        virtual size_t flat_size() const = 0;

    protected:
        ArrayLike() {}
        template< typename ... SZ>
            ArrayLike(SZ ...sz): shape{{static_cast<long>(sz)...}} {}
        ArrayLike(array<long, value> const& shape_): shape(shape_) {}
        ArrayLike(array<long, value> && shape_): shape(std::move(shape_)) {}
};

}

}

#endif

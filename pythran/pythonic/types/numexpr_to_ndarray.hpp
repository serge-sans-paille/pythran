#ifndef PYTHONIC_TYPES_NUMEXPR_TO_NDARRAY_HPP
#define PYTHONIC_TYPES_NUMEXPR_TO_NDARRAY_HPP

namespace pythonic {

    namespace types {

        template<class T, size_t N>
            struct ndarray;
        template<class T>
            struct is_numexpr_arg;

/*
         * 3 informations are available:
         * - the type `type` of the equivalent array
         * - the number of dimensions `value` of the equivalent array
         * - the type `T` of the value contained by the equivalent array
         */
        template<class T, class _ = typename std::enable_if<is_numexpr_arg<T>::value, void>::type /* just to filter out scalar types */>
            struct numpy_expr_to_ndarray;
        template <class E, class _>
            struct numpy_expr_to_ndarray {
                typedef typename E::dtype T;
                static const size_t N = E::value;
                typedef ndarray<T, N> type;
            };
        template <class L, class _>
            struct numpy_expr_to_ndarray<list<L>, _> {
                typedef typename utils::nested_container_value_type<list<L>>::type T;
                static const size_t N = utils::nested_container_depth<list<L>>::value;
                typedef ndarray<T, N> type;
            };

}
}
#endif

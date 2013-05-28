#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

template<class T, size_t N>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, ndarray<T,N>> NUMPY_UNARY_FUNC_NAME(ndarray<T,N> const & self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, ndarray<T,N>>(self);
}
template<class T>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename numpy_expr_to_ndarray<list<T>>::type> NUMPY_UNARY_FUNC_NAME(list<T> const & self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename numpy_expr_to_ndarray<list<T>>::type>(typename numpy_expr_to_ndarray<list<T>>::type(self));
}
template<class T>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, sliced_ndarray<T>> NUMPY_UNARY_FUNC_NAME(sliced_ndarray<T> const & self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, sliced_ndarray<T>>(self);
}
template<class T, size_t N, size_t L>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, gsliced_ndarray<T,N,L>> NUMPY_UNARY_FUNC_NAME(gsliced_ndarray<T,N,L> const & self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, gsliced_ndarray<T,N,L>>(self);
}
template<class Op, class Arg0, class Arg1>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1>> NUMPY_UNARY_FUNC_NAME(numpy_expr<Op, Arg0, Arg1> const& self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1> >(self);
}
template<class Op, class Arg0>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, numpy_uexpr<Op, Arg0>> NUMPY_UNARY_FUNC_NAME(numpy_uexpr<Op, Arg0> const& self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, numpy_uexpr<Op, Arg0> >(self);
}
#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

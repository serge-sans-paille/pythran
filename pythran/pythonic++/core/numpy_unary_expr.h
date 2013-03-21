#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

template<class T, unsigned long N>
numpy_uexpr<NUMPY_UNARY_FUNC_SYM, ndarray<T,N>> NUMPY_UNARY_FUNC_NAME(ndarray<T,N> const & self) {
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, ndarray<T,N>>(self);
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

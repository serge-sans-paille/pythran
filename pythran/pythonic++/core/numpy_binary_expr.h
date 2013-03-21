#ifndef NUMPY_BINARY_FUNC_NAME        
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template<class T, unsigned long N>
numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, ndarray<T,N>> NUMPY_BINARY_FUNC_NAME(ndarray<T,N> const & self, ndarray<T,N> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, ndarray<T,N>>(self, other);
}

template<class T, unsigned long N, class Op, class Arg0, class Arg1>
numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, numpy_expr<Op, Arg0, Arg1>> NUMPY_BINARY_FUNC_NAME(ndarray<T,N> const & self, numpy_expr<Op, Arg0, Arg1> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, numpy_expr<Op, Arg0, Arg1>>(self, other);
}

template<class T, unsigned long N, class Op, class Arg0>
numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, numpy_uexpr<Op, Arg0>> NUMPY_BINARY_FUNC_NAME(ndarray<T,N> const & self, numpy_uexpr<Op, Arg0> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, numpy_uexpr<Op, Arg0>>(self, other);
}

template<class OpA, class ArgA0, class ArgA1, class OpB, class ArgB0, class ArgB1>
numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<OpA, ArgA0, ArgA1>, numpy_expr<OpB, ArgB0, ArgB1>> NUMPY_BINARY_FUNC_NAME( numpy_expr<OpA, ArgA0, ArgA1> const & self, numpy_expr<OpB, ArgB0, ArgB1> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<OpA, ArgA0, ArgA1>, numpy_expr<OpB, ArgB0, ArgB1>>(self, other);
}

template<class OpA, class ArgA0, class OpB, class ArgB0, class ArgB1>
numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_uexpr<OpA, ArgA0>, numpy_expr<OpB, ArgB0, ArgB1>> NUMPY_BINARY_FUNC_NAME( numpy_uexpr<OpA, ArgA0> const & self, numpy_expr<OpB, ArgB0, ArgB1> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_uexpr<OpA, ArgA0>, numpy_expr<OpB, ArgB0, ArgB1>>(self, other);
}

template<class OpA, class ArgA0, class OpB, class ArgB0, class ArgB1>
numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<OpB, ArgB0, ArgB1>, numpy_uexpr<OpA, ArgA0>> NUMPY_BINARY_FUNC_NAME( numpy_expr<OpB, ArgB0, ArgB1> const & self, numpy_uexpr<OpA, ArgA0> const & other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<OpB, ArgB0, ArgB1>, numpy_uexpr<OpA, ArgA0>>(self, other);
}

template<class T, unsigned long N, class Op, class Arg0, class Arg1>
numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1>, ndarray<T,N>> NUMPY_BINARY_FUNC_NAME(numpy_expr<Op, Arg0, Arg1> const & other, ndarray<T,N> const & self) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1>, ndarray<T,N>>(other, self);
}

template<class T, unsigned long N, class Op, class Arg0>
numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_uexpr<Op, Arg0>, ndarray<T,N>> NUMPY_BINARY_FUNC_NAME(numpy_uexpr<Op, Arg0> const & other, ndarray<T,N> const & self) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_uexpr<Op, Arg0>, ndarray<T,N>>(other, self);
}

template<class T, unsigned long N, class S>
typename std::enable_if<std::is_scalar<S>::value, numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, broadcast<S>>>::type NUMPY_BINARY_FUNC_NAME(ndarray<T,N> const & self, S other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, ndarray<T,N>, broadcast<S>>(self, broadcast<S>(other));
}

template<class T, unsigned long N, class S>
typename std::enable_if<std::is_scalar<S>::value, numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, ndarray<T,N>>>::type NUMPY_BINARY_FUNC_NAME(S other, ndarray<T,N> const & self) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, ndarray<T,N>>(broadcast<S>(other), self);
}

template<class Op, class Arg0, class Arg1, class S>
typename std::enable_if<std::is_scalar<S>::value, numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1>, broadcast<S>>>::type NUMPY_BINARY_FUNC_NAME(numpy_expr<Op,Arg0,Arg1> const & self, S other) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, numpy_expr<Op, Arg0, Arg1>, broadcast<S>>(self, broadcast<S>(other));
}

template<class Op, class Arg0, class Arg1, class S>
typename std::enable_if<std::is_scalar<S>::value, numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, numpy_expr<Op, Arg0, Arg1>>>::type NUMPY_BINARY_FUNC_NAME(S other, numpy_expr<Op,Arg0,Arg1> const & self) {
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, numpy_expr<Op, Arg0, Arg1>>(broadcast<S>(other), self);
}
#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

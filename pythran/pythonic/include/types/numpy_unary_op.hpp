#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

#ifndef CYTHON_ABI
template <class E>
typename std::enable_if<types::valid_numop_parameters<E>::value,
                        types::numpy_expr<NUMPY_UNARY_FUNC_SYM, E &>>::type
NUMPY_UNARY_FUNC_NAME(E &self);
#endif

template <class E>
typename std::enable_if<types::valid_numop_parameters<E>::value,
                        types::numpy_expr<NUMPY_UNARY_FUNC_SYM, E>>::type
NUMPY_UNARY_FUNC_NAME(E const &self);

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

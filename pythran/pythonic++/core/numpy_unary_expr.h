#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

template<class E>
typename std::enable_if<is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value,
         numpy_uexpr<NUMPY_UNARY_FUNC_SYM, E>
         >::type
         NUMPY_UNARY_FUNC_NAME(E&& self)
{
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, E>(std::forward<E>(self));
}
template<class T>
    numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename numpy_expr_to_ndarray<list<T>>::type>
NUMPY_UNARY_FUNC_NAME(list<T> const& self)
{
    return numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename numpy_expr_to_ndarray<list<T>>::type>(typename numpy_expr_to_ndarray<list<T>>::type(self));
}

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

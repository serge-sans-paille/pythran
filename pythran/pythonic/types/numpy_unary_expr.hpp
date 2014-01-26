#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

template<class E>
typename std::enable_if<types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value,
         types::numpy_uexpr<NUMPY_UNARY_FUNC_SYM, E>
    >::type
NUMPY_UNARY_FUNC_NAME(E&& self)
{
    return types::numpy_uexpr<NUMPY_UNARY_FUNC_SYM, E>(std::forward<E>(self));
}
template<class T>
    types::numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename types::numpy_expr_to_ndarray<types::list<T>>::type>
NUMPY_UNARY_FUNC_NAME(types::list<T> const& self)
{
    return types::numpy_uexpr<NUMPY_UNARY_FUNC_SYM, typename types::numpy_expr_to_ndarray<types::list<T>>::type>(typename types::numpy_expr_to_ndarray<types::list<T>>::type(self));
}

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

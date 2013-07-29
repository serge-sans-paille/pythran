#ifndef NUMPY_BINARY_FUNC_NAME        
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template<class E0, class E1>
typename std::enable_if<
types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E0>::type>::type>::value
and
types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E1>::type>::type>::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>
    >::type
NUMPY_BINARY_FUNC_NAME(E0 && self, E1 && other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>(std::forward<E0>(self), std::forward<E1>(other));
}

template<class E, class S>
typename std::enable_if<
types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
and
std::is_scalar<S>::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  types::broadcast<S>>
    >::type
NUMPY_BINARY_FUNC_NAME(E && self, S other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  types::broadcast<S>>(std::forward<E>(self), types::broadcast<S>(other));
}
template<class E, class S>
typename std::enable_if<
types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
and
std::is_scalar<S>::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, types::broadcast<S>, E>
    >::type
NUMPY_BINARY_FUNC_NAME(S other, E && self)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, types::broadcast<S>, E>(types::broadcast<S>(other), std::forward<E>(self));
}


#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

#ifndef NUMPY_BINARY_FUNC_NAME        
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template<class E0, class E1>
typename std::enable_if<
        is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E0>::type>::type>::value
        and
        is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E1>::type>::type>::value,
        numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>
        >::type
        NUMPY_BINARY_FUNC_NAME(E0 && self, E1 && other)
{
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>(self, other);
}

template<class E, class S>
typename std::enable_if<
        is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
        and
        std::is_scalar<S>::value,
        numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  broadcast<S>>
        >::type
        NUMPY_BINARY_FUNC_NAME(E && self, S other)
{
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  broadcast<S>>(std::forward<E>(self), broadcast<S>(other));
}
template<class E, class S>
typename std::enable_if<
        is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
        and
        std::is_scalar<S>::value,
        numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, E>
        >::type
        NUMPY_BINARY_FUNC_NAME(S other, E && self)
{
    return numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcast<S>, E>(broadcast<S>(other), std::forward<E>(self));
}


#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

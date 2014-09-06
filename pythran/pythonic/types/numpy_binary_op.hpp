#ifndef NUMPY_BINARY_FUNC_NAME
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template<class E0, class E1>
typename std::enable_if<
types::is_numexpr_arg<E0>::value
and
types::is_numexpr_arg<E1>::value
and
E0::value == E1::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>
    >::type
NUMPY_BINARY_FUNC_NAME(E0 const& self, E1 const& other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, E1>(self, other);
}

template<class E0, class E1>
typename std::enable_if<
types::is_numexpr_arg<E0>::value
and
types::is_numexpr_arg<E1>::value
and
E0::value < E1::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcasted<E0>, E1>
    >::type
NUMPY_BINARY_FUNC_NAME(E0 const& self, E1 const& other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, broadcasted<E0>, E1>(self, other);
}

template<class E0, class E1>
typename std::enable_if<
types::is_numexpr_arg<E0>::value
and
types::is_numexpr_arg<E1>::value
and
(E0::value > E1::value),
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, broadcasted<E1>>
    >::type
NUMPY_BINARY_FUNC_NAME(E0 const& self, E1 const& other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E0, broadcasted<E1>>(self, other);
}

template<class E, class S>
typename std::enable_if<
types::is_numexpr_arg<E>::value
and
(std::is_scalar<S>::value or types::is_complex<S>::value),
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  types::broadcast<typename E::dtype, S>>
    >::type
NUMPY_BINARY_FUNC_NAME(E const& self, S other)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, E,  types::broadcast<typename E::dtype, S>>(self, types::broadcast<typename E::dtype, S>(other));
}
template<class E, class S>
typename std::enable_if<
types::is_numexpr_arg<E>::value
and
(std::is_scalar<S>::value or types::is_complex<S>::value),
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM, types::broadcast<typename E::dtype, S>, E>
    >::type
NUMPY_BINARY_FUNC_NAME(S other, E const& self)
{
    return types::numpy_expr<NUMPY_BINARY_FUNC_SYM, types::broadcast<typename E::dtype, S>, E>(types::broadcast<typename E::dtype, S>(other), self);
}



#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

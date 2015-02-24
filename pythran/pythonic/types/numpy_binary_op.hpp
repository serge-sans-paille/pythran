
#ifndef NUMPY_BINARY_FUNC_NAME
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template<class E0, class E1>
typename std::enable_if<types::valid_numexpr_parameters<typename std::remove_cv<typename std::remove_reference<E0>::type>::type,
                                                        typename std::remove_cv<typename std::remove_reference<E1>::type>::type
                                                       >::value
                        and
                        types::any_array<typename std::remove_cv<typename std::remove_reference<E0>::type>::type,
                                         typename std::remove_cv<typename std::remove_reference<E1>::type>::type
                                        >::value
                        ,
                        types::numpy_expr<NUMPY_BINARY_FUNC_SYM,
                                          typename types::adapt_type<E0, E1>::type,
                                          typename types::adapt_type<E1, E0>::type
                                         >
                       >::type
NUMPY_BINARY_FUNC_NAME(E0 && self, E1 && other)
{
    return {std::forward<E0>(self), std::forward<E1>(other)};
}

#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

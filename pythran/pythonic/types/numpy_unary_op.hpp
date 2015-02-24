#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

template<class E>
typename std::enable_if<types::valid_numexpr_parameters<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
                        and
                        types::any_array<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
                        ,
                        types::numpy_expr<NUMPY_UNARY_FUNC_SYM, E>
    >::type
NUMPY_UNARY_FUNC_NAME(E && self)
{
    return {self};
}

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

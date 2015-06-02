#ifndef NUMPY_BINARY_FUNC_NAME
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

template <class E0, class E1>
typename std::enable_if<
    types::valid_numexpr_parameters<E0, E1>::value,
    types::numpy_expr<NUMPY_BINARY_FUNC_SYM,
                      typename types::adapt_type<E0, E1>::type,
                      typename types::adapt_type<E1, E0>::type>>::type
NUMPY_BINARY_FUNC_NAME(E0 const &self, E1 const &other)
{
  return {self, other};
}

#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

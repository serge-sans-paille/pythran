
#ifndef NUMPY_BINARY_FUNC_NAME
#error NUMPY_BINARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_BINARY_FUNC_SYM
#error NUMPY_BINARY_FUNC_SYM undefined
#endif

namespace proxy {

    struct NUMPY_BINARY_FUNC_NAME {
        typedef void callable;

        template<typename T0, typename T1>
        auto operator()(T0 && arg0, T1 && arg1) const
        ->  typename std::enable_if<
                not types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<T1>::type>::type>::value
                and
                not types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<T0>::type>::type>::value,
                decltype(NUMPY_BINARY_FUNC_SYM(std::forward<T0>(arg0), std::forward<T1>(arg1)))
            >::type
        {
            return NUMPY_BINARY_FUNC_SYM(std::forward<T0>(arg0), std::forward<T1>(arg1));
        }

        template<class E0, class E1>
        typename std::enable_if<types::valid_numexpr_parameters<E0, E1>::value,
                                types::numpy_expr<NUMPY_BINARY_FUNC_NAME, typename types::adapt_type<E0,E1>::type, typename types::adapt_type<E1, E0>::type>
                               >::type
        operator()(E0 const& self, E1 const& other) const
        {
            return {self, other};
        }

    };

}

#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

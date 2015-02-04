#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

namespace proxy {

    struct NUMPY_UNARY_FUNC_NAME {
        typedef void callable;

        template<typename E>
            auto operator()(E&& arg) const
            -> typename std::enable_if<
                  not types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value,
                  decltype(NUMPY_UNARY_FUNC_SYM(std::forward<E>(arg)))
               >::type
            {
                return NUMPY_UNARY_FUNC_SYM(std::forward<E>(arg));
            }

        template<class E>
            typename std::enable_if<types::valid_numexpr_parameters<E>::value,
                                    types::numpy_expr<NUMPY_UNARY_FUNC_NAME, E>
                                   >::type
            operator()(E const & self) const
            {
                return types::numpy_expr<NUMPY_UNARY_FUNC_NAME, E>(self);
            }

    };

}

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

#ifndef NUMPY_UNARY_FUNC_NAME
#error NUMPY_UNARY_FUNC_NAME undefined
#endif
#ifndef NUMPY_UNARY_FUNC_SYM
#error NUMPY_UNARY_FUNC_SYM undefined
#endif

namespace types {
    template <class Expr>
        struct is_numexpr_arg;
}

namespace proxy {

    struct NUMPY_UNARY_FUNC_NAME {
        typedef void callable;

        template<typename E>
            auto operator()(E&& arg) const
            -> typename std::enable_if<
                not types::is_numexpr_arg<
                    typename std::remove_cv<
                        typename std::remove_reference<E>::type
                        >::type
                    >::value,
                decltype(NUMPY_UNARY_FUNC_SYM(std::forward<E>(arg)))
                >::type
            {
                return NUMPY_UNARY_FUNC_SYM(std::forward<E>(arg));
            }

        template<class E>
            typename std::enable_if<
                types::is_numexpr_arg<
                    typename std::remove_cv<
                        typename std::remove_reference<E>::type
                        >::type
                    >::value,
                types::numpy_uexpr<NUMPY_UNARY_FUNC_NAME, E>
                >::type
            operator()(E const & self) const
            {
                return types::numpy_uexpr<NUMPY_UNARY_FUNC_NAME, E>(self);
            }
        template<class T>
            types::numpy_uexpr<
                NUMPY_UNARY_FUNC_NAME,
                typename types::numpy_expr_to_ndarray<
                    types::list<T>
                    >::type
                >
            operator()(types::list<T> const& self) const
            {
                using arr2list = typename types::numpy_expr_to_ndarray<
                    types::list<T>>::type;

                return types::numpy_uexpr<NUMPY_UNARY_FUNC_NAME, arr2list>(arr2list(self));
            }
    };

}

#undef NUMPY_UNARY_FUNC_NAME
#undef NUMPY_UNARY_FUNC_SYM

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
        auto operator()(T0&& arg0, T1&& arg1) const
        -> decltype(NUMPY_BINARY_FUNC_SYM(std::forward<T0>(arg0), std::forward<T1>(arg1)))
        {
            return NUMPY_BINARY_FUNC_SYM(std::forward<T0>(arg0), std::forward<T1>(arg1));
        }


        template<class E0, class E1>
            typename std::enable_if<
            types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E0>::type>::type>::value
            and
            types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E1>::type>::type>::value,
            types::numpy_expr<NUMPY_BINARY_FUNC_NAME, E0, E1>
                >::type
                operator()(E0 const& self, E1 const& other) const
                {
                    return types::numpy_expr<NUMPY_BINARY_FUNC_NAME, E0, E1>(self, other);
                }

        template<class E, class S>
            typename std::enable_if<
            types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
            and
            std::is_scalar<S>::value,
            types::numpy_expr<NUMPY_BINARY_FUNC_NAME, E,  types::broadcast<S>>
                >::type
                operator()(E const& self, S other)
                {
                    return types::numpy_expr<NUMPY_BINARY_FUNC_NAME, E,  types::broadcast<S>>(self, types::broadcast<S>(other));
                }
        template<class E, class S>
            typename std::enable_if<
            types::is_numexpr_arg<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
            and
            std::is_scalar<S>::value,
            types::numpy_expr<NUMPY_BINARY_FUNC_NAME, types::broadcast<S>, E>
                >::type
                operator()(S other, E const& self)
                {
                    return types::numpy_expr<NUMPY_BINARY_FUNC_NAME, types::broadcast<S>, E>(types::broadcast<S>(other), self);
                }
    };

}

#undef NUMPY_BINARY_FUNC_NAME
#undef NUMPY_BINARY_FUNC_SYM

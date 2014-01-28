#ifndef PYTHONIC_UTILS_NUMPY_CONVERSION_HPP
#define PYTHONIC_UTILS_NUMPY_CONVERSION_HPP

#define NUMPY_EXPR_TO_NDARRAY0(fname)\
    template<class Op, class Arg, class... Types>\
auto fname(types::numpy_uexpr<Op,Arg> const& expr, Types... others)\
-> decltype(fname(typename types::numpy_expr_to_ndarray<types::numpy_uexpr<Op,Arg>>::type(expr), std::forward<Types>(others)...)) \
{\
    return fname(typename types::numpy_expr_to_ndarray<types::numpy_uexpr<Op,Arg>>::type(expr), std::forward<Types>(others)...);\
}\
template<class Op, class Arg0, class Arg1, class... Types>\
auto fname(types::numpy_expr<Op,Arg0, Arg1> const& expr, Types... others)\
-> decltype(fname(typename types::numpy_expr_to_ndarray<types::numpy_expr<Op,Arg0,Arg1>>::type(expr), std::forward<Types>(others)...)) \
{\
    return fname(typename types::numpy_expr_to_ndarray<types::numpy_expr<Op,Arg0, Arg1>>::type(expr), std::forward<Types>(others)...);\
}\
template<class T, class... Types>\
auto fname(types::list<T> const& expr, Types... others)\
-> decltype(fname(typename types::numpy_expr_to_ndarray<types::list<T>>::type(expr), std::forward<Types>(others)...)) \
{\
    return fname(typename types::numpy_expr_to_ndarray<types::list<T>>::type(expr), std::forward<Types>(others)...);\
}


#endif

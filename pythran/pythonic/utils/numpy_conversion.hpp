#ifndef PYTHONIC_UTILS_NUMPY_CONVERSION_HPP
#define PYTHONIC_UTILS_NUMPY_CONVERSION_HPP

#define NUMPY_EXPR_TO_NDARRAY0(fname)\
template<class E, class... Types>\
auto fname(E const& expr, Types&&... others)\
-> typename std::enable_if<not types::is_ndarray<E>::value and types::is_array<E>::value, decltype(fname(typename types::numpy_expr_to_ndarray<E>::type(expr), std::forward<Types>(others)...))>::type \
{\
    return fname(typename types::numpy_expr_to_ndarray<E>::type(expr), std::forward<Types>(others)...);\
}\


#endif

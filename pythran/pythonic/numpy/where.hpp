#ifndef PYTHONIC_NUMPY_WHERE_HPP
#define PYTHONIC_NUMPY_WHERE_HPP

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/numpy/nonzero.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic {

    namespace numpy {

        /* cas : array_like, array_like, array_like */
        template<class E, class X, class Y>
            typename std::enable_if<types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<
                decltype(std::declval<
                        typename utils::nested_container_value_type<
                        typename std::remove_reference<typename std::remove_cv<X>::type>::type,
                        types::is_numexpr_arg<
                        typename std::remove_reference<typename std::remove_cv<X>::type>::type
                        >::value * std::numeric_limits<size_t>::max()
                        >::type>() +
                        std::declval<
                        typename utils::nested_container_value_type<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type,
                        types::is_numexpr_arg<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                        >::value * std::numeric_limits<size_t>::max()
                        >::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<E>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto condition = asarray(e);
                    auto x_ = asarray(x);
                    auto y_ = asarray(y);
                    types::ndarray<
                        decltype(std::declval<
                                typename utils::nested_container_value_type<
                                typename std::remove_reference<typename std::remove_cv<X>::type>::type
                                >::type>() +
                                std::declval<
                                typename utils::nested_container_value_type<
                                typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                                >::type>()),
                        utils::nested_container_depth<
                            typename std::remove_reference<typename std::remove_cv<E>::type>::type
                            >::value
                            > out(condition.shape, __builtin__::None);
                    auto out_iter = out.fbegin();
                    for(long i=0, n=condition.size(); i<n; ++i) {
                        if(*(condition.fbegin()+i))
                            *out_iter++ = *(x_.fbegin()+i);
                        else
                            *out_iter++ = *(y_.fbegin()+i);
                    }
                    return out;
                }

        /* cas : array_like, value, array_like */
        template<class E, class X, class Y>
            typename std::enable_if<types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<
                decltype(std::declval<X>() +
                        std::declval<
                        typename utils::nested_container_value_type<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type,
                        types::is_numexpr_arg<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                        >::value * std::numeric_limits<size_t>::max()>::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<E>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto condition = asarray(e);
                    auto y_ = asarray(y);
                    types::ndarray<
                        decltype(std::declval<X>() +
                                std::declval<
                                typename utils::nested_container_value_type<
                                typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                                >::type>()),
                        utils::nested_container_depth<
                            typename std::remove_reference<typename std::remove_cv<E>::type>::type
                            >::value
                            > out(condition.shape, __builtin__::None);
                    auto out_iter = out.buffer;
                    for(long i=0, n=condition.size(); i<n; ++i) {
                        if(*(condition.fbegin()+i))
                            *out_iter++ = x;
                        else
                            *out_iter++ = *(y_.fbegin()+i);
                    }
                    return out;
                }

        /* cas : array_like, array_like, value */
        template<class E, class X, class Y>
            typename std::enable_if<types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<
                decltype(std::declval<Y>() +
                        std::declval<
                        typename utils::nested_container_value_type<
                        typename std::remove_reference<typename std::remove_cv<X>::type>::type,
                        types::is_numexpr_arg<
                        typename std::remove_reference<typename std::remove_cv<X>::type>::type
                        >::value * std::numeric_limits<size_t>::max()
                        >::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<E>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto condition = asarray(e);
                    auto x_ = asarray(x);
                    types::ndarray<
                        decltype(std::declval<Y>() +
                                std::declval<
                                typename utils::nested_container_value_type<
                                typename std::remove_reference<typename std::remove_cv<X>::type>::type
                                >::type>()),
                        utils::nested_container_depth<
                            typename std::remove_reference<typename std::remove_cv<E>::type>::type
                            >::value
                            > out(condition.shape, __builtin__::None);
                    auto out_iter = out.buffer;
                    for(long i=0, n=condition.size(); i<n; ++i) {
                        if(*(condition.fbegin()+i))
                            *out_iter++ = *(x_.fbegin()+i);
                        else
                            *out_iter++ = y;
                    }
                    return out;
                }

        /* cas : array_like, value, value */
        template<class E, class X, class Y>
            typename std::enable_if<types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<
                decltype(std::declval<Y>() + std::declval<X>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<E>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto condition = asarray(e);
                    types::ndarray<
                        decltype(std::declval<Y>() + std::declval<X>()),
                        utils::nested_container_depth<
                            typename std::remove_reference<typename std::remove_cv<E>::type>::type
                            >::value
                            > out(condition.shape, __builtin__::None);
                    auto out_iter = out.buffer;
                    for(long i=0, n=condition.size(); i<n; ++i) {
                        if(*(condition.fbegin()+i))
                            *out_iter++ = x;
                        else
                            *out_iter++ = y;
                    }
                    return out;
                }

        /* cas : value, value, array_like */
        template<class E, class X, class Y>
            typename std::enable_if<!types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<
                decltype(std::declval<X>() +
                        std::declval<
                        typename utils::nested_container_value_type<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type,
                        types::is_numexpr_arg<
                        typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                        >::value * std::numeric_limits<size_t>::max()
                        >::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<Y>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto y_ = asarray(y);
                    if(e)
                        return types::ndarray<
                            decltype(std::declval<X>() +
                                    std::declval<
                                    typename utils::nested_container_value_type<
                                    typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                                    >::type>()),
                            utils::nested_container_depth<
                                typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                                >::value
                                >(y_.shape, x);
                    else
                        return copy(y_);
                }

        /* cas : value, array_like, value */
        template<class E, class X, class Y>
            typename std::enable_if<!types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            !types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<decltype(std::declval<Y>() +
                    std::declval<
                    typename utils::nested_container_value_type<
                    typename std::remove_reference<typename std::remove_cv<X>::type>::type,
                    types::is_numexpr_arg<
                    typename std::remove_reference<typename std::remove_cv<X>::type>::type
                    >::value * std::numeric_limits<size_t>::max()
                    >::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<
                typename std::remove_reference<typename std::remove_cv<X>::type>::type
                >::value,
            typename std::remove_reference<typename std::remove_cv<X>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    auto x_ = asarray(x);
                    if(e)
                        return copy(x_);
                    else
                        return types::ndarray<decltype(std::declval<Y>() + std::declval<typename utils::nested_container_value_type<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::type>()), utils::nested_container_depth<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value>(x_.shape, y);
                }

        /* cas : value, array_like, array_like */
        template<class E, class X, class Y>
            typename std::enable_if<!types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<E>::type>::type>::value && 
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value &&
            types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<Y>::type>::type>::value,
            types::ndarray<decltype(std::declval<
                    typename utils::nested_container_value_type<
                    typename std::remove_reference<typename std::remove_cv<Y>::type>::type,
                    types::is_numexpr_arg<
                    typename std::remove_reference<typename std::remove_cv<Y>::type>::type
                    >::value * std::numeric_limits<size_t>::max()>::type>() +
                    std::declval<
                    typename utils::nested_container_value_type<
                    typename std::remove_reference<typename std::remove_cv<X>::type>::type,
                    types::is_numexpr_arg<
                    typename std::remove_reference<typename std::remove_cv<X>::type>::type
                    >::value * std::numeric_limits<size_t>::max()>::type>()),
            utils::nested_container_depth<
                typename std::conditional<
                types::is_numexpr_arg<typename std::remove_reference<typename std::remove_cv<X>::type>::type>::value,
            typename std::remove_reference<typename std::remove_cv<X>::type>::type,
            bool
                >::type
                >::value>
                >::type where(E const& e, X const& x, Y const& y) {
                    if(e)
                        return copy(asarray(x));
                    else
                        return copy(asarray(y));
                }

        template<class E>
            auto where(E const& expr) -> types::array<types::ndarray<long,1>, types::numpy_expr_to_ndarray<E>::N>
            {
                return nonzero(expr);
            }

        PROXY(pythonic::numpy, where)

    }

}

#endif


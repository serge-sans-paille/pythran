// switch.hpp
//
// Copyright (c) 2006-2008
// Steven Watanabe
//
// Distriuted under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost/org/LICENSE_1_0.txt)

#ifndef BOOST_CONTROL_SWITCH_HPP_INCLUDED
#define BOOST_CONTROL_SWITCH_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/preprocessor/config/limits.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>

#ifndef BOOST_SWITCH_LIMIT
    #define BOOST_SWITCH_LIMIT 50
#endif

#if BOOST_SWITCH_LIMIT > BOOST_PP_LIMIT_REPEAT
    #error BOOST_SWITCH_LIMIT exceeds Boost.Preprocessor limit
#endif
#if BOOST_SWITCH_LIMIT > BOOST_PP_LIMIT_ITERATION
    #error BOOST_SWITCH_LIMIT exceeds Boost.Preprocessor limit
#endif

namespace boost {

namespace control {

namespace switch_detail {

// Avoid the need to create all the specializations of switch_impl
// twice. Just pass this to switch_impl<N>::apply(...) when no
// default is supplied.

template<class R>
struct default_construct {
    template<class Int>
    R operator()(Int) const {
        return(R());
    }
};

// N is the number of cases not including the default
template<int N>
struct switch_impl;

// specialize for 0 separately to avoid warnings
template<>
struct switch_impl<0> {
    template<class R, class Int, class S, class Default>
    static R
    apply(Int i, S&, Default d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {
        return(d(i));
    }
};

template<class R, class L, class T>
R do_call(T& t) {
    return(t.template apply<R>(L()));
}

template<int N>
struct mpl_at_c_impl {
    template<class T>
    struct apply {
        typedef typename mpl::next<typename mpl_at_c_impl<N - 1>::template apply<T>::type>::type type;
    };
};

template<>
struct mpl_at_c_impl<0> {
    template<class T>
    struct apply {
        typedef T type;
    };
};

template<class T, class R>
struct internal_at {
    template<int N>
    struct apply {
        typedef typename mpl::deref<typename mpl_at_c_impl<N>::template apply<typename mpl::begin<typename T::labels>::type>::type>::type label;
        static R call(T& t) {
            return(do_call<R, label>(t));
        }
        static bool fallthrough() { return(false); }
    };
};

template<class T>
struct size : mpl::size<typename T::labels> {};

#define BOOST_SWITCH_CASE(z, n, data)           \
    {                                           \
    typedef typename impl::template apply<n> c; \
    case c::label::value:                       \
        if(!c::fallthrough())                   \
            return(c::call(s));                 \
        else c::call(s);                        \
    }

#define BOOST_SWITCH_IMPL(z, n, data)                                   \
    template<>                                                          \
    struct switch_impl<n> {                                             \
        template<class R, class I, class S, class D>                    \
        static R                                                        \
        apply(I i, S& s, D d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {  \
            typedef internal_at<S, R> impl;                             \
            switch(i) {                                                 \
                BOOST_PP_REPEAT_##z(n, BOOST_SWITCH_CASE, ~)            \
                default: return(d(i));                                  \
            }                                                           \
        }                                                               \
    };

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_SWITCH_LIMIT)
#define BOOST_PP_LOCAL_MACRO(n) BOOST_SWITCH_IMPL(1, n, ~)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_SWITCH_IMPL
#undef BOOST_SWITCH_CASE

// N is the number of cases not including the default
template<int N>
struct range_switch_impl;

// specialize for 0 separately to avoid warnings
template<>
struct range_switch_impl<0> {
    template<class R, class T, T low, T high, class I, class F, class D>
    static R apply(I i, F, D d) {
        return(d(i));
    }
};

#define BOOST_SWITCH_RANGE_CASE(z, n, data)                     \
    case data + n: return(f(mpl::integral_c<T, data + n>()));

#define BOOST_SWITCH_RANGE_SWITCH_IMPL(z, n, data)                          \
    template<>                                                              \
    struct range_switch_impl<n> {                                           \
        template<class R, class T, T low, T high, class I, class F, class D>\
        static R apply(I i, F f, D d) {                                     \
            switch(i) {                                                     \
                BOOST_PP_REPEAT_##z(n, BOOST_SWITCH_RANGE_CASE, low)        \
                default: return(d(i));                                      \
            }                                                               \
        }                                                                   \
    };

#define BOOST_PP_LOCAL_LIMITS (1, BOOST_SWITCH_LIMIT)
#define BOOST_PP_LOCAL_MACRO(n) BOOST_SWITCH_RANGE_SWITCH_IMPL(1, n, ~)
#include BOOST_PP_LOCAL_ITERATE()

#undef BOOST_SWITCH_RANGE_SWITCH_IMPL
#undef BOOST_SWITCH_RANGE_CASE


}

template<class R, class N, class S>
inline R switch_(N n, S s BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {
    typedef switch_detail::switch_impl<switch_detail::size<S>::value> impl;
    switch_detail::default_construct<R> default_;
    return(impl::template apply<R>(n, s, default_));
}

template<class R, class N, class S, class D>
inline R switch_(N n, S s, D d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {
    typedef switch_detail::switch_impl<switch_detail::size<S>::value> impl;
    return(impl::template apply<R>(n, s, d));
}

} // namespace control

} // namespace boost

#endif

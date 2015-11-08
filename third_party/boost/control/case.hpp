// case.hpp
//
// Copyright (c) 2008
// Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTROL_CASE_HPP_INCLUDED
#define BOOST_CONTROL_CASE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/range_c.hpp>

namespace boost {

namespace control {

namespace switch_detail {

// N is the number of cases not including the default
template<int N>
struct range_switch_impl;

struct empty_set {
    template<class T>
    static char lookup(T);
};

template<class Base, class T>
struct set : Base {
    static char (&lookup(T))[2];
    using Base::lookup;
    typedef set type;
};

template<int N>
struct make_set {
    template<class Iter>
    struct apply {
        typedef set<typename make_set<N - 1>::template apply<typename boost::mpl::next<Iter>::type>::type, typename boost::mpl::deref<Iter>::type> type;
    };
};

template<>
struct make_set<0> {
    template<class Iter>
    struct apply {
        typedef empty_set type;
    };
};

template<class S, class N>
struct contains_impl {
    typedef typename make_set<boost::mpl::size<S>::value>::template apply<typename boost::mpl::begin<S>::type>::type as_set;
    static const bool value = (sizeof(as_set::lookup(N())) != 1);
};
template<class T, int low, int high, class N>
struct contains_impl<mpl::range_c<T, low, high>, N> {
    static const bool value = (low <= (N::value)) && ((N::value) < high);
};

}

template<class Case>
class restrict_case_t {
public:
    template<class T>
    explicit restrict_case_t(T& t) : impl(t) {}
    typedef typename Case::labels labels;
    template<class R, class N>
    typename boost::enable_if_c<
        switch_detail::contains_impl<typename Case::labels, N>::value,
        R
    >::type apply(N n) const {
        return(impl.template apply<R>(n));
    }
    const Case& get() const {
        return(impl);
    }
private:
    Case impl;
};

template<class Case1, class Case2>
class binary_case_t : public Case1, public Case2 {
public:
    template<class T>
    explicit binary_case_t(const T& t) : Case1(t), Case2(t) {}
    binary_case_t(const Case1& case1, const Case2& case2) :
        Case1(case1),
        Case2(case2) {}
    // msvc does not like mpl::joint_view
    // if the labels are not reversed.
    typedef typename mpl::joint_view<
        typename Case2::labels,
        typename Case1::labels
    > labels;
    using Case1::apply;
    using Case2::apply;
};

template<class N, class F>
class single_case_t {
public:
    single_case_t(F f) : impl(f) {}
    typedef mpl::single_view<N> labels;
    template<class R>
    R apply(N n) const {
        return(impl(n));
    }
private:
    F impl;
};

template<class S, class F>
class case_group_t {
public:
    case_group_t(F f) : impl(f) {}
    typedef S labels;
    template<class R, class N>
    R apply(N n) const {
        return(impl(n));
    }
    const F& get() const {
        return(impl);
    }
private:
    F impl;
};

template<class F>
struct add_to_group {
    template<class Prev, class Current>
    struct apply {
        typedef binary_case_t<Prev, single_case_t<Current, F> > type;
    };
};

template<class Case>
class expression_template_case_t {
public:
    typedef typename Case::labels labels;
    template<class T>
    explicit expression_template_case_t(T& t) : impl(t) {}
    template<class T0, class T1>
    expression_template_case_t(T0& t0, T1& t1) : impl(t0, t1) {}
    template<class R, class N>
    R apply(N n) const {
        return(impl.template apply<R>(n));
    }
    Case& get() { return(impl); }
    const Case& get() const { return(impl); }
private:
    Case impl;
};

// allows a Case to be used in the expression template
// framework.
template<class Case>
expression_template_case_t<restrict_case_t<Case> > make_case(Case& c) {
    return(expression_template_case_t<restrict_case_t<Case> >(c));
}

template<class Case1, class Case2>
expression_template_case_t<binary_case_t<Case1, Case2> >
operator,(const expression_template_case_t<Case1>& c1,
          const expression_template_case_t<Case2>& c2) {
    return(expression_template_case_t<binary_case_t<Case1, Case2> >(
        c1.get(), c2.get()));
}

template<class S, class F>
expression_template_case_t<restrict_case_t<case_group_t<S,F> > > case_(F f) {
 return(expression_template_case_t<restrict_case_t<case_group_t<S,F> > >(f));
}

template<int N, class F>
expression_template_case_t<single_case_t<mpl::int_<N>, F> > case_c(F f) {
    return(expression_template_case_t<single_case_t<mpl::int_<N>, F> >(f));
}

template<int L, int H, class F>
expression_template_case_t<restrict_case_t<case_group_t<mpl::range_c<int, L, H>, F> > > case_range_c(F f) {
    return(expression_template_case_t<restrict_case_t<case_group_t<mpl::range_c<int, L, H>, F> > >(f));
}


template<class R, class N, class T, T low, T high, class F>
inline R switch_(N n, expression_template_case_t<restrict_case_t<case_group_t<mpl::range_c<T, low, high>, F> > > cases BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {
    typedef switch_detail::range_switch_impl<high - low> impl;
    switch_detail::default_construct<R> default_;
    return(impl::template apply<R, T, low, high>(n, cases.get().get().get(), default_));
}

template<class R, class N, class T, T low, T high, class F, class D>
inline R switch_(N n, expression_template_case_t<restrict_case_t<case_group_t<mpl::range_c<T, low, high>, F> > > cases, D d BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(R)) {
    typedef switch_detail::range_switch_impl<high - low> impl;
    return(impl::template apply<R, T, low, high>(n, cases.get().get().get(), d));
}

} // namespace control

} // namespace boost

#endif

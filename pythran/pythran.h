#ifndef PYTHRAN_H
#define PYTHRAN_H

#include <pythonic++.h>

/* boost::python converters */
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/stl_iterator.hpp>
template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template <class T>
struct fwd {
    typedef T type;
    type operator()(T t) { return t; }
};
template <>
struct fwd<void> {
    typedef void type;
};

template <class... Types >
struct fwd< std::tuple<Types...> > {
    typedef boost::python::tuple type; 
    template<int ...S>
        type dispatch( std::tuple<Types...> const & t, seq<S...>) {
            return boost::python::make_tuple( fwd<Types>()(std::get<S>(t)) ...);
        }

    type operator()( std::tuple<Types...> const & t) {
        return this->dispatch(t, typename gens< sizeof...(Types) >::type());
    }
};

template <class E>
struct fwd< sequence<E> >  {
    typedef boost::python::list type;
    type operator()(sequence<E> s) {
        boost::python::list l;
        fwd<E> f;
        for(auto & e: s) l.append(f(e));
        return l;
    }
};

template <>
struct fwd< xrange >  {
    typedef boost::python::list type;
    type operator()(xrange xr) {
        boost::python::list l;
        for(auto & e: xr) l.append(e);
        return l;
    }
};

template< class T >
T to_sequence(boost::python::list const & l) {
    T s;
    boost::python::stl_input_iterator<typename T::value_type> begin(l), end;
    std::copy(begin, end, std::back_inserter(s));
    return s;
}

template<class T, int ...S>
T _to_tuple(boost::python::tuple const & bt, seq<S...>) {
     return std::make_tuple( fwd< typename std::tuple_element<S,T>::type>()(boost::python::extract< typename std::tuple_element<S,T>::type >(bt[S]))...);
}
template< class T >
T to_tuple(boost::python::tuple const & t) {
    return _to_tuple<T>(t, typename gens< std::tuple_size<T>::value >::type());
}

template <class T, class R = typename T::return_type >
struct Fwd : T {
    template<class... Types>
    typename fwd<R>::type operator()(Types... arguments) { return fwd<R>()(T::operator()(arguments...)); }
};

template <class T>
struct Fwd<T,void> : T {
    template<class... Types>
    void operator()(Types... arguments) { T::operator()(arguments...); }
};

#endif

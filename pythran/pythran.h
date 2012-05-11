#ifndef PYTHRAN_H
#define PYTHRAN_H

#include <pythonic++.h>
using namespace pythonic;

/* some overloads */
namespace std {
    template <size_t I, class T>
        auto get( sequence<T>& t) -> decltype(t[I]) { return t[I]; }

    template <size_t I, class T>
        struct tuple_element<I, sequence<T> > {
            typedef typename sequence<T>::value_type type;
        };
}
namespace pythonic {
    namespace proxy {
        struct bind0 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> decltype(std::bind(op, types...)) {
                    return std::bind(op, types...); 
                }
        };
        struct bind1 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> decltype(std::bind(op, types..., std::placeholders::_1)) {
                    return std::bind(op, types..., std::placeholders::_1); 
                }
        };
        struct bind2 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2)) {
                    return std::bind(op, types..., std::placeholders::_1, std::placeholders::_2); 
                }
        };
        struct bind3 {
            template<typename Operator, typename... Types>
                auto operator()(Operator const& op, Types &&... types) -> decltype(std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) {
                    return std::bind(op, types..., std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); 
                }
        };
    }
}

template <class T>
void __append(sequence<T>& s, T const & value) {
    s.push_back(value);
}

template<class T>
struct content_of {
    typedef typename T::value_type type;
};

/* boost::python converters */
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>
#include <boost/python/stl_iterator.hpp>
template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template <class T>
struct to_python {
    typedef T type;
    type operator()(T t) { return t; }
};
template <>
struct to_python<void> {
    typedef void type;
};

template <class... Types >
struct to_python< std::tuple<Types...> > {
    typedef boost::python::tuple type; 
    template<int ...S>
        type dispatch( std::tuple<Types...> const & t, seq<S...>) {
            return boost::python::make_tuple( to_python<Types>()(std::get<S>(t)) ...);
        }

    type operator()( std::tuple<Types...> const & t) {
        return this->dispatch(t, typename gens< sizeof...(Types) >::type());
    }
};

template <class E>
struct to_python< sequence<E> >  {
    typedef boost::python::list type;
    type operator()(sequence<E> s) {
        boost::python::list l;
        to_python<E> f;
        for(auto & e: s) l.append(f(e));
        return l;
    }
};
template <>
struct to_python< empty_sequence >  {
    typedef boost::python::list type;
    type operator()(empty_sequence const& s) {
        return boost::python::list();
    }
};

template <>
struct to_python< xrange >  {
    typedef boost::python::list type;
    type operator()(xrange xr) {
        boost::python::list l;
        for(auto & e: xr) l.append(e);
        return l;
    }
};

template <class T>
struct to_python< none<T> >  {
    typedef boost::python::object type;
    type operator()(none<T> n) {
        if(n.is_none) return type(); // this is the way boost python encodes Py_None
        else return to_python<T>()(n.data);
    }
};
template <>
struct to_python< none_type >  {
    typedef boost::python::object type;
    type operator()(none_type) {
        return type(); // this is the way boost python encodes Py_None
    }
};

template <class T>
struct from_python_type {
    typedef T type;
};

template <class T>
struct from_python_type<sequence<T>> {
    typedef T type;
};

template <class... Types>
struct from_python_type<sequence<std::tuple<Types...>>> {
    typedef boost::python::tuple type;
};

template <class T>
struct from_python_type<sequence<sequence<T>>> {
    typedef boost::python::list type;
};

template <class T>
struct from_python {
    typedef typename from_python_type<T>::type type;
    auto operator()(T const & t) ->decltype(t) { return t; }

    T operator()(boost::python::list const & l) {
        T s;
        boost::python::stl_input_iterator<type> begin(l), end;
        for(auto iter = begin; iter!=end; ++iter)
            s.push_back( from_python< typename T::value_type > () (*iter) );
        return s;
    }

    template<int ...S>
        T operator()(boost::python::tuple const & bt, seq<S...>) {
            return std::make_tuple( from_python< typename std::tuple_element<S,T>::type>()(boost::python::extract< typename std::tuple_element<S,T>::type >(bt[S]))...);
        }

    T operator()(boost::python::tuple const & t) {
        return operator()(t, typename gens< std::tuple_size<T>::value >::type());
    }
};

template <class T, class R = typename T::return_type >
struct ToPython : T {
    template<class... Types>
    typename to_python<R>::type operator()(Types... arguments) { return to_python<R>()(T::operator()(arguments...)); }
};

template <class T>
struct ToPython<T,void> : T {
    template<class... Types>
    void operator()(Types... arguments) { T::operator()(arguments...); }
};

#endif

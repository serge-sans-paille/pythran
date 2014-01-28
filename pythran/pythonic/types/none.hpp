#ifndef PYTHONIC_TYPES_NONE_HPP
#define PYTHONIC_TYPES_NONE_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/__builtin__/id.hpp"

#include <iterator>
#include <cassert>
#include <complex>

namespace pythonic {

    namespace types {

        static const intptr_t NONE_ID = 0x1331;

        struct none_type { none_type(){} intptr_t id() const { return NONE_ID; } };

        /* Type adapator to simulate an option type
         *
         * see http://en.wikipedia.org/wiki/Option_type
         */
        template<class T>
            struct none : T {

                bool is_none;  // set to true if the type is none

                none(none_type const&) : T(), is_none(true) {}

                template<class... Types>
                    none(Types &&... args) : T(std::forward<Types>(args)...), is_none(false) {}

                bool operator==(none_type const &) const {
                    return is_none;
                }

                template <class O>
                    bool operator==(O const & t) const {
                        return not is_none and static_cast<T&>(*this) == t;
                    }

                operator bool() const {
                    return not is_none and static_cast<T&>(*this);
                }

                intptr_t id() const {
                    return is_none ?
                        NONE_ID :
                        __builtin__::id(*static_cast<T*>(this));
                }
            };

        /* specialization of none for integral types we cannot derive from
        */
#define SPECIALIZE_NONE(T)\
        template<>\
        class none<T> {\
            T data;\
            friend std::ostream& operator<<(std::ostream&, none<T> const &);\
            friend T operator+(none<T> const& t0, T const &t1)         ;\
            friend T operator+(T const &t0, none<T> const& t1)         ;\
            friend T operator+(none<T> const &t0, none<T> const& t1)   ;\
            friend T operator>(none<T> const& t0, T const &t1)         ;\
            friend T operator>(T const &t0, none<T> const& t1)         ;\
            friend T operator>(none<T> const &t0, none<T> const& t1)   ;\
            friend T operator>=(none<T> const& t0, T const &t1)        ;\
            friend T operator>=(T const &t0, none<T> const& t1)        ;\
            friend T operator>=(none<T> const &t0, none<T> const& t1)  ;\
            friend T operator<(none<T> const& t0, T const &t1)         ;\
            friend T operator<(T const &t0, none<T> const& t1)         ;\
            friend T operator<(none<T> const &t0, none<T> const& t1)   ;\
            friend T operator<=(none<T> const& t0, T const &t1)        ;\
            friend T operator<=(T const &t0, none<T> const& t1)        ;\
            friend T operator<=(none<T> const &t0, none<T> const& t1)  ;\
            friend T operator-(none<T> const& t0, T const &t1)         ;\
            friend T operator-(T const &t0, none<T> const& t1)         ;\
            friend T operator-(none<T> const &t0, none<T> const& t1)   ;\
            friend T operator*(none<T> const& t0, T const &t1)         ;\
            friend T operator*(T const &t0, none<T> const& t1)         ;\
            friend T operator*(none<T> const &t0, none<T> const& t1)   ;\
            friend T operator/(none<T> const& t0, T const &t1)         ;\
            friend T operator/(T const &t0, none<T> const& t1)         ;\
            friend T operator/(none<T> const &t0, none<T> const& t1)   ;\
            public:\
                   bool is_none;\
            none() : data(), is_none(false) {}\
            none(none_type const&) : data(), is_none(true) {}\
            none(T const& data) : data(data), is_none(false) {}\
            bool operator==(none_type const &) const { return is_none; }\
            template <class O>\
            bool operator==(O const & t) const { return not is_none and data == t; }\
            operator bool() const { return not is_none and data; }\
            operator size_t() const { return data; }\
            operator long() const { return data; }\
            operator long long() const { return data; }\
            operator double() const { return data; }\
            T& operator=(T const& t) { is_none = false ; return data = t; }\
            intptr_t id() const { return is_none ? NONE_ID : reinterpret_cast<intptr_t>(&data); } \
        };\
        T operator+(none<T> const& t0, T const &t1)         { return t0.data + t1     ; }\
        T operator+(T const &t0, none<T> const& t1)         { return t0      + t1.data; }\
        T operator+(none<T> const &t0, none<T> const& t1)   { return t0.data + t1.data; }\
        T operator>(none<T> const& t0, T const &t1)         { return t0.data > t1     ; }\
        T operator>(T const &t0, none<T> const& t1)         { return t0      > t1.data; }\
        T operator>(none<T> const &t0, none<T> const& t1)   { return t0.data > t1.data; }\
        T operator>=(none<T> const& t0, T const &t1)        { return t0.data >= t1    ; }\
        T operator>=(T const &t0, none<T> const& t1)        { return t0      >= t1.data;}\
        T operator>=(none<T> const &t0, none<T> const& t1)  { return t0.data >= t1.data;}\
        T operator<(none<T> const& t0, T const &t1)         { return t0.data < t1     ; }\
        T operator<(T const &t0, none<T> const& t1)         { return t0      < t1.data; }\
        T operator<(none<T> const &t0, none<T> const& t1)   { return t0.data < t1.data; }\
        T operator<=(none<T> const& t0, T const &t1)        { return t0.data <= t1    ; }\
        T operator<=(T const &t0, none<T> const& t1)        { return t0      <= t1.data;}\
        T operator<=(none<T> const &t0, none<T> const& t1)  { return t0.data <= t1.data;}\
        T operator-(none<T> const& t0, T const &t1)         { return t0.data - t1     ; }\
        T operator-(T const &t0, none<T> const& t1)         { return t0      - t1.data; }\
        T operator-(none<T> const &t0, none<T> const& t1)   { return t0.data - t1.data; }\
        T operator*(none<T> const& t0, T const &t1)         { return t0.data * t1     ; }\
        T operator*(T const &t0, none<T> const& t1)         { return t0      * t1.data; }\
        T operator*(none<T> const &t0, none<T> const& t1)   { return t0.data * t1.data; }\
        T operator/(none<T> const& t0, T const &t1)         { return t0.data / t1     ; }\
        T operator/(T const &t0, none<T> const& t1)         { return t0      / t1.data; }\
        T operator/(none<T> const &t0, none<T> const& t1)   { return t0.data / t1.data; }\
        std::ostream& operator<<(std::ostream& os, none<T> const & v) { if(v.is_none) return os << "None"; else return os << v.data; }

        SPECIALIZE_NONE(size_t);
        SPECIALIZE_NONE(long);
        SPECIALIZE_NONE(long long);
        SPECIALIZE_NONE(double);

        template<class T> struct none;
        template<class T>
            struct is_none {
                static const bool value = false;
            };
        template<class T>
            struct is_none<none<T>> {
                static const bool value = true;
            };

    }

    template<class T>
        struct assignable< types::none<T> >{
            typedef types::none<typename assignable<T>::type > type;
        };
}

/* type inference stuff { */
#include "pythonic/types/combined.hpp"

/*
   template <class A>
   struct __combined<container<A> , pythonic::types::none_type > {
   typedef typename __combined<pythonic::types::list<A>, pythonic::types::none_type>::type type;
   };

   template <class A>
   struct __combined<pythonic::types::none_type , container<A> > {
   typedef typename __combined<pythonic::types::list<A>, pythonic::types::none_type>::type type;
   };
   */

template<class T0, class T1>
struct __combined<pythonic::types::none<T0>, T1> : std::enable_if<!pythonic::types::is_none<T1>::value, pythonic::dummy>::type {
    typedef pythonic::types::none<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<T1, pythonic::types::none<T0>> : std::enable_if<!pythonic::types::is_none<T0>::value, pythonic::dummy>::type {
    typedef pythonic::types::none<typename __combined<T0,T1>::type> type;
};
template<class T0, class T1>
struct __combined<pythonic::types::none<T1>, pythonic::types::none<T0>>  {
    typedef pythonic::types::none<typename __combined<T0,T1>::type> type;
};

template<class T>
struct __combined<typename std::enable_if<!pythonic::types::is_none<T>::value, pythonic::types::none_type>::type, T> {
    typedef pythonic::types::none<T> type;
};

template<class T>
struct __combined<T, typename std::enable_if<!pythonic::types::is_none<T>::value, pythonic::types::none_type>::type> {
    typedef pythonic::types::none<T> type;
};

template<>
struct __combined<pythonic::types::none_type, pythonic::types::none_type>  {
    typedef pythonic::types::none_type type;
};

/* } */
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#include <boost/python/object.hpp>

namespace pythonic {
    struct custom_none_type_to_none {
        static PyObject* convert(types::none_type const&) {
            return boost::python::incref(boost::python::object().ptr());
        }
    };

    template<>
        struct pythran_to_python<types::none_type> {
            pythran_to_python() {
                register_once<types::none_type, custom_none_type_to_none >();
            }
        };
    template <typename T>
        struct custom_none_to_any {
            static PyObject* convert( types::none<T> const& n) {
                if(n.is_none) return boost::python::incref(boost::python::object().ptr());
                else return boost::python::incref(boost::python::object(static_cast<T const&>(n)).ptr());
            }
        };

    template<typename T>
        struct pythran_to_python< types::none<T> > {
            pythran_to_python() {
                pythran_to_python<T>();
                register_once<types::none<T>, custom_none_to_any<T>>();
            }
        };
}

#endif

#endif

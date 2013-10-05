#ifndef PYTHONIC_NONE_H
#define PYTHONIC_NONE_H

#include <iterator>
#include <complex>

namespace pythonic {

    struct none_type { none_type(){} };

    namespace __builtin__ {
        extern none_type const None; // forward declaration
        template<class T> intptr_t id(T const&);
    }


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

            intptr_t id() const { return __builtin__::id<T>(this); }
        };

    /* specialization of none for integrat types we cannot derive from
     */
#define SPECIALIZE_NONE(T)\
    template<>\
    class none<T> {\
        T data;\
        template<class F> \
        friend std::ostream& operator<<(std::ostream&, none<F> const &);\
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
        intptr_t id() const { return is_none ? reinterpret_cast<intptr_t>(&__builtin__::None) : reinterpret_cast<intptr_t>(&data); } \
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
    T operator/(none<T> const &t0, none<T> const& t1)   { return t0.data / t1.data; }

    SPECIALIZE_NONE(size_t);
    SPECIALIZE_NONE(long);
    SPECIALIZE_NONE(long long);
    SPECIALIZE_NONE(double);
}

#endif

#ifndef PYTHONIC_NONE_H
#define PYTHONIC_NONE_H

#include <iterator>
#include <complex>

namespace pythonic {

    struct none_type { none_type(){} };

    static const none_type None;

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
        };

    /* speciaization of none for integrat types we cannot derive from
     */
#define SPECIALIZE_NONE(T)\
    template<>\
    struct none<T> {\
        T data;\
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
    };\
    T operator+(none<T> const& t0, T const &t1)         { return t0.data + t1     ; }\
    T operator+(T const &t0, none<T> const& t1)         { return t0      + t1.data; }\
    T operator+(none<T> const &t0, none<T> const& t1)   { return t0.data + t1.data; }\
    T operator>(none<T> const& t0, T const &t1)         { return t0.data > t1     ; }\
    T operator>(T const &t0, none<T> const& t1)         { return t0      > t1.data; }\
    T operator>(none<T> const &t0, none<T> const& t1)   { return t0.data > t1.data; }\
    T operator>=(none<T> const& t0, T const &t1)        { return t0.data >= t1     ; }\
    T operator>=(T const &t0, none<T> const& t1)        { return t0      >= t1.data; }\
    T operator>=(none<T> const &t0, none<T> const& t1)  { return t0.data >= t1.data; }\
    T operator<(none<T> const& t0, T const &t1)         { return t0.data < t1     ; }\
    T operator<(T const &t0, none<T> const& t1)         { return t0      < t1.data; }\
    T operator<(none<T> const &t0, none<T> const& t1)   { return t0.data < t1.data; }\
    T operator<=(none<T> const& t0, T const &t1)        { return t0.data <= t1     ; }\
    T operator<=(T const &t0, none<T> const& t1)        { return t0      <= t1.data; }\
    T operator<=(none<T> const &t0, none<T> const& t1)  { return t0.data <= t1.data; }\
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

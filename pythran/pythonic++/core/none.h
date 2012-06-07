#ifndef PYTHONIC_NONE_H
#define PYTHONIC_NONE_H

namespace pythonic {

struct none_type { none_type(){} };

static const none_type None;

template<class T>
struct none {
    T data;
    bool is_none;
    none() : data(), is_none(false) {}
    none(none_type const&) : data(), is_none(true) {}
    none(T const& data) : data(data), is_none(false) {}
    bool operator==(none_type const &) const { return is_none; }
    template <class O>
        bool operator==(O const & t) const { return not is_none and data == t; }
    operator bool() const { return not is_none and data; }
};

template <class T0, class T1>
T0 operator+(T0 const& self, none<T1> const& other) { return self + other.data; }

template <class T0, class T1>
T0 operator+(none<T0> const& self, T1 const& other) { return self.data + other; }

/* for type inference only */
template <class T>
none<T> operator+(T ,none_type ); 
template <class T>
none<T> operator+(none_type , T ); 
}

#endif

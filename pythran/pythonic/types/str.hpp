#ifndef PYTHONIC_TYPES_STR_HPP
#define PYTHONIC_TYPES_STR_HPP

#include "pythonic/include/types/str.hpp"

#include "pythonic/types/slice.hpp"
#include "pythonic/types/long.hpp"
#include "pythonic/types/tuple.hpp"

#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/int_.hpp"

#include <boost/format.hpp>
#include <cassert>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>

namespace pythonic
{

  namespace types
  {

    /// const_sliced_str_iterator implementation
    const_sliced_str_iterator::const_sliced_str_iterator(char const *data,
                                                         long step)
        : data(data), step(step)
    {
    }

    const_sliced_str_iterator const_sliced_str_iterator::operator++()
    {
      data += step;
      return *this;
    }

    bool const_sliced_str_iterator::
    operator<(const_sliced_str_iterator const &other) const
    {
      return (step > 0) ? (data < other.data) : (data > other.data);
    }

    bool const_sliced_str_iterator::
    operator==(const_sliced_str_iterator const &other) const
    {
      return data == other.data;
    }

    bool const_sliced_str_iterator::
    operator!=(const_sliced_str_iterator const &other) const
    {
      return data != other.data;
    }

    char const_sliced_str_iterator::operator*() const
    {
      return *data;
    }

    const_sliced_str_iterator const_sliced_str_iterator::operator-(long n) const
    {
      const_sliced_str_iterator other(*this);
      other.data -= step * n;
      return other;
    }

    long const_sliced_str_iterator::
    operator-(const_sliced_str_iterator const &other) const
    {
      return (data - other.data) / step;
    }

    /// sliced_str implementation
    // constructor
    template <class S>
    sliced_str<S>::sliced_str()
        : data(utils::no_memory())
    {
    }

    template <class S>
    sliced_str<S>::sliced_str(sliced_str const &s)
        : data(s.data), slicing(s.slicing)
    {
    }

    template <class S>
    sliced_str<S>::sliced_str(sliced_str const &s,
                              typename S::normalized_type const &sl)
        : data(s.data), slicing(s.slicing * sl)
    {
    }

    template <class S>
    sliced_str<S>::sliced_str(str const &other,
                              typename S::normalized_type const &s)
        : data(other.data), slicing(s)
    {
    }

    // const getter
    template <class S>
    typename sliced_str<S>::container_type const &
    sliced_str<S>::get_data() const
    {
      return *data;
    }

    template <class S>
    typename S::normalized_type const &sliced_str<S>::get_slice() const
    {
      return slicing;
    }

    // iterators
    template <class S>
    typename sliced_str<S>::const_iterator sliced_str<S>::begin() const
    {
      return typename sliced_str<S>::const_iterator(
          data->c_str() + slicing.lower, slicing.step);
    }

    template <class S>
    typename sliced_str<S>::const_iterator sliced_str<S>::end() const
    {
      return typename sliced_str<S>::const_iterator(
          data->c_str() + slicing.upper, slicing.step);
    }

    // size
    template <class S>
    long sliced_str<S>::size() const
    {
      return slicing.size();
    }

    // accessor
    template <class S>
    char const &sliced_str<S>::operator[](long i) const
    {
      return (*data)[slicing.get(i)];
    }

    template <class S>
    char &sliced_str<S>::operator[](long i)
    {
      return (*data)[slicing.get(i)];
    }

    template <class S>
    sliced_str<slice> sliced_str<S>::operator[](slice const &s) const
    {
      return sliced_str<slice>(*this, s.normalize(size()));
    }

    template <class S>
    sliced_str<contiguous_slice> sliced_str<S>::
    operator[](contiguous_slice const &s) const
    {
      return sliced_str<contiguous_slice>(*this, s.normalize(size()));
    }

    // conversion
    template <class S>
    sliced_str<S>::operator bool() const
    {
      return size() > 0;
    }

    template <class S>
    sliced_str<S>::operator long() const
    {
      long out;
      std::istringstream iss(str(*this).get_data());
      iss >> out;
      return out;
    }

    template <class S>
    bool sliced_str<S>::operator!() const
    {
      return not bool();
    }

    template <class S>
    bool sliced_str<S>::contains(str const &v) const
    {
      return find(v) != std::string::npos;
    }

    // io
    template <class S>
    std::ostream &operator<<(std::ostream &os, types::sliced_str<S> const &v)
    {
      for (auto b = v.begin(); b != v.end(); ++b)
        os << *b;
      return os;
    }

    template <class S>
    str sliced_str<S>::operator+(sliced_str<S> const &s)
    {
      str out(*data);
      std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
      return out;
    }

    template <class S>
    size_t sliced_str<S>::find(str const &s, size_t pos) const
    {
      return str(*this).find(s); // quite inefficient
    }

    template <class S>
    sliced_str<S> &sliced_str<S>::operator=(sliced_str<S> const &s)
    {
      slicing = s.slicing;
      data = s.data;
      return *this;
    }

    template <class S>
    sliced_str<S> &sliced_str<S>::operator=(str const &s)
    {
      if (slicing.step == 1) {
        data->erase(slicing.lower, slicing.upper);
        data->insert(slicing.lower, s.get_data());
      } else
        assert("not implemented yet");
      return *this;
    }

    /// str implementation
    str::str() : data()
    {
    }

    str::str(std::string const &s) : data(s)
    {
    }

    str::str(std::string &&s) : data(std::move(s))
    {
    }

    str::str(const char *s) : data(s)
    {
    }

    str::str(const char *s, size_t n) : data(s, n)
    {
    }

    str::str(char c) : data(1, c)
    {
    }

    template <class S>
    str::str(sliced_str<S> const &other)
        : data(other.begin(), other.end())
    {
    }

    template <class T>
    str::str(T const &begin, T const &end)
        : data(begin, end)
    {
    }

    str::operator char() const
    {
      assert(size() == 1);
      return (*data)[0];
    }

    str::operator long int() const
    { // Allows implicit conversion without loosing bool conversion
      char *endptr;
      auto dat = data->data();
      long res = strtol(dat, &endptr, 10);
      if (endptr == dat) {
        std::ostringstream err;
        err << "invalid literal for long() with base 10:'" << c_str() << '\'';
        throw std::runtime_error(err.str());
      }
      return res;
    }

    str::operator pythran_long_t() const
    {
#ifdef USE_GMP
      return pythran_long_t(*data);
#else
      char *endptr;
      auto dat = data->data();
      pythran_long_t res = strtoll(dat, &endptr, 10);
      if (endptr == dat) {
        std::ostringstream err;
        err << "invalid literal for long() with base 10:'" << c_str() << '\'';
        throw std::runtime_error(err.str());
      }
      return res;
#endif
    }

    str::operator double() const
    {
      char *endptr;
      auto dat = data->data();
      double res = strtod(dat, &endptr);
      if (endptr == dat) {
        std::ostringstream err;
        err << "invalid literal for double():'" << c_str() << "'";
        throw std::runtime_error(err.str());
      }
      return res;
    }

    template <class S>
    str &str::operator=(sliced_str<S> const &other)
    {
      if (other.get_data() == *data) {
        auto it = std::copy(other.begin(), other.end(), begin());
        resize(it - this->begin());
      } else
        *this = other.get_data();
      return *this;
    }

    str &str::operator+=(str const &s)
    {
      *data += *s.data;
      return *this;
    }

    str::container_type const &str::get_data() const
    {
      return *data;
    }

    long str::size() const
    {
      return data->size();
    }

    auto str::begin() const -> decltype(data->begin())
    {
      return data->begin();
    }

    auto str::begin() -> decltype(data->begin())
    {
      return data->begin();
    }

    auto str::rbegin() const -> decltype(data->rbegin())
    {
      return data->rbegin();
    }

    auto str::rbegin() -> decltype(data->rbegin())
    {
      return data->rbegin();
    }

    auto str::end() const -> decltype(data->end())
    {
      return data->end();
    }

    auto str::end() -> decltype(data->end())
    {
      return data->end();
    }

    auto str::rend() const -> decltype(data->rend())
    {
      return data->rend();
    }

    auto str::rend() -> decltype(data->rend())
    {
      return data->rend();
    }

    auto str::c_str() const -> decltype(data->c_str())
    {
      return data->c_str();
    }

    auto str::resize(long n) -> decltype(data->resize(n))
    {
      return data->resize(n);
    }

    long str::find(str const &s, size_t pos) const
    {
      const char *res = strstr(c_str() + pos, s.c_str());
      return res ? res - c_str() : -1;
    }

    bool str::contains(str const &v) const
    {
      return find(v) != -1;
    }

    long str::find_first_of(str const &s, size_t pos) const
    {
      return data->find_first_of(*s.data, pos);
    }

    long str::find_first_of(const char *s, size_t pos) const
    {
      return data->find_first_of(s, pos);
    }

    long str::find_first_not_of(str const &s, size_t pos) const
    {
      return data->find_first_not_of(*s.data, pos);
    }

    long str::find_last_not_of(str const &s, size_t pos) const
    {
      return data->find_last_not_of(*s.data, pos);
    }

    str str::substr(size_t pos, size_t len) const
    {
      return data->substr(pos, len);
    }

    bool str::empty() const
    {
      return data->empty();
    }

    int str::compare(size_t pos, size_t len, str const &str) const
    {
      return data->compare(pos, len, *str.data);
    }

    void str::reserve(size_t n)
    {
      data->reserve(n);
    }

    str &str::replace(size_t pos, size_t len, str const &str)
    {
      data->replace(pos, len, *str.data);
      return *this;
    }

    template <class S>
    str &str::operator+=(sliced_str<S> const &other)
    {
      resize(size() + other.get_data().size());
      std::copy(other.begin(), other.end(), begin());
      return *this;
    }

    bool str::operator==(str const &other) const
    {
      return *data == *other.data;
    }

    bool str::operator!=(str const &other) const
    {
      return *data != *other.data;
    }

    bool str::operator<=(str const &other) const
    {
      return *data <= *other.data;
    }

    bool str::operator<(str const &other) const
    {
      return *data < *other.data;
    }

    bool str::operator>=(str const &other) const
    {
      return *data >= *other.data;
    }

    bool str::operator>(str const &other) const
    {
      return *data > *other.data;
    }

    template <class S>
    bool str::operator==(sliced_str<S> const &other) const
    {
      if (size() != other.size())
        return false;
      for (long i = other.get_slice().lower, j = 0L; j < size();
           i = i + other.get_slice().step, j++)
        if (other.get_data()[i] != (*this)[j])
          return false;
      return true;
    }

    sliced_str<slice> str::operator()(slice const &s) const
    {
      return operator[](s);
    }

    sliced_str<contiguous_slice> str::
    operator()(contiguous_slice const &s) const
    {
      return operator[](s);
    }

    char str::operator[](long i) const
    {
      if (i < 0)
        i += size();
      return (*data)[i];
    }

    char &str::operator[](long i)
    {
      if (i < 0)
        i += size();
      return (*data)[i];
    }

    sliced_str<slice> str::operator[](slice const &s) const
    {
      return sliced_str<slice>(*this, s.normalize(size()));
    }

    sliced_str<contiguous_slice> str::
    operator[](contiguous_slice const &s) const
    {
      return sliced_str<contiguous_slice>(*this, s.normalize(size()));
    }

#ifdef USE_GMP
    char str::operator[](pythran_long_t const &m) const
    {
      return (*this)[m.get_si()];
    }

    char &str::operator[](pythran_long_t const &m)
    {
      return (*this)[m.get_si()];
    }
#endif

    str::operator bool() const
    {
      return not data->empty();
    }

    template <class A>
    str str::operator%(A const &a) const
    {
      const boost::format fmter(*data);
      return (boost::format(fmter) % a).str();
    }

    template <class... A>
    types::str str::operator%(std::tuple<A...> const &a) const
    {
      boost::format fmter(*data);
      fmt(fmter, a, utils::int_<sizeof...(A)>());
      return fmter.str();
    }

    template <size_t N, class T>
    str str::operator%(types::array<T, N> const &a) const
    {
      boost::format fmter(*data);
      fmt(fmter, a, utils::int_<N>());
      return fmter.str();
    }

    long str::count(types::str const &sub) const
    {
      long counter = 0;
      for (long z = find(sub);            // begin by looking for sub
           z != -1;                       // as long as we don't reach the end
           z = find(sub, z + sub.size())) // look for another one
      {
        ++counter;
      }
      return counter;
    }

    template <class Tuple, size_t I>
    void str::fmt(boost::format &f, Tuple const &a, utils::int_<I>) const
    {
      fmt(f % std::get<std::tuple_size<Tuple>::value - I>(a), a,
          utils::int_<I - 1>());
    }

    template <class Tuple>
    void str::fmt(boost::format &f, Tuple const &a, utils::int_<1>) const
    {
      f % std::get<std::tuple_size<Tuple>::value - 1>(a);
    }

    str operator+(str const &self, str const &other)
    {
      return str(self.get_data() + other.get_data());
    }

    template <size_t N>
    str operator+(str const &self, char const(&other)[N])
    {
      std::string s;
      s.reserve(self.size() + N);
      s += self.get_data();
      s += other;
      return {std::move(s)};
    }

    template <size_t N>
    str operator+(char const(&self)[N], str const &other)
    {
      std::string s;
      s.reserve(other.size() + N);
      s += self;
      s += other.get_data();
      return {std::move(s)};
    }

    bool operator==(char c, str const &s)
    {
      return s.size() == 1 and s[0] == c;
    }

    bool operator==(str const &s, char c)
    {
      return s.size() == 1 and s[0] == c;
    }

    bool operator!=(char c, str const &s)
    {
      return s.size() != 1 or s[0] != c;
    }

    bool operator!=(str const &s, char c)
    {
      return s.size() != 1 or s[0] != c;
    }

    std::ostream &operator<<(std::ostream &os, str const &s)
    {
      return os << s.c_str();
    }

    size_t hash_value(str const &x)
    {
      return std::hash<str>()(x);
    }
  }

  namespace operator_
  {

    template <size_t N, class Arg>
    auto mod(const char(&fmt)[N], Arg &&arg)
        -> decltype(types::str(fmt) % std::forward<Arg>(arg))
    {
      return types::str(fmt) % std::forward<Arg>(arg);
    }
  }
}

pythonic::types::str operator*(pythonic::types::str const &s, long n)
{
  if (n <= 0)
    return pythonic::types::str();
  pythonic::types::str other;
  other.resize(s.size() * n);
  auto where = other.begin();
  for (long i = 0; i < n; i++, where += s.size())
    std::copy(s.begin(), s.end(), where);
  return other;
}

pythonic::types::str operator*(long t, pythonic::types::str const &s)
{
  return s * t;
}

namespace std
{

  size_t hash<pythonic::types::str>::
  operator()(const pythonic::types::str &x) const
  {
    return hash<std::string>()(x.get_data());
  }

  template <size_t I>
  pythonic::types::str get(pythonic::types::str const &t)
  {
    return pythonic::types::str(t[I]);
  }
}
#ifdef ENABLE_PYTHON_MODULE

#if PY_MAJOR_VERSION >= 3
#define PyString_FromStringAndSize PyBytes_FromStringAndSize
#define PyString_Check PyBytes_Check
#define PyString_AS_STRING PyBytes_AS_STRING
#define PyString_GET_SIZE PyBytes_GET_SIZE
#endif

namespace pythonic
{

  PyObject *to_python<types::str>::convert(types::str const &v)
  {
    return PyString_FromStringAndSize(v.c_str(), v.size());
  }

  template <class S>
  PyObject *
  to_python<types::sliced_str<S>>::convert(types::sliced_str<S> const &v)
  {
    return ::to_python(types::str(v));
  }
  PyObject *to_python<char>::convert(char l)
  {
    return PyString_FromStringAndSize(&l, 1);
  }

  bool from_python<types::str>::is_convertible(PyObject *obj)
  {
    return PyString_Check(obj);
  }
  types::str from_python<types::str>::convert(PyObject *obj)
  {
    return {PyString_AS_STRING(obj), (size_t)PyString_GET_SIZE(obj)};
  }
}

#endif

#endif

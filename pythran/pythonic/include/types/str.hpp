#ifndef PYTHONIC_INCLUDE_TYPES_STR_HPP
#define PYTHONIC_INCLUDE_TYPES_STR_HPP

#include "pythonic/include/types/slice.hpp"
#include "pythonic/include/types/long.hpp"
#include "pythonic/include/types/tuple.hpp"

#include "pythonic/include/types/assignable.hpp"
#include "pythonic/include/utils/shared_ref.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/int_.hpp"

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

    class str;

    struct const_sliced_str_iterator
        : std::iterator<std::random_access_iterator_tag, char, ptrdiff_t,
                        char *, char> {
      const char *data;
      long step;
      const_sliced_str_iterator(char const *data, long step);
      const_sliced_str_iterator operator++();
      bool operator<(const_sliced_str_iterator const &other) const;
      bool operator==(const_sliced_str_iterator const &other) const;
      bool operator!=(const_sliced_str_iterator const &other) const;
      char operator*() const;
      const_sliced_str_iterator operator-(long n) const;
      long operator-(const_sliced_str_iterator const &other) const;
    };

    template <class S = slice>
    class sliced_str
    {

      using container_type = std::string;
      utils::shared_ref<container_type> data;

      typename S::normalized_type slicing;

    public:
      //  types
      using reference = container_type::reference;
      using const_reference = container_type::const_reference;
      using iterator = const_sliced_str_iterator;
      using const_iterator = const_sliced_str_iterator;
      using size_type = container_type::size_type;
      using difference_type = container_type::difference_type;
      using value_type = container_type::value_type;
      using allocator_type = container_type::allocator_type;
      using pointer = container_type::pointer;
      using const_pointer = container_type::const_pointer;

      // constructor
      sliced_str();
      sliced_str(sliced_str const &s);

      sliced_str(sliced_str const &s, typename S::normalized_type const &sl);
      sliced_str(types::str const &other, typename S::normalized_type const &s);

      // const getter
      container_type const &get_data() const;
      typename S::normalized_type const &get_slice() const;

      // assignment
      sliced_str &operator=(str const &);
      sliced_str &operator=(sliced_str const &);
      str operator+(sliced_str const &);

      // iterators
      const_iterator begin() const;
      const_iterator end() const;

      // size
      long size() const;

      // accessor
      char const &operator[](long i) const;
      char &operator[](long i);
      sliced_str<slice> operator[](slice const &s) const;
      sliced_str<contiguous_slice> operator[](contiguous_slice const &s) const;

      // conversion
      operator long() const;
      explicit operator bool() const;
      bool operator!() const;

      size_t find(str const &s, size_t pos = 0) const;
      bool contains(str const &v) const;

      // io
      template <class SS>
      friend std::ostream &operator<<(std::ostream &os,
                                      types::sliced_str<SS> const &v);
    };

    class str
    {

      template <class S>
      friend class sliced_str;

      using container_type = std::string;
      utils::shared_ref<container_type> data;

    public:
      static const size_t npos = std::string::npos;

      using value_type = str; // in Python, a string contains... strings
      using iterator = container_type::iterator;
      using reverse_iterator = container_type::reverse_iterator;
      using const_reverse_iterator = container_type::const_reverse_iterator;

      str();
      str(std::string const &s);
      str(std::string &&s);
      str(const char *s);
      str(const char *s, size_t n);
      str(char c);
      template <class S>
      str(sliced_str<S> const &other);
      template <class T>
      str(T const &begin, T const &end);

      explicit operator char() const;
      operator long int() const;
      operator pythran_long_t() const;
      explicit operator double() const;

      template <class S>
      str &operator=(sliced_str<S> const &other);

      types::str &operator+=(types::str const &s);

      container_type const &get_data() const;

      long size() const;
      auto begin() const -> decltype(data->begin());
      auto begin() -> decltype(data->begin());
      auto rbegin() const -> decltype(data->rbegin());
      auto rbegin() -> decltype(data->rbegin());
      auto end() const -> decltype(data->end());
      auto end() -> decltype(data->end());
      auto rend() const -> decltype(data->rend());
      auto rend() -> decltype(data->rend());
      auto c_str() const -> decltype(data->c_str());
      auto resize(long n) -> decltype(data->resize(n));
      long find(str const &s, size_t pos = 0) const;
      bool contains(str const &v) const;
      long find_first_of(str const &s, size_t pos = 0) const;
      long find_first_of(const char *s, size_t pos = 0) const;
      long find_first_not_of(str const &s, size_t pos = 0) const;
      long find_last_not_of(str const &s, size_t pos = npos) const;
      str substr(size_t pos = 0, size_t len = npos) const;
      bool empty() const;
      int compare(size_t pos, size_t len, str const &str) const;
      void reserve(size_t n);
      str &replace(size_t pos, size_t len, str const &str);

      template <class S>
      str &operator+=(sliced_str<S> const &other);
      bool operator==(str const &other) const;
      bool operator!=(str const &other) const;
      bool operator<=(str const &other) const;
      bool operator<(str const &other) const;
      bool operator>=(str const &other) const;
      bool operator>(str const &other) const;
      template <class S>
      bool operator==(sliced_str<S> const &other) const;
      sliced_str<slice> operator()(slice const &s) const;
      sliced_str<contiguous_slice> operator()(contiguous_slice const &s) const;

      char operator[](long i) const;
      char &operator[](long i);

      sliced_str<slice> operator[](slice const &s) const;
      sliced_str<contiguous_slice> operator[](contiguous_slice const &s) const;
#ifdef USE_GMP
      char operator[](pythran_long_t const &m) const;
      char &operator[](pythran_long_t const &m);
#endif

      explicit operator bool() const;
      template <class A>
      types::str operator%(A const &a) const;
      template <class... A>
      types::str operator%(std::tuple<A...> const &a) const;
      template <size_t N, class T>
      types::str operator%(types::array<T, N> const &a) const;

      long count(types::str const &sub) const;

    private:
      template <class Tuple, size_t I>
      void fmt(boost::format &f, Tuple const &a, utils::int_<I>) const;
      template <class Tuple>
      void fmt(boost::format &f, Tuple const &a, utils::int_<1>) const;
    };

    size_t hash_value(str const &x);

    str operator+(str const &self, str const &other);

    template <size_t N>
    str operator+(str const &self, char const(&other)[N]);

    template <size_t N>
    str operator+(char const(&self)[N], str const &other);

    bool operator==(char c, str const &s);
    bool operator==(str const &s, char c);
    bool operator!=(char c, str const &s);
    bool operator!=(str const &s, char c);
    std::ostream &operator<<(std::ostream &os, str const &s);
  }

  namespace operator_
  {

    template <size_t N, class Arg>
    auto mod(const char(&fmt)[N], Arg &&arg)
        -> decltype(pythonic::types::str(fmt) % std::forward<Arg>(arg));
  }

  template <>
  struct assignable<char *> {
    using type = types::str;
  };
  template <>
  struct assignable<char const *> {
    using type = types::str;
  };
  template <size_t N>
  struct assignable<char[N]> {
    using type = types::str;
  };
  template <size_t N>
  struct assignable<char const[N]> {
    using type = types::str;
  };
}

pythonic::types::str operator*(pythonic::types::str const &s, long n);
pythonic::types::str operator*(long t, pythonic::types::str const &s);

namespace std
{
  template <>
  struct hash<pythonic::types::str> {
    size_t operator()(const pythonic::types::str &x) const;
  };

  /* std::get overload */
  template <size_t I>
  pythonic::types::str get(pythonic::types::str const &t);

  template <size_t I>
  struct tuple_element<I, pythonic::types::str> {
    using type = pythonic::types::str;
  };

  template <size_t I, class S>
  struct tuple_element<I, pythonic::types::sliced_str<S>> {
    using type = pythonic::types::str;
  };
}

/* type inference stuff  {*/
#include "pythonic/include/types/combined.hpp"

template <>
struct __combined<char const *, pythonic::types::str> {
  using type = pythonic::types::str;
};

template <>
struct __combined<pythonic::types::str, char const *> {
  using type = pythonic::types::str;
};

template <size_t N, size_t M>
struct __combined<char[N], char[M]> {
  using type = pythonic::types::str;
};

/* } */
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{

  template <>
  struct to_python<types::str> {
    static PyObject *convert(types::str const &v);
  };

  template <class S>
  struct to_python<types::sliced_str<S>> {
    static PyObject *convert(types::sliced_str<S> const &v);
  };
  template <>
  struct to_python<char> {
    static PyObject *convert(char l);
  };

  template <>
  struct from_python<types::str> {
    static bool is_convertible(PyObject *obj);
    static types::str convert(PyObject *obj);
  };
}

#endif

#endif

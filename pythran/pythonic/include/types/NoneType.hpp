#ifndef PYTHONIC_INCLUDE_TYPES_NONE_HPP
#define PYTHONIC_INCLUDE_TYPES_NONE_HPP

#include "pythonic/include/types/assignable.hpp"

namespace pythonic
{

  namespace types
  {

    static const intptr_t NONE_ID = 0x1331;

    template <class T>
    struct is_none;

    struct weak_none_type {
      template <class T>
      operator T() const
      {
        return {};
      }
    };

    struct none_type {
      none_type();
      intptr_t id() const;
    };

    template <class T>
    typename std::enable_if<!is_none<T>::value, bool>::type
    operator==(none_type const &, T const &)
    {
      return false;
    }
    template <class T>
    typename std::enable_if<!is_none<T>::value, bool>::type
    operator==(T const &, none_type const &)
    {
      return false;
    }
    template <class T>
    bool operator==(none_type const &, none_type const &)
    {
      return true;
    }

    /* Type adapator to simulate an option type
     *
     * see http://en.wikipedia.org/wiki/Option_type
     */
    template <class T>
    struct none {
      T data;
      template <class T1>
      friend std::ostream &operator<<(std::ostream &, none<T1> const &);
      template <class T1>
      friend bool operator==(T1 const &, none<T1> const &);
      template <class T1>
      friend bool operator==(none<T1> const &, T1 const &);

    public:
      bool is_none;
      none();
      none(none_type const &);
      none(T const &data);
      operator T() const;
      T &operator=(T const &t);
      bool operator==(none_type const &) const;
      intptr_t id() const;
    };

    template <class T>
    struct is_none {
      static const bool value = false;
    };

    template <class T>
    struct is_none<none<T>> {
      static const bool value = true;
    };
  }

  template <class T>
  struct assignable<types::none<T>> {
    using type = types::none<typename assignable<T>::type>;
  };
}

/* type inference stuff { */
#include "pythonic/include/types/combined.hpp"

template <class T>
struct __combined<pythonic::types::weak_none_type, T> {
  using type = T;
};
template <class T>
struct __combined<T, pythonic::types::weak_none_type> {
  using type = T;
};
template <>
struct __combined<pythonic::types::weak_none_type,
                  pythonic::types::weak_none_type> {
  using type = pythonic::types::weak_none_type;
};

template <class T0, class T1>
struct __combined<pythonic::types::none<T0>, T1>
    : std::enable_if<!pythonic::types::is_none<T1>::value,
                     pythonic::dummy>::type {
  using type = pythonic::types::none<typename __combined<T0, T1>::type>;
};

template <class T0, class T1>
struct __combined<T1, pythonic::types::none<T0>>
    : std::enable_if<!pythonic::types::is_none<T0>::value,
                     pythonic::dummy>::type {
  using type = pythonic::types::none<typename __combined<T0, T1>::type>;
};

template <class T0, class T1>
struct __combined<pythonic::types::none<T1>, pythonic::types::none<T0>> {
  using type = pythonic::types::none<typename __combined<T0, T1>::type>;
};

template <class T>
struct __combined<typename std::enable_if<!pythonic::types::is_none<T>::value,
                                          pythonic::types::none_type>::type,
                  T> {
  using type = pythonic::types::none<T>;
};

template <class T>
struct __combined<T,
                  typename std::enable_if<!pythonic::types::is_none<T>::value,
                                          pythonic::types::none_type>::type> {
  using type = pythonic::types::none<T>;
};

template <>
struct __combined<pythonic::types::none_type, pythonic::types::none_type> {
  using type = pythonic::types::none_type;
};

/* } */

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/core.hpp"

namespace pythonic
{
  template <>
  struct to_python<types::none_type> {
    static PyObject *convert(types::none_type);
  };

  template <class T>
  struct to_python<types::none<T>> {
    static PyObject *convert(types::none<T> const &n);
  };

  template <>
  struct from_python<types::none_type> {

    static bool is_convertible(PyObject *obj);

    static types::none_type convert(PyObject *obj);
  };
}

#endif
#endif

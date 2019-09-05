#ifndef PYTHONIC_BUILTIN_TYPE_HPP
#define PYTHONIC_BUILTIN_TYPE_HPP

#include "pythonic/include/__builtin__/type.hpp"

#include "pythonic/utils/functor.hpp"

#include "pythonic/__builtin__/bool_.hpp"
#include "pythonic/__builtin__/int_.hpp"
#include "pythonic/__builtin__/float_.hpp"
#include "pythonic/__builtin__/complex.hpp"
#include "pythonic/__builtin__/set.hpp"
#include "pythonic/__builtin__/str.hpp"
#include "pythonic/__builtin__/list.hpp"
#include "pythonic/__builtin__/dict.hpp"
#include "pythonic/__builtin__/tuple.hpp"
#include "pythonic/numpy/array.hpp"
#include "pythonic/numpy/int8.hpp"
#include "pythonic/numpy/uint8.hpp"
#include "pythonic/numpy/int16.hpp"
#include "pythonic/numpy/uint16.hpp"
#include "pythonic/numpy/int32.hpp"
#include "pythonic/numpy/uint32.hpp"
#include "pythonic/numpy/int64.hpp"
#include "pythonic/numpy/uint64.hpp"
#include "pythonic/numpy/float32.hpp"
#include "pythonic/numpy/float128.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{
  template <>
  struct type_functor<bool> {
    using type = functor::bool_;
  };
  template <>
  struct type_functor<double> {
    using type = functor::float_;
  };
  template <>
  struct type_functor<types::str> {
    using type = functor::str;
  };
  template <class T>
  struct type_functor<std::complex<T>> {
    using type = functor::complex;
  };
  template <>
  struct type_functor<types::empty_set> {
    using type = functor::set;
  };
  template <class T>
  struct type_functor<types::set<T>> {
    using type = functor::set;
  };
  template <>
  struct type_functor<types::empty_list> {
    using type = functor::list;
  };
  template <class T>
  struct type_functor<types::list<T>> {
    using type = functor::list;
  };
  template <class T, size_t N>
  struct type_functor<types::static_list<T, N>> {
    using type = functor::list;
  };
  template <>
  struct type_functor<types::empty_dict> {
    using type = functor::dict;
  };
  template <class K, class V>
  struct type_functor<types::dict<K, V>> {
    using type = functor::dict;
  };
  template <class... Tys>
  struct type_functor<std::tuple<Tys...>> {
    using type = functor::tuple;
  };
  template <class T, size_t N>
  struct type_functor<types::array<T, N>> {
    using type = functor::tuple;
  };
  template <class T, class pS>
  struct type_functor<types::ndarray<T, pS>> {
    using type = numpy::functor::array;
  };
  template <>
  struct type_functor<int8_t> {
    using type = numpy::functor::int8;
  };
  template <>
  struct type_functor<uint8_t> {
    using type = numpy::functor::uint8;
  };
  template <>
  struct type_functor<int16_t> {
    using type = numpy::functor::int16;
  };
  template <>
  struct type_functor<uint16_t> {
    using type = numpy::functor::uint16;
  };
  template <>
  struct type_functor<int32_t> {
    using type = numpy::functor::int32;
  };
  template <>
  struct type_functor<uint32_t> {
    using type = numpy::functor::uint32;
  };
  template <>
  struct type_functor<int64_t> {
    using type = numpy::functor::int64;
  };
  template <>
  struct type_functor<uint64_t> {
    using type = numpy::functor::uint64;
  };
  template <>
  struct type_functor<float> {
    using type = numpy::functor::float32;
  };
  template <>
  struct type_functor<long double> {
    using type = numpy::functor::float128;
  };

  template <class T>
  typename type_functor<T>::type type(T const &)
  {
    return {};
  }
}
PYTHONIC_NS_END

#endif

#ifndef PYTHONIC_TYPES_LIST_HPP
#define PYTHONIC_TYPES_LIST_HPP

#include "pythonic/include/types/list.hpp"
#include "pythonic/types/nditerator.hpp"

#include "pythonic/__builtin__/len.hpp"
#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"

#include <cassert>
#include <algorithm>

namespace pythonic
{

  namespace types
  {

    /// Sliced list

    // Constructors
    template <class T, class S>
    sliced_list<T, S>::sliced_list()
        : data(utils::no_memory())
    {
    }
    template <class T, class S>
    sliced_list<T, S>::sliced_list(sliced_list<T, S> const &s)
        : data(s.data), slicing(s.slicing)
    {
    }
    template <class T, class S>
    sliced_list<T, S>::sliced_list(list<T> &other, S const &s)
        : data(other.data), slicing(s.normalize(other.size()))
    {
    }

    // iterators
    template <class T, class S>
    typename sliced_list<T, S>::iterator sliced_list<T, S>::begin()
    {
      assert(slicing.step == 1);
      return data->begin() + slicing.lower;
    }
    template <class T, class S>
    typename sliced_list<T, S>::const_iterator sliced_list<T, S>::begin() const
    {
      assert(slicing.step == 1);
      return data->begin() + slicing.lower;
    }
    template <class T, class S>
    typename sliced_list<T, S>::iterator sliced_list<T, S>::end()
    {
      assert(slicing.step == 1);
      return data->begin() + slicing.upper;
    }
    template <class T, class S>
    typename sliced_list<T, S>::const_iterator sliced_list<T, S>::end() const
    {
      assert(slicing.step == 1);
      return data->begin() + slicing.upper;
    }

    // size
    template <class T, class S>
    long sliced_list<T, S>::size() const
    {
      return slicing.size();
    }

    // accessor
    template <class T, class S>
    T const &sliced_list<T, S>::operator[](long i) const
    {
      return (*data)[slicing.get(i)];
    }
    template <class T, class S>
    T &sliced_list<T, S>::operator[](long i)
    {
      return (*data)[slicing.get(i)];
    }

    // comparison
    template <class T, class S>
    template <class K>
    bool sliced_list<T, S>::operator==(list<K> const &other) const
    {
      if (size() != other.size())
        return false;
      return std::equal(begin(), end(), other.begin());
    }
    template <class T, class S>
    bool sliced_list<T, S>::operator==(empty_list const &other) const
    {
      return size() == 0;
    }
    template <class T, class S>
    inline sliced_list<T, S> &sliced_list<T, S>::
    operator=(sliced_list<T, S> const &s)
    {
      slicing = s.slicing;
      if (data != s.data)
        data = s.data;
      return *this;
    }
    template <class T, class S>
    sliced_list<T, S> &sliced_list<T, S>::operator=(list<T> const &seq)
    {
      if (slicing.step == 1) {
        data->erase(begin(), end());
        data->insert(begin(), seq.begin(), seq.end());
      } else
        assert(!"not implemented yet");
      return *this;
    }
    template <class T, class S>
    list<T> sliced_list<T, S>::operator+(list<T> const &s)
    {
      list<T> out(size() + s.size());
      std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
      return out;
    }
    template <class T, class S>
    list<T> sliced_list<T, S>::operator+(sliced_list<T, S> const &s)
    {
      list<T> out(size() + s.size());
      std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
      return out;
    }
    template <class N, class T>
    list<T> operator*(N n, list<T> const &l)
    {
      return l * n;
    }

    /// List

    // constructors
    template <class T>
    list<T>::list()
        : data(utils::no_memory())
    {
    }
    template <class T>
    template <class InputIterator>
    list<T>::list(InputIterator start, InputIterator stop)
        : data()
    {
      if (std::is_same<
              typename std::iterator_traits<InputIterator>::iterator_category,
              std::random_access_iterator_tag>::value)
        data->reserve(std::distance(start, stop));
      else
        data->reserve(DEFAULT_LIST_CAPACITY);
      std::copy(start, stop, std::back_inserter(*data));
    }
    template <class T>
    list<T>::list(empty_list const &)
        : data(0)
    {
    }
    template <class T>
    list<T>::list(size_type sz)
        : data(sz)
    {
    }
    template <class T>
    list<T>::list(T const &value, single_value)
        : data(1)
    {
      (*data)[0] = value;
    }
    template <class T>
    list<T>::list(std::initializer_list<T> l)
        : data(std::move(l))
    {
    }
    template <class T>
    list<T>::list(list<T> &&other)
        : data(std::move(other.data))
    {
    }
    template <class T>
    list<T>::list(list<T> const &other)
        : data(other.data)
    {
    }
    template <class T>
    template <class F>
    list<T>::list(list<F> const &other)
        : data(other.size())
    {
      std::copy(other.begin(), other.end(), begin());
    }
    template <class T>
    template <class S>
    list<T>::list(sliced_list<T, S> const &other)
        : data(other.begin(), other.end())
    {
    }

    // operators
    template <class T>
    list<T> &list<T>::operator=(list<T> &&other)
    {
      data = std::move(other.data);
      return *this;
    }
    template <class T>
    template <class F>
    list<T> &list<T>::operator=(list<F> const &other)
    {
      data = utils::shared_ref<container_type>{other.size()};
      std::copy(other.begin(), other.end(), begin());
      return *this;
    }
    template <class T>
    list<T> &list<T>::operator=(list<T> const &other)
    {
      data = other.data;
      return *this;
    }
    template <class T>
    list<T> &list<T>::operator=(empty_list const &)
    {
      data = utils::shared_ref<container_type>();
      return *this;
    }
    template <class T>
    template <class S>
    list<T> &list<T>::operator=(sliced_list<T, S> const &other)
    {
      if (other.data == data) {
        auto it = std::copy(other.begin(), other.end(), data->begin());
        data->resize(it - data->begin());
      } else
        data = utils::shared_ref<T>(other.begin(), other.end());
      return *this;
    }

    template <class T>
    template <class S>
    list<T> &list<T>::operator+=(sliced_list<T, S> const &other)
    {
      data->resize(data->size() + other.size());
      std::copy(other.begin(), other.end(), data->begin());
      return *this;
    }
    template <class T>
    template <class S>
    list<T> list<T>::operator+(sliced_list<T, S> const &other) const
    {
      list<T> new_list(begin(), end());
      new_list.reserve(data->size() + other.size());
      std::copy(other.begin(), other.end(), std::back_inserter(new_list));
      return new_list;
    }

    // io
    template <class T>
    std::ostream &operator<<(std::ostream &os, list<T> const &v)
    {
      os << '[';
      auto iter = v.begin();
      if (iter != v.end()) {
        while (iter + 1 != v.end())
          os << *iter++ << ", ";
        os << *iter;
      }
      return os << ']';
    }

    // comparison
    template <class T>
    template <class K>
    bool list<T>::operator==(list<K> const &other) const
    {
      if (size() != other.size())
        return false;
      return std::equal(begin(), end(), other.begin());
    }
    template <class T>
    bool list<T>::operator==(empty_list const &) const
    {
      return size() == 0;
    }
    template <class T>
    template <class K>
    bool list<T>::operator!=(list<K> const &other) const
    {
      return !operator==(other);
    }
    template <class T>
    bool list<T>::operator!=(empty_list const &) const
    {
      return size() != 0;
    }

    // iterators
    template <class T>
    typename list<T>::iterator list<T>::begin()
    {
      return data->begin();
    }
    template <class T>
    typename list<T>::const_iterator list<T>::begin() const
    {
      return data->begin();
    }
    template <class T>
    typename list<T>::iterator list<T>::end()
    {
      return data->end();
    }
    template <class T>
    typename list<T>::const_iterator list<T>::end() const
    {
      return data->end();
    }
    template <class T>
    typename list<T>::reverse_iterator list<T>::rbegin()
    {
      return data->rbegin();
    }
    template <class T>
    typename list<T>::const_reverse_iterator list<T>::rbegin() const
    {
      return data->rbegin();
    }
    template <class T>
    typename list<T>::reverse_iterator list<T>::rend()
    {
      return data->rend();
    }
    template <class T>
    typename list<T>::const_reverse_iterator list<T>::rend() const
    {
      return data->rend();
    }

    // comparison
    template <class T>
    int list<T>::operator<(list<T> const &other) const
    {
      auto other_iter = other.begin();
      auto self_iter = begin();
      for (; other_iter != other.end() and self_iter != end();
           ++other_iter, ++self_iter) {
        if (*other_iter < *self_iter)
          return 1;
        if (*other_iter > *self_iter)
          return -1;
      }
      if (other_iter != other.end() and self_iter == end())
        return 1;
      if (other_iter == other.end() and self_iter != end())
        return -1;
      return 0;
    }

// element access
#ifdef USE_BOOST_SIMD
    template <class T>
    typename list<T>::simd_iterator list<T>::vbegin() const
    {
      return {*this, 0};
    }

    template <class T>
    typename list<T>::simd_iterator list<T>::vend() const
    {
      using vector_type =
          typename boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>;
      static const std::size_t vector_size =
          boost::simd::meta::cardinal_of<vector_type>::value;
      return {*this, long(size() / vector_size * vector_size)};
    }
    template <class T>
    auto list<T>::load(long i) const -> decltype(
        boost::simd::load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(
            (*this->data), i))
    {
      return boost::simd::load<
          boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(data->data(),
                                                                i);
    }
    template <class T>
    template <class V>
    void list<T>::store(V &&v, long i)
    {
      boost::simd::store(v, data->data(), i);
    }
#endif
    template <class T>
    typename list<T>::reference list<T>::fast(long n)
    {
      return (*data)[n];
    }
    template <class T>
    typename list<T>::reference list<T>::operator[](long n)
    {
      if (n < 0)
        n += data->size();
      return fast(n);
    }
    template <class T>
    typename list<T>::const_reference list<T>::fast(long n) const
    {
      return (*data)[n];
    }
    template <class T>
    typename list<T>::const_reference list<T>::operator[](long n) const
    {
      if (n < 0)
        n += data->size();
      return fast(n);
    }

    template <class T>
    list<T> list<T>::operator[](slice const &s) const
    {
      normalized_slice norm = s.normalize(size());
      list<T> out(norm.size());
      for (long i = 0; i < out.size(); i++)
        out[i] = (*data)[norm.get(i)];
      return out;
    }
    template <class T>
    list<T> list<T>::operator[](contiguous_slice const &s) const
    {
      contiguous_normalized_slice norm = s.normalize(size());
      list<T> out(norm.size());
      for (long i = 0; i < out.size(); i++)
        out[i] = (*data)[norm.get(i)];
      return out;
    }
    template <class T>
    sliced_list<T, slice> list<T>::operator()(slice const &s) const
    {
      return sliced_list<T, slice>(*const_cast<list<T> *>(this),
                                   s); // SG: ugly !
    }
    template <class T>
    sliced_list<T, contiguous_slice> list<T>::
    operator()(contiguous_slice const &s) const
    {
      return sliced_list<T, contiguous_slice>(*const_cast<list<T> *>(this),
                                              s); // SG: ugly !
    }

    // modifiers
    template <class T>
    void list<T>::push_back(T const &x)
    {
      data->push_back(x);
    }
    template <class T>
    void list<T>::insert(long i, T const &x)
    {
      if (i == size())
        data->push_back(x);
      else
        data->insert(data->begin() + i, x);
    }
    template <class T>
    void list<T>::reserve(size_t n)
    {
      data->reserve(n);
    }
    template <class T>
    void list<T>::resize(size_t n)
    {
      data->resize(n);
    }
    template <class T>
    typename list<T>::iterator list<T>::erase(size_t n)
    {
      return data->erase(data->begin() + n);
    }
    template <class T>
    T list<T>::pop(long x)
    {
      long sz = size();
      x = x % sz;
      if (x < 0)
        x += sz;
      T res = fast(x);
      erase(x);
      return res;
    }
    // TODO: have to raise a valueError
    template <class T>
    none_type list<T>::remove(T const &x)
    {
      erase(index(x));
      return {};
    }

    // Misc
    template <class T>
    long list<T>::index(T const &x) const
    {
      return std::find(begin(), end(), x) - begin();
    }

    // list interface
    template <class T>
    list<T>::operator bool() const
    {
      return not data->empty();
    }

    template <class T>
    template <class F>
    list<decltype(std::declval<T>() +
                  std::declval<typename list<F>::value_type>())> list<T>::
    operator+(list<F> const &s) const
    {
      list<decltype(std::declval<T>() +
                    std::declval<typename list<F>::value_type>())>
          clone(data->size() + s.data->size());
      std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
      return clone;
    }

    template <class T>
    template <class F, class S>
    list<decltype(std::declval<T>() +
                  std::declval<typename sliced_list<F, S>::value_type>())>
        list<T>::operator+(sliced_list<F, S> const &s) const
    {
      list<decltype(std::declval<T>() +
                    std::declval<typename sliced_list<F, S>::value_type>())>
          clone(data->size() + len(s));
      std::copy(s.begin(), s.end(), std::copy(begin(), end(), clone.begin()));
      return clone;
    }

    template <class T>
    list<T> list<T>::operator+(empty_list const &) const
    {
      return list<T>(begin(), end());
    }

    template <class T>
    list<T> list<T>::operator*(long n) const
    {
      list<T> r(data->size() * n);
      auto start = r.begin();
      for (long i = 0; i < n; i++, start += data->size())
        std::copy(this->begin(), this->end(), start);
      return r;
    }

    template <class T>
    template <class F>
    list<T> &list<T>::operator+=(list<F> const &s)
    {
      reserve(size() + s.size());
      std::copy(s.begin(), s.end(), std::back_inserter(*this));
      return *this;
    }

    template <class T>
    long list<T>::size() const
    {
      return data->size();
    }
    template <class T>
    template <class E>
    long list<T>::_flat_size(E const &e, utils::int_<1>) const
    {
      return std::distance(e.begin(), e.end());
    }
    template <class T>
    template <class E, size_t L>
    long list<T>::_flat_size(E const &e, utils::int_<L>) const
    {
      return std::distance(e.begin(), e.end()) *
             _flat_size(e[0], utils::int_<L - 1>{});
    }
    template <class T>
    long list<T>::flat_size() const
    {
      return _flat_size(*this, utils::int_<value>{});
    }

    template <class T>
    template <class V>
    bool list<T>::contains(V const &v) const
    {
      return std::find(data->begin(), data->end(), v) != data->end();
    }
    template <class T>
    intptr_t list<T>::id() const
    {
      return reinterpret_cast<intptr_t>(&(*data));
    }

    template <class T>
    long list<T>::count(T const &x) const
    {
      return std::count(begin(), end(), x);
    }
    template <class T>
    array<long, list<T>::value> list<T>::shape() const
    {
      array<long, value> res;
      details::init_shape(res, *this, utils::int_<value>{});
      return res;
    }

    /// Empty list
    template <class T>
    list<T> empty_list::operator+(list<T> const &s) const
    {
      return s;
    }
    template <class T, class S>
    sliced_list<T, S> empty_list::operator+(sliced_list<T, S> const &s) const
    {
      return s;
    }
    empty_list empty_list::operator+(empty_list const &) const
    {
      return empty_list();
    }
    empty_list::operator bool() const
    {
      return false;
    }

    template <class T>
    empty_list::operator list<T>() const
    {
      return list<T>(0);
    }

    constexpr long empty_list::size()
    {
      return 0;
    }

    std::ostream &operator<<(std::ostream &os, empty_list const &)
    {
      return os << "[]";
    }

    // declared here and not in list to avoid dependency hell
    template <class T, size_t N>
    list<T> array<T, N>::operator[](types::slice const &s)
    {
      types::slice norm = s.normalize(size());
      list<T> out(norm.size());
      for (long i = 0; i < out.size(); i++)
        out[i] = buffer[norm.get(i)];
      return out;
    }
  }

  namespace utils
  {

    template <class T, class From>
    void reserve(types::list<T> &l, From const &f,
                 typename From::const_iterator *)
    {
      l.reserve(__builtin__::len(f));
    }
  }
}

/* overload std::get */
namespace std
{
  template <size_t I, class T>
  typename pythonic::types::list<T>::reference get(pythonic::types::list<T> &t)
  {
    return t[I];
  }

  template <size_t I, class T>
  typename pythonic::types::list<T>::const_reference
  get(pythonic::types::list<T> const &t)
  {
    return t[I];
  }

  template <size_t I, class T>
  typename pythonic::types::list<T>::value_type
  get(pythonic::types::list<T> &&t)
  {
    return std::move(t)[I];
  }

  template <size_t I, class T>
  typename pythonic::types::sliced_list<T>::reference
  get(pythonic::types::sliced_list<T> &t)
  {
    return t[I];
  }

  template <size_t I, class T>
  typename pythonic::types::sliced_list<T>::const_reference
  get(pythonic::types::sliced_list<T> const &t)
  {
    return t[I];
  }

  template <size_t I, class T>
  typename pythonic::types::sliced_list<T>::value_type
  get(pythonic::types::sliced_list<T> &&t)
  {
    return std::move(t)[I];
  }
}

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{
  template <class T>
  PyObject *to_python<types::list<T>>::convert(types::list<T> const &v)
  {
    Py_ssize_t n = v.size();
    PyObject *ret = PyList_New(n);
    for (Py_ssize_t i = 0; i < n; i++)
      PyList_SET_ITEM(ret, i, ::to_python(v[i]));
    return ret;
  }
  PyObject *to_python<types::empty_list>::convert(types::empty_list const &)
  {
    return PyList_New(0);
  }

  template <class T>
  bool from_python<types::list<T>>::is_convertible(PyObject *obj)
  {
    return PyList_Check(obj) and
           (PyObject_Not(obj) or
            ::is_convertible<T>(PySequence_Fast_GET_ITEM(obj, 0)));
  }

  template <class T>
  types::list<T> from_python<types::list<T>>::convert(PyObject *obj)
  {
    Py_ssize_t l = PySequence_Fast_GET_SIZE(obj);
    types::list<T> v(l);

    PyObject **core = PySequence_Fast_ITEMS(obj);
    std::transform(core, core + l, v.begin(),
                   [](PyObject *o) { return ::from_python<T>(o); });

    return v;
  }
}

#endif

#endif

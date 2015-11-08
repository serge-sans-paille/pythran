//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_SOA_PROXY_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_SOA_PROXY_HPP_INCLUDED

#include <boost/simd/memory/functions/extract.hpp>
#include <boost/simd/memory/functions/insert.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/functor/proxy.hpp>
#include <boost/dispatch/meta/proxy.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/config.hpp>
#include <iterator>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4512) // custom operator= required
#pragma warning(disable: 4522) // multiple operator=
#endif

namespace boost { namespace simd { namespace tag
{
  struct insert_;
  struct extract_;
} } }

namespace boost { namespace simd
{
  template<class T, class X>
  struct soa_proxy
  {
    typedef T value_type;

    BOOST_FORCEINLINE soa_proxy(native<T, X>& data_, std::size_t index_) : data(data_), index(index_)
    {
    }

#ifdef BOOST_MSVC
    BOOST_FORCEINLINE soa_proxy(soa_proxy const& other) : data(other.data), index(other.index)
    {
    }
#endif

    BOOST_FORCEINLINE soa_proxy const& operator=(T const& other) const
    {
      typename dispatch::make_functor<tag::insert_, T>::type()(other, data, index);
      return *this;
    }

    BOOST_FORCEINLINE soa_proxy& operator=(soa_proxy const& other)
    {
      return const_cast<soa_proxy&>(*this = other());
    }

    BOOST_FORCEINLINE soa_proxy const& operator=(soa_proxy const& other) const
    {
      return *this = other();
    }

    BOOST_FORCEINLINE operator T() const
    {
      return typename dispatch::make_functor<tag::extract_, T>::type()(data, index);
    }

    BOOST_FORCEINLINE T const operator()() const
    {
      return static_cast<T const&>(*this);
    }

    native<T, X>& data;
    std::size_t index;

    friend BOOST_FORCEINLINE bool operator!(soa_proxy const& a0) { return !a0(); }
    friend BOOST_FORCEINLINE bool operator==(soa_proxy const& a0, soa_proxy const& a1) { return a0() == a1(); }
    template<class U> friend BOOST_FORCEINLINE bool operator==(U const& a0, soa_proxy const& a1) { return a0 == a1(); }
    template<class U> friend BOOST_FORCEINLINE bool operator==(soa_proxy const& a0, U const& a1) { return a0() == a1; }
    friend BOOST_FORCEINLINE bool operator!=(soa_proxy const& a0, soa_proxy const& a1) { return a0() != a1(); }
    template<class U> friend BOOST_FORCEINLINE bool operator!=(U const& a0, soa_proxy const& a1) { return a0 != a1(); }
    template<class U> friend BOOST_FORCEINLINE bool operator!=(soa_proxy const& a0, U const& a1) { return a0() != a1; }
    friend BOOST_FORCEINLINE std::ostream& operator<<(std::ostream& a0, soa_proxy const& a1) { return a0 << a1(); }
  };

  template<class T>
  struct is_value;

  template<class T, class X>
  struct is_value< soa_proxy<T, X> >
       : mpl::true_
  {
  };

  template<class T>
  struct soa_iterator_base
       : std::iterator<std::random_access_iterator_tag, T>
  {
  protected:
    BOOST_FORCEINLINE soa_iterator_base(T& data_, std::size_t index_ = 0) : data(data_), index(index_) {}


    BOOST_FORCEINLINE void increment()
    {
      ++index;
    }

    BOOST_FORCEINLINE void advance(std::ptrdiff_t n)
    {
      index += n;
    }

    BOOST_FORCEINLINE void decrement()
    {
      --index;
    }

  public:
    BOOST_FORCEINLINE bool
    operator==(soa_iterator_base const& other) const
    {
      return index == other.index;
    }

    BOOST_FORCEINLINE bool
    operator<(soa_iterator_base const& other) const
    {
      return index < other.index;
    }

    BOOST_FORCEINLINE bool
    operator!=(soa_iterator_base const& other) const
    {
      return !(this->operator==(other));
    }

    BOOST_FORCEINLINE bool
    operator>(soa_iterator_base const& other) const
    {
      return other.operator<(*this);
    }

    BOOST_FORCEINLINE bool
    operator<=(soa_iterator_base const& other) const
    {
      return !(other.operator<(*this));
    }

    BOOST_FORCEINLINE bool
    operator>=(soa_iterator_base const& other) const
    {
      return !(this->operator<(other));
    }

    T& data;
    std::size_t index;
  };

  template<class T>
  BOOST_FORCEINLINE std::ptrdiff_t
  operator-(soa_iterator_base<T> const& a0, soa_iterator_base<T> const& a1)
  {
    return a0.index - a1.index;
  }

  template<class T, class X>
  struct soa_iterator : soa_iterator_base< native<T, X> >
  {
    typedef soa_proxy<T, X>      reference;
    typedef soa_proxy<T, X>*     pointer;
    typedef soa_iterator         iterator;

    typedef typename soa_iterator_base< native<T, X> >::difference_type difference_type;

    BOOST_FORCEINLINE soa_iterator(native<T, X>& data_, std::size_t index_ = 0)
      : soa_iterator_base< native<T, X> >(data_, index_)
    {
    }

    BOOST_FORCEINLINE reference
    operator*() const
    {
      return reference(this->data, this->index);
    }

    BOOST_FORCEINLINE iterator&
    operator++()
    {
      this->increment();
      return *this;
    }

    BOOST_FORCEINLINE iterator
    operator++(int)
    {
      iterator tmp = *this;
      this->increment();
      return tmp;
    }

    BOOST_FORCEINLINE iterator&
    operator--()
    {
      this->decrement();
      return *this;
    }

    BOOST_FORCEINLINE iterator
    operator--(int)
    {
      iterator tmp = *this;
      this->decrement();
      return tmp;
    }

    BOOST_FORCEINLINE iterator&
    operator+=(difference_type i)
    {
      this->advance(i);
      return *this;
    }

    BOOST_FORCEINLINE iterator&
    operator-=(difference_type i)
    {
      this->operator+=(-i);
      return *this;
    }

    BOOST_FORCEINLINE iterator
    operator+(difference_type i) const
    {
      iterator tmp = *this;
      return tmp.operator+=(i);
    }

    BOOST_FORCEINLINE iterator
    operator-(difference_type i) const
    {
      iterator tmp = *this;
      return tmp.operator-=(i);
    }

    BOOST_FORCEINLINE reference
    operator[](difference_type i) const
    {
      return *(this->operator+(i));
    }
  };

  template<class T, class X>
  BOOST_FORCEINLINE soa_iterator<T, X>
  operator+(std::ptrdiff_t n, soa_iterator<T, X> const& it)
  {
    return it + n;
  }

  template<class T, class X>
  struct soa_const_iterator : soa_iterator_base< native<T, X> >
  {
    typedef T                   reference;
    typedef T                   const_reference;
    typedef const T*            pointer;
    typedef soa_const_iterator  const_iterator;

    typedef typename soa_iterator_base< native<T, X> >::difference_type difference_type;

    BOOST_FORCEINLINE soa_const_iterator(native<T, X> const& data_, std::size_t index_ = 0)
      : soa_iterator_base< native<T, X> >(const_cast<native<T, X>&>(data_), index_)
    {
    }

    BOOST_FORCEINLINE soa_const_iterator(soa_iterator<T, X> const& other)
      : soa_iterator_base< native<T, X> >(other.data, other.index)
    {
    }

    BOOST_FORCEINLINE const_reference
    operator*() const
    {
      return soa_proxy<T, X>(this->data, this->index);
    }

    BOOST_FORCEINLINE const_iterator&
    operator++()
    {
      this->increment();
      return *this;
    }

    BOOST_FORCEINLINE const_iterator
    operator++(int)
    {
      const_iterator tmp = *this;
      this->increment();
      return tmp;
    }

    BOOST_FORCEINLINE const_iterator&
    operator--()
    {
      this->decrement();
      return *this;
    }

    BOOST_FORCEINLINE const_iterator
    operator--(int)
    {
      const_iterator tmp = *this;
      this->decrement();
      return tmp;
    }

    BOOST_FORCEINLINE const_iterator&
    operator+=(difference_type i)
    {
      this->advance(i);
      return *this;
    }

    BOOST_FORCEINLINE const_iterator&
    operator-=(difference_type i)
    {
      this->operator+=(-i);
      return *this;
    }

    BOOST_FORCEINLINE const_iterator
    operator+(difference_type i) const
    {
      const_iterator tmp = *this;
      return tmp.operator+=(i);
    }

    BOOST_FORCEINLINE const_iterator
    operator-(difference_type i) const
    {
      const_iterator tmp = *this;
      return tmp.operator-=(i);
    }

    BOOST_FORCEINLINE const_reference
    operator[](difference_type i) const
    {
      return *(this->operator+(i));
    }
  };

  template<class T, class X>
  BOOST_FORCEINLINE soa_const_iterator<T, X>
  operator+(std::ptrdiff_t n, soa_const_iterator<T, X> const& it)
  {
    return it + n;
  }
} }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class X, class Origin>
  struct  hierarchy_of< boost::simd::soa_proxy<T, X>
                      , Origin
                      >
  {
    typedef meta::proxy_<Origin>       type;
  };
} } }

#endif

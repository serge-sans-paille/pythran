//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/range/detail/iterator_proxy.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>

namespace boost { namespace simd { namespace detail
{
  /*
    Factorize all the iterator logic, specializing on the Load and Store function tag
    for behavior and pack_proxy for dereferencing to actual pack proxy.
  */
  template< typename Iterator
          , std::size_t C, typename Value
          , typename Load, typename Store
          >
  struct  iterator_base
        : boost::iterator_adaptor< iterator_base<Iterator,C,Value,Load,Store>
                                 , Iterator
                                 , pack<Value, C>
                                 , std::random_access_iterator_tag
                                 , pack_proxy
                                          < dereferencable< typename boost::pointee<Iterator>::type
                                                          , C
                                                          , Load, Store
                                                          >
                                          >
                                 >
  {
    using value_type = Value;
    static const typename iterator_base::difference_type cardinal = C;
    BOOST_FORCEINLINE iterator_base() : iterator_base::iterator_adaptor_() {}

    BOOST_FORCEINLINE explicit
    iterator_base( Iterator p ) : iterator_base::iterator_adaptor_(p) {}

    protected:
    friend class boost::iterator_core_access;

    BOOST_FORCEINLINE
    typename iterator_base::reference dereference() const
    {
      return typename iterator_base::reference(make_deref<C,Load,Store>(&(*this->base())));
    }

    BOOST_FORCEINLINE  void increment() { this->base_reference() += C; }
    BOOST_FORCEINLINE  void decrement() { this->base_reference() -= C; }

    BOOST_FORCEINLINE
    void advance(typename iterator_base::difference_type n) { this->base_reference() += n*C; }

    BOOST_FORCEINLINE typename iterator_base::difference_type
    distance_to(iterator_base const& other) const
    {
      return (other.base() - this->base()) / cardinal;
    }
  };
} } }

#endif

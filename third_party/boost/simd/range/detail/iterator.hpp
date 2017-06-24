//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_ITERATOR_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/function/load.hpp>
#include <boost/simd/function/store.hpp>
#include <boost/simd/range/detail/iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{
  template< typename Iterator
          , std::size_t C = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  struct  iterator
        : detail::iterator_base
                  < Iterator, C
                  , typename std::iterator_traits<Iterator>::value_type, tag::load_, tag::store_
                  >
  {
    typedef detail::iterator_base
                    < Iterator, C
                    , typename std::iterator_traits<Iterator>::value_type, tag::load_, tag::store_
                    >                                           parent;

    BOOST_FORCEINLINE iterator() : parent() {}
    BOOST_FORCEINLINE iterator( parent const& src ) : parent(src) {}
    explicit BOOST_FORCEINLINE iterator(Iterator p) : parent(p) {}
  };

  template<typename Iterator> BOOST_FORCEINLINE iterator<Iterator> begin(Iterator p)
  {
    return iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE iterator<Iterator, C> begin(Iterator p)
  {
    return iterator<Iterator, C>(p);
  }

  template<typename Iterator> BOOST_FORCEINLINE iterator<Iterator> end(Iterator p)
  {
    return iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE iterator<Iterator,C> end(Iterator p)
  {
    return iterator<Iterator, C>(p);
  }
} } }

#endif

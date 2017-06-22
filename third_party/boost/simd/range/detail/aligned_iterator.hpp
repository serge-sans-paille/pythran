//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_ALIGNED_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_ALIGNED_ITERATOR_HPP_INCLUDED

#include <boost/simd/pack.hpp>
#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/function/aligned_store.hpp>
#include <boost/simd/range/detail/iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{
  template< typename Iterator
          , std::size_t C = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  struct  aligned_iterator
        : detail::iterator_base
                  < Iterator, C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::aligned_load_, tag::aligned_store_
                  >
  {
    typedef detail::iterator_base
                    < Iterator, C
                    , typename std::iterator_traits<Iterator>::value_type
                    , tag::aligned_load_, tag::aligned_store_
                    >                                           parent;

    BOOST_FORCEINLINE aligned_iterator() : parent() {}
    BOOST_FORCEINLINE aligned_iterator( parent const& src ) : parent(src) {}
    explicit BOOST_FORCEINLINE aligned_iterator(Iterator p) : parent(p) {}
  };

  template<typename Iterator>
  BOOST_FORCEINLINE aligned_iterator<Iterator> aligned_begin(Iterator p)
  {
    return aligned_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE aligned_iterator<Iterator, C> aligned_begin(Iterator p)
  {
    return aligned_iterator<Iterator, C>(p);
  }

  template<typename Iterator>
  BOOST_FORCEINLINE aligned_iterator<Iterator> aligned_end(Iterator p)
  {
    return aligned_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE aligned_iterator<Iterator,C> aligned_end(Iterator p)
  {
    return aligned_iterator<Iterator, C>(p);
  }
} } }

#endif

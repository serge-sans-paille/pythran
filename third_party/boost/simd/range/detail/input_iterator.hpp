//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/function/load.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/range/detail/input_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{
  template< typename Iterator
          , std::size_t C = pack<typename std::iterator_traits<Iterator>::value_type>::static_size
          >
  struct  input_iterator
        : details::input_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::load_
                  >
  {
    typedef details::input_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::load_
                  >                                           parent;

    BOOST_FORCEINLINE input_iterator() : parent() {}
    BOOST_FORCEINLINE input_iterator( parent const& src ) : parent(src) {}
    explicit BOOST_FORCEINLINE input_iterator(Iterator p) : parent(p) {}
  };

  template<typename Iterator> BOOST_FORCEINLINE input_iterator<Iterator> input_begin(Iterator p)
  {
    return input_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE input_iterator<Iterator, C> input_begin(Iterator p)
  {
    return input_iterator<Iterator, C>(p);
  }

  template<typename Iterator> BOOST_FORCEINLINE input_iterator<Iterator> input_end(Iterator p)
  {
    return input_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE input_iterator<Iterator,C> input_end(Iterator p)
  {
    return input_iterator<Iterator, C>(p);
  }
} } }

#endif

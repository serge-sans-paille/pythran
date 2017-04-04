//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_RANGE_DETAIL_ALIGNED_INPUT_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_RANGE_DETAIL_ALIGNED_INPUT_ITERATOR_HPP_INCLUDED

#include <boost/simd/function/aligned_load.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/range/detail/uncheck_iterator.hpp>
#include <boost/simd/range/detail/input_iterator_base.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/config.hpp>
#include <iterator>

namespace boost { namespace simd { namespace detail
{
  template< typename Iterator
          , std::size_t C = boost::simd::cardinal_of
                            < pack< typename std::iterator_traits<Iterator>
                                                ::value_type
                                  >
                            >::value
          >
  struct  aligned_input_iterator
        : details::input_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::aligned_load_
                  >
  {
    typedef details::input_iterator_base
                  < Iterator
                  , C
                  , typename std::iterator_traits<Iterator>::value_type
                  , tag::aligned_load_
                  >                                           parent;

    BOOST_FORCEINLINE aligned_input_iterator() : parent() {}
    BOOST_FORCEINLINE aligned_input_iterator( parent const& src ) : parent(src) {}

    explicit BOOST_FORCEINLINE aligned_input_iterator(Iterator p) : parent(p)
    {
      // MSVC SCL_SECURE mode adds extra-check that make aligned end
      // difficult to check with this.
      typename details::unchecker<Iterator>::type lp = details::unchecker<Iterator>::call(p);
      boost::ignore_unused(lp);

      #if !defined(NDEBUG)
      using target_pack = pack<typename std::iterator_traits<Iterator>::value_type, C>;
      #endif

      BOOST_ASSERT_MSG
      ( boost::simd::detail::is_aligned(&(*lp) , target_pack::alignment )
      , "The constructor of aligned_input_iterator has been called on a pointer "
        "which alignment is not compatible with the current SIMD extension."
      );
    }
  };

  template<typename Iterator>
  BOOST_FORCEINLINE aligned_input_iterator<Iterator> aligned_input_begin(Iterator p)
  {
    return aligned_input_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE aligned_input_iterator<Iterator, C> aligned_input_begin(Iterator p)
  {
    return aligned_input_iterator<Iterator, C>(p);
  }

  template<typename Iterator>
  BOOST_FORCEINLINE aligned_input_iterator<Iterator> aligned_input_end(Iterator p)
  {
    return aligned_input_iterator<Iterator>(p);
  }

  template<std::size_t C, typename Iterator>
  BOOST_FORCEINLINE aligned_input_iterator<Iterator,C> aligned_input_end(Iterator p)
  {
    return aligned_input_iterator<Iterator, C>(p);
  }
} } }

#endif

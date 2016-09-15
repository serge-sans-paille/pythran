//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_MAKE_DEPENDENT_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_MAKE_DEPENDENT_HPP_INCLUDED

namespace boost { namespace simd { namespace detail
{
  template < class T,  class U >  struct make_dependent
  {
    using type = T;
  };

  template < typename T,  typename U>
  using make_dependent_t = typename make_dependent<T, U>::type;
} } }


#endif

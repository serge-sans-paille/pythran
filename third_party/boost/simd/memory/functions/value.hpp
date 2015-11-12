//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_VALUE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_VALUE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag {
    /*!
     * \brief Define the tag value_ of functor extract
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct value_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::value_     , value       , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::value_, value       , 1 )
} }

#endif

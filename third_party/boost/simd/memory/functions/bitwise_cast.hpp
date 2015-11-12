//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief bitwise_cast generic tag

      Represents the bitwise_cast function in generic contexts.
    **/
    struct bitwise_cast_ : ext::elementwise_<bitwise_cast_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<bitwise_cast_> parent;
    };
  }

  /*!
    @brief Bitwise cast

    bitwise_cast performs a bit-preserving cast of its parameters into an arbitrary
    type @c Target.

    @pre
    @code
    sizeof(a0) == sizeof(Target)
    @endcode

    @tparam Target     Target type to cast toward
    @param  value Value to cast

    @return A value of type @c Target which is bit-equivalent to @c value.

    @usage_output{memory/bitwise_cast.cpp,memory/bitwise_cast.out}
  **/
  template<typename Target, typename Value>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta::
  result_of< typename boost::dispatch::meta::
             dispatch_call<tag::bitwise_cast_( Value const&
                                             , boost::dispatch::meta::as_<Target> const&
                                             )
                          >::type
             ( Value const&
             , boost::dispatch::meta::as_<Target> const&
             )
           >::type
  bitwise_cast(Value const& value)
  {
    typename boost::dispatch::meta::
    dispatch_call<tag::bitwise_cast_( Value const&
                                    , boost::dispatch::meta::as_<Target> const&
                                    )
                 >::type callee;
    dispatch::meta::as_<Target> const target = {};
    return callee(value, target);
  }
} }

#endif

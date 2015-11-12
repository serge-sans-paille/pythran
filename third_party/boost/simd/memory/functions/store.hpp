//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_STORE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief store generic tag

      Represents the store function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct store_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Store a value at an arbitrary memory location

    Store a given value into a random memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both pointer and offset arguments can
    themselves be SIMD register or Fusion Sequences.

    @par Semantic:

    store semantic is similar to aligned_store semantic except for the fact
    that memory location doesn't need to be aligned.

    @param val    Value to stream
    @param ptr    Memory location to stream @c val to
    @param offset Optional memory offset. Can be either a scalar or a SIMD type
                  of same cardinal than the value to write (scatter).
    @param mask   Optional logical mask. Only stores values for which the mask is true.
  **/
  template<typename Value, typename Pointer, typename Offset>
  BOOST_FORCEINLINE void
  store(Value const& val, Pointer const& ptr, Offset const& offset)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::store_ ( Value const&
                                        , Pointer const&
                                        , Offset const&
                                        )>::type          callee;
    callee(val, ptr, offset);
  }

  /// @overload
  template<typename Value, typename Pointer>
  BOOST_FORCEINLINE void
  store(Value const& val, Pointer const& ptr)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::store_ ( Value const&
                                        , Pointer const&
                                        )>::type          callee;
    callee(val, ptr);
  }

  /// @overload for mask scatter
  template<typename Value, typename Pointer, typename Offset, typename Mask>
  BOOST_FORCEINLINE void
  store(Value const& val, Pointer const& ptr, Offset const& offset, Mask const& mask)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::store_ ( Value const&
                                        , Pointer const&
                                        , Offset const&
                                        , Mask const&
                                        )>::type          callee;
    callee(val, ptr, offset, mask);
  }
} }

#endif

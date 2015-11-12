//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief aligned_store generic tag

      Represents the aligned_store function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct aligned_store_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Store a value at an aligned memory location

    Store a given value into an aligned memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both pointer and offset arguments can
    themselves be SIMD register or Fusion Sequences.

    @par Semantic:

    Depending on the type of its arguments, store exhibits different semantics.
    For any @c x of type @c Value, @c ptr of type @c Pointer, @c offset
    of type @c Offset and @c mask of type @c Mask, consider:

    @code
    aligned_store(x,ptr,offset,mask);
    @endcode


    If @c x is a SIMD value, this code is equivalent to:
    - If @c offset is a scalar integer:

      @code
      for(int i=0;i<Value::static_size;++i)
        if mask[i]
          *(ptr+offset+i) = x[i];
      @endcode

    - If @c offset is a SIMD integral register:

      @code
      for(int i=0;i<Value::static_size;++i)
        if mask[i]
          *(ptr+offset[i]) = x[i];
      @endcode

      In this case, the store operation is equivalent to a scatter operation.

    If @c x and @c ptr are Fusion Sequences of size @c N, this code is
    equivalent to:

    @code
    aligned_storeat_c<0>(x),at_c<0>(ptr),offset);
    ...
    aligned_storeat_c<N-1>(x),at_c<N-1>(ptr),offset);
    @endcode

    If @c x is a scalar value, this code is equivalent to:

    @code
    if (mask)
      *(ptr+offset) = x;
    @endcode

    @usage{memory/aligned_store.cpp}

    @par Precondition

    If @c Type is a SIMD register type:

    @code
    is_aligned( ptr + offset - Misalignment )
    @endcode

    evaluates to @c true

    @param val    Value to store
    @param ptr    Memory location to store @c val to
    @param offset Optional memory offset.
    @param mask   Optional logical mask. Only stores values for which the mask is true.

  **/
  template<typename Value, typename Pointer, typename Offset>
  BOOST_FORCEINLINE void
  aligned_store(Value const& val, Pointer const& ptr, Offset const& offset)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_store_ ( Value const&
                                                , Pointer const&
                                                , Offset const&
                                                )>::type          callee;
    callee(val, ptr, offset);
  }

  /// @overload
  template<typename Value, typename Pointer, typename Offset, typename Mask>
  BOOST_FORCEINLINE void
  aligned_store(Value const& val, Pointer const& ptr, Offset const& offset, Mask const& mask)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_store_ ( Value const&
                                                , Pointer const&
                                                , Offset const&
                                                , Mask const&
                                                )>::type          callee;
    callee(val, ptr, offset, mask);
  }

  /// @overload
  template<typename Value, typename Pointer>
  BOOST_FORCEINLINE void aligned_store(Value const& val, Pointer const& ptr)
  {
    typename  boost::dispatch::meta
            ::dispatch_call<tag::aligned_store_ ( Value const&
                                                , Pointer const&
                                                )>::type          callee;
    callee(val, ptr);
  }
} }

#endif

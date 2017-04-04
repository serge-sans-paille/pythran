//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-memory

    @brief Store a value at an aligned memory location

    Store a given value into an aligned memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both @c Pointer and @c Offset arguments can
    themselves be SIMD register or Fusion Sequences.


    @par Header <boost/simd/function/aligned_store.hpp>

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
  template<typename Value, typename Pointer, typename Offset, typename Mask>
  void aligned_store( Value const& val, Pointer const& ptr, Offset const& offset, Mask const& mask) {}

  /*!
   * @overload
   */
  template<typename Value, typename Pointer>
  void aligned_store( Value const& val, Pointer ptr) {}

  /*!
   * @overload
   */
  template<typename Value, typename Pointer, typename Offset>
  void aligned_store( Value const& val, Pointer const& ptr
                    , Offset const& offset) {}

} }
#endif

#include <boost/simd/function/scalar/aligned_store.hpp>
#include <boost/simd/function/simd/aligned_store.hpp>

#endif

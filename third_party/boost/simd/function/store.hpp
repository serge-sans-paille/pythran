//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_STORE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_STORE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-memory

    @brief Store a value at an arbitrary memory location

    Store a given value into a random memory location referenced by either
    a pointer or a pointer and an offset. To support SIMD idioms like data
    scattering or non-POD values, both pointer and offset arguments can
    themselves be SIMD register or Fusion Sequences.


    @par Header <boost/simd/function/store.hpp>

    @par Semantic:

    store semantic is similar to aligned_store semantic except for the fact
    that memory location doesn't need to be aligned.

    @param val    Value to store
    @param ptr    Memory location to store @c val to
    @param offset Optional memory offset. Can be either a scalar or a SIMD type
                  of same cardinal than the value to write (scatter).
    @param mask   Optional logical mask. Only stores values for which the mask is true.

  **/
  template<typename Value, typename Pointer, typename Offset> void store( Value const& val, Pointer const& ptr
                                                                        , Offset const& offset, Mask const& mask) {}

  /*!
    @overload
  **/
  template<typename Value, typename Pointer> void store( Value const& val, Pointer ptr) {}
  /*!
    @overload
  **/
  template<typename Value, typename Pointer, typename Offset> void store( Value const& val, Pointer const& ptr, Offset const& offset) {}

} }
#endif

#include <boost/simd/function/scalar/store.hpp>
#include <boost/simd/function/simd/store.hpp>

#endif

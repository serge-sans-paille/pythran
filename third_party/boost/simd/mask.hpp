//==================================================================================================
/*!
  @file

  Defines the mask adapter for pointer

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MASK_HPP_INCLUDED
#define BOOST_SIMD_MASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy_of.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    // Hint-type for masked pointer
    template<typename T, typename Mask, bool isZero = false> struct masked_pointer
    {
      using pointer       = T*;
      using element_type  = T;
      using mask_type     = Mask;

      BOOST_FORCEINLINE operator      pointer() const BOOST_NOEXCEPT { return ptr;      }
      BOOST_FORCEINLINE pointer       get()     const BOOST_NOEXCEPT { return ptr;      }
      BOOST_FORCEINLINE Mask          mask()    const BOOST_NOEXCEPT { return status;   }
      BOOST_FORCEINLINE element_type  value()   const BOOST_NOEXCEPT { return fallback; }

      pointer       ptr;
      element_type  fallback;
      Mask          status;
    };
  }

  /*!
    @ingroup group-api
    @brief Marks a pointer as being masked

    Wraps a pointer, a condition and an optional base value to be passed to masked memory
    aware operation.

    @param ptr    Value to mask
    @param status Condition associated to the pointer
    @param def    Optional value to use when trying to acces ptr when status is false

    @return A wrapped pointer and condition
  **/
  template<typename T, typename U, typename Mask> BOOST_FORCEINLINE
  detail::masked_pointer<T,Mask> mask(T* ptr, Mask const& status, U const& def)
  {
    return detail::masked_pointer<T,Mask>{ptr,T(def),status};
  }

  /*!
    @overload
  */
  template<typename T, typename Mask>
  BOOST_FORCEINLINE detail::masked_pointer<T,Mask, true> mask(T* ptr, Mask const& status)
  {
    return detail::masked_pointer<T,Mask, true>{ptr,T{0},status};
  }
} }

//--------------------------------------------------------------------------------------------------
// Hierarchy and dispatch helpers for masked_pointer
namespace boost { namespace dispatch
{
#if defined(DOXYGEN_ONLY)
  template<typename T, typename Zero>
  struct masked_pointer_
  {
    using parent = masked_pointer_<typename T::parent, Zero>;
  };
#else
  template<typename T, typename Zero>
  struct masked_pointer_ : masked_pointer_<typename T::parent, Zero>
  {
    using parent = masked_pointer_<typename T::parent, Zero>;
  };

  template<typename T, typename Zero>
  struct  masked_pointer_<unspecified_<T>,Zero> : unspecified_<T>
  {
    using parent = unspecified_<T>;
  };
#endif

  namespace ext
  {
    template<typename T, typename Mask, bool Zero, typename Origin>
    struct hierarchy_of< boost::simd::detail::masked_pointer<T,Mask,Zero>, Origin >
    {
      using base = typename boost::simd::detail::masked_pointer<T,Mask,Zero>::element_type;
      using type = masked_pointer_< boost::dispatch::hierarchy_of_t<base,Origin>
                                  , nsm::bool_<Zero>
                                  >;
    };
  }
} }

#endif

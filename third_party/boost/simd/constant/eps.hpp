//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant
    Generates a value of the chosen type equals to the difference between 1 and the next
    representable value of the chosen type.

    @par Semantic:

    @code
    T r = Eps<T>();
    @endcode

    is equivalent to:

    - if @c T is an integral type:
      @code
      T r = 1;
      @endcode

    - otherwise:
      @code
      T r = std::numeric_limits<boost::dispatch::scalar_of_t<T>>::epsilon();
      @endcode

    @return A value of type @c T equals to the difference between 1 and the next
            representable value of the chosen type.

     @see functional::eps
  **/
  template<typename T> T Eps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generates a value of the chosen type equals to the difference between 1 and the next
      representable value of the chosen type.

      @par Semantic:

      For any value @c x of type @c T:
      @code
      T r = simd::functional::eps( boost::simd::as(x) );
      @endcode

      is equivalent to:

      @code
      T r = simd::Eps<T>();
      @endcode

      @return A value of type @c T equals to the difference between 1 and the next
              representable value of the chosen type.

      @see Eps
    **/
    Value Eps();
  }
} }
#endif

#include <boost/simd/constant/definition/eps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

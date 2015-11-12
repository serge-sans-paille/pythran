//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
  @file
  @brief Definition of sinecosine function
**/

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {

    template < class T > struct sinecosine_ : ext::elementwise_< sinecosine_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< sinecosine_<T> > parent;
    };
  }
  /*!
    @brief sinecosine

    @c sinecosine compute simultaneously the  templatized sine and cosine of the input

    @see @funcref{fast_sincos}, @funcref{sincosine}, @funcref{sincosd}, @funcref{sincos}
    @param a0 angle in radian

    @return A Fusion Sequence containing the  templatized sine and cosine of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&), 2)


  /*!
    @brief sinecosine

    @c sinecosine compute simultaneously the templatized sine and cosine of the input

    @see @funcref{fast_sincos}, @funcref{sincosine}, @funcref{sincosd}, @funcref{sincos}
    @param a0 angle in radian
    @param a1 L-Value that will receive the  templatized sine of @c a0

    @return A Fusion Sequence containing the  templatized cosine of @c a0
  **/

    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&),3)

  /*!
    @brief  sinecosine

    @c sinecosine compute simultaneously the templatized sine and cosine of the input

    @see @funcref{fast_sincos}, @funcref{sincosine}, @funcref{sincosd}, @funcref{sincos}
    @param a0 angle in radian
    @param a1 L-Value that will receive the templatized sined of @c a0
    @param a2 L-Value that will receive the templatized cosine of @c a0

  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&)(A2&),3)


    }

#endif


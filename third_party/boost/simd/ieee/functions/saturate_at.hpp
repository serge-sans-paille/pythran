//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SATURATE_AT_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SATURATE_AT_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief eps generic tag

     Represents the saturate_at function in generic contexts.

     @par Models:
        Hierarchy
    **/
    template <class T>
    struct saturate_at_ : ext::elementwise_< saturate_at_<T> >
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_< saturate_at_<T> > parent;
    };
  }
  /*!
    Returns the saturated value of the first input relative to the symmetric
    interval defined by the template parameter which has to be the tag of
    a constant.

    @par Semantic:

    @code
    T r = saturate <Tag>(x)
    @endcode

    is similar to:

    @code
    if (a0 > Tag<T>()) r =  Tag<T>();
    else if  (a0 < -Tag<T>()) r = -Tag<T>() ;
    else r = a0;
    @endcode

    @param a0

    @return a value of same type as the inputs
  **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL( tag::saturate_at_<A0>
                                            , saturate_at
                                            , (A1 const&)
                                            , 2
                                            )
} }

#endif

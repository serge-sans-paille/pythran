//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALMAX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALMAX_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/global.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/globalfind.hpp>


namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalmax functor
    **/
     struct globalmax_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief maximum  of all the elements of a table expression and its position.

    Computes maximum of all the elements of a table expression and optionaly its linear index

    @par Semantic

    For any table expression @c t:

    @code
    T r = globalmax(t);
    @endcode

    is equivalent to:

    @code
    T r = max(a(_));
    @endcode

    and

    @code
    ptrdiff_t i;
    T m = globalmax(t, i);
    @endcode

    is equivalent to:

    @code
    T r = max(a(_));
    ptrdiff_t i =  globalfind(eq(a0, m))
    @endcode


    @see @funcref{colon}, @funcref{max}, @funcref{globalfind}
    @param a0 Table to process
    @param a1 optional L-value to receive the index

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmax_, globalmax,(A0 const&)(A1&),2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::globalmax_, g_max ,(A0 const&)(A1&),2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmax_       , globalmax, 1)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalmax_       , g_max, 1)
  /// @overload

}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmax_, tag::cpu_,
                              (A0),
                              (unspecified_<A0>)
    )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::maximum_>
                                             , const A0&
      )>::type                           result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::global(nt2::functor<tag::maximum_>(), a0);
    }
  };
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalmax_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)(scalar_<integer_<A1> > )
    )
  {
    typedef typename meta::call<tag::global_(nt2::functor<tag::maximum_>, const A0&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 & a1) const
    {
       result_type tmp =  global(nt2::functor<tag::maximum_>(), a0);
       A1 k = nt2::globalfind(eq(a0, tmp));
       a1 = k;
       return tmp;
    }
  };


} }
#endif

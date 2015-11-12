//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALASUM2_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALASUM2_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalasum2 functor
    **/
    struct globalasum2_ : boost::dispatch::tag::formal_
    {
      /// @brief Parent hierarchy
      typedef boost::dispatch::tag::formal_ parent;
    };
  }
  /*!
    @brief Sum of the absolute square of all the elements of a table expression

    Computes the sum of the absolute square of all the elements of a
    table expression

    @par Semantic

    For any table @c t:

    @code
    T r = globalasum2(t);
    @endcode

    is equivalent to:

    @code
    T r = asum2(a(_))(1);
    @endcode

    @see @funcref{colon}, @funcref{asum2}
    @param a0 Table expression to process

    @return An expression eventually evaluated to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalasum2_, globalasum2, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalasum2_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::asum2_>
                                            , const A0&
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
       return global(nt2::functor<tag::asum2_>(), a0);
    }
  };
} }

#endif

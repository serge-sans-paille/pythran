//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_FUZZY_FUNCTIONS_SIMD_COMMON_ALMOST_GREATER_OR_EQUAL_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_SIMD_COMMON_ALMOST_GREATER_OR_EQUAL_HPP_INCLUDED
#include <nt2/fuzzy/functions/almost_greater_or_equal.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/predecessor.hpp>
#include <nt2/include/functions/simd/is_ord.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/subs.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::almost_greater_or_equal_, tag::cpu_,
                         (A0)(A1)(X),
                         (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
                         ((simd_<integer_<A0>,X>))
                         ((simd_<integer_<A0>,X>))
                         ((simd_<integer_<A1>,X>))
                       )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()( A0 const& a0, A0 const& a1, A1 const& a2) const
    {
      return ge(a0, a1-abs(a2));
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::almost_greater_or_equal_, tag::cpu_,
                         (A0)(A1)(X),
                         (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
                         ((simd_<unsigned_<A0>,X>))
                         ((simd_<unsigned_<A0>,X>))
                         ((simd_<unsigned_<A1>,X>))
                       )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()( A0 const& a0, A0 const& a1, A1 const& a2) const
    {
      return ge(a0, subs(a1, a2));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION_IF(nt2::tag::almost_greater_or_equal_, tag::cpu_,
                         (A0)(A1)(X),
                         (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
                         ((simd_<floating_<A0>,X>))
                         ((simd_<floating_<A0>,X>))
                         ((simd_<integer_<A1>,X>))
                       )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()( A0 const& a0, A0 const& a1, A1 const& a2) const
    {
      return l_and(
               is_ord(a0, a1),
               ge(a0, predecessor(a1, a2))
               );
    }
  };
} }
#endif

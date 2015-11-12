//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_SUBSPACE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_SUBSPACE_HPP_INCLUDED
#include <nt2/linalg/functions/subspace.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/ofsameheight.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/table/table.hpp>
namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::subspace_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type result_type;
    typedef typename nt2::container::table<result_type> t_t;
    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(nt2::ofsameheight(a0, a1), "in subspace a and b must have same height");
      // Compute orthonormal bases, using SVD in "orth" to avoid problems
      // when A and/or B is nearly rank deficient.
      t_t a = nt2::orth(a0);
      t_t b = nt2::orth(a1);
      bool test =  (nt2::size(a,2) < nt2::size(b,2));
      t_t & aa =  test ? a : b;
      t_t & bb =  test ? b : a;
      // Compute the projection the most accurate way, according to [1].
      for (size_t k = 1; k <= nt2::size(aa,2); ++k)
      {
        t_t c = bb - nt2::mtimes(aa(nt2::_,k), nt2::mtimes(nt2::rowvect(aa(nt2::_,k)), bb));
        bb = c;
      }
      // Make sure it's magnitude is less than 1.
      return  nt2::asin(nt2::min(One<result_type>(),nt2::mnorm(bb)));
    }
  };

} }

#endif

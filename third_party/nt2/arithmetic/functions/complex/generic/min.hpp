//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Disributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MIN_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_MIN_HPP_INCLUDED
#include <nt2/arithmetic/functions/min.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
// as matlab min for complex is first on magnitudes and if equality on arguments

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      rtype absa0 = nt2::abs(a0);
      rtype absa1 = nt2::abs(a1);
      result_type r = select(lt(absa0, absa1), a0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, a1), r);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < arithmetic_<A0> > > )
                              (generic_< dry_ < arithmetic_<A1> > > )
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<result_type>::type rtype;
      rtype absa0 = nt2::abs(a0);
      rtype absa1 = nt2::abs(a1);
      result_type r = if_else(lt(absa0, absa1), a0, a1);
      return if_else(eq(absa0, absa1), if_else(is_gtz(a0), a0, a1), r);
    }
  };




  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef A0 rtype;
      rtype absa0 = nt2::abs(a0);
      rtype absa1 = nt2::abs(a1);
      result_type ca0 = result_type(a0);
      result_type r = select(lt(absa0, absa1), ca0, a1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), ca0, a1), r);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_ < arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::min(nt2::real(a0), a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 rtype;
      rtype absa0 = nt2::abs(a0);
      rtype absa1 = nt2::abs(a1);
      result_type ca1 = result_type(a1);
      result_type r = select(lt(absa0, absa1), a0, ca1);
      return select(eq(absa0, absa1), select(lt(arg(a0), arg(a1)), a0, ca1), r);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< dry_ < arithmetic_<A1> > >)

                            )
  {
    typedef typename meta::as_complex<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::min(a0, nt2::real(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)

                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return min(a0, bitwise_cast<A0>(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< dry_< arithmetic_<A1> > >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return min(bitwise_cast<A1>(a0), a1);
    }
  };

} }

#endif

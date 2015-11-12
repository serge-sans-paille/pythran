//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_MNORMEST_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_MNORMEST_HPP_INCLUDED
#include <nt2/include/functions/mnormest.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/sdk/error/warning.hpp>

#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/core/container/table/table.hpp>


namespace nt2 { namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                                (A0)(A1)(A2),
                                ((ast_<A0, nt2::container::domain>))
                                (scalar_<floating_<A1> > )
                                (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::value_type                   value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& s, const A1 &tol, A2& cnt) const
    {
      typedef container::table<value_type>  vtab_t;
      vtab_t x =  nt2::asum1(s, 1)(_);
      cnt = 0;
      result_type e =  nt2::globalnorm2(x);
      if (is_eqz(e)) return e;
      x /= e;
      result_type e0 =  Zero<result_type>();
      while (nt2::abs(e-e0) > tol*e)
        {
          e0 = e;
          vtab_t  sx = nt2::mtimes(s, x);
          //if (nt2::none(nt2::abs(sx(_)))){ sx = nt2::ones/*rand*/(nt2::size(sx)); }
          x = nt2::mtimes(ctrans(s), sx);
          result_type normx =  nt2::globalnorm2(x);
          e = normx/nt2::globalnorm2(sx);
          x /= normx;
          if (++cnt > 100)
          {
            NT2_WARNING ( true
                        , "mnormest has not converged after 100 iterations."
                        );
            break;
          }

        }
      return e;
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                                       (A0)(A1),
                                       ((ast_<A0, nt2::container::domain>))
                                       (scalar_<floating_<A1> > )
                                       )
  {
    typedef typename A0::value_type                   value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1 &tol) const
    {
      size_t cnt = 0;
      return mnormest(a0, tol, cnt);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                                       (A0)(A1),
                                       ((ast_<A0, nt2::container::domain>))
                                       (scalar_<integer_<A1> > )
                                       )
  {
    typedef typename A0::value_type                   value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 &cnt) const
    {
      return mnormest(a0, Sqrteps<result_type>(), cnt);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::as_real<value_type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::mnormest(a0, Sqrteps<result_type>());
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                              (A0),
                              (scalar_<arithmetic_<A0> > )
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return nt2::abs(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<arithmetic_<A0> > )
                              (scalar_<floating_<A1> >)
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1 &) const
    {
      return nt2::abs(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnormest_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<arithmetic_<A0> > )
                              (scalar_<floating_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1 &, A2& cnt) const
    {
      cnt = 0;
      return nt2::abs(a0);
    }
  };

} }


#endif


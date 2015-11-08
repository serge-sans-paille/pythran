//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_DETAILS_ROS_IMPL_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_DETAILS_ROS_IMPL_HPP_INCLUDED
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rsqrt.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/cumsum.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/adjfun.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/oneo_10.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2 { namespace details
{
  template<class T,  typename FLOAT = typename T::value_type >
  class ros_impl
  {
    // f(vec) is minimized.
  public :

    typedef FLOAT                     float_t;
    typedef ptrdiff_t                  bool_t;
    typedef T                         array_t;
    typedef nt2::container::table<FLOAT>         table_t;
    typedef details::optimization_settings<float_t>   otype;

    ros_impl() :
      nbeval(0),
      ok(false)
    {}
    ~ros_impl() {}

    template < class FUNC>
    void optimize( const FUNC& crit,
                   array_t& x, //unkowns init values
                   const otype & o);        //options

    size_t          nbiteration()  const { return nbeval;  }
    bool            convok() const { return ok;  }
    float_t         lasteval() const { return last_eval;  }
  private :

    size_t nbeval;
    float_t last_eval;
    bool ok;
  };


  template<typename T, typename FLOAT>
  template < class FUNC>
  void ros_impl<T, FLOAT>::optimize( const FUNC& crit,
                                     T &x,
                                     const otype& o)
  {
    size_t maxiter =  o.maximum_iterations;
    float_t epsi =  o.absolute_tolerance;
    ok =  false;
    int n = nt2::numel(x);
    bool restart = true;
    array_t xi = nt2::eye(n, n, meta::as_<float_t>());
    array_t xk = x(nt2::_);
    array_t d = nt2::oneo_10(n, 1, meta::as_<float_t>());
    array_t lambda = nt2::zeros(nt2::of_size(n, 1), meta::as_<float_t>());
    nbeval = 1;
    float_t yprev = nt2::Inf<float_t>();
    float_t yfirstfirst = crit(x);
    float_t ycurrent = yfirstfirst;
    do
    {
      float_t ybest=yfirstfirst;
      float_t yfirst;
      do
      {
        yfirst = ybest;
        for (int i=1; i<= n; ++i)
        {
          //array_t xcurrent = xk+d(i)*x(i, nt2::_);
          array_t xcurrent = xk;
          for (int j=1; j<= n; ++j) xcurrent(j) += d(i)*xi(i, j);
          yprev = ycurrent;
          ycurrent = crit(xcurrent);  ++nbeval;
          if (ycurrent<ybest)
          {
            lambda(i)+=d(i);        // success
            d(i)*=Two<float_t>();
            ybest=ycurrent;
            xk = xcurrent;
          }
          else
          {
            d(i)*= Mhalf<float_t>();             // failure
          }
        }
      } while (ybest<yfirst);

      float_t mini = nt2::globalmin(nt2::abs(d));
      restart= (mini>epsi);
      if (ybest<yfirstfirst)
      {
        mini = nt2::globalmin(nt2::abs(xk-x(nt2::_)));
        restart = restart || (mini>epsi);
        if (restart)
        {
          // nous avons:
          // xk[j]-x[j]=(somme sur i de) lambda[i]*xi[i][j];
          array_t A =  nt2::flipud(nt2::cumsum(nt2::flipud(nt2::expand_to(lambda, n, n)*xi)));
          array_t t =  nt2::flipud(nt2::cumsum(nt2::flipud(nt2::sqr(lambda))));
          array_t fact = nt2::rsqrt(nt2::adjfun(functor<nt2::tag::multiplies_>(), t));
          for (int i=n; i>1; --i)
          {
            if (nt2::is_finite(fact(i-1)))
            {
              xi(i, nt2::_)=(lambda(i-1)*A(i, nt2::_)-xi(i-1, nt2::_)*t(i))*fact(i-1);
            }
          }
          xi(1, nt2::_)=A(1, nt2::_)*nt2::rsqrt(t(1));
          x =  xk;
          lambda = zeros(n, 1, meta::as_<float_t>());
          d = repnum(nt2::Oneo_10<float_t>(), n, 1);
          yfirstfirst=ybest;
        }
      }
    } while ((restart)&&(nbeval<maxiter));
    last_eval = ycurrent;
    ok = (nbeval<maxiter);
  }

} }

#endif

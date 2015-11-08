//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_DETAILS_NELDER_IMPL_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_DETAILS_NELDER_IMPL_HPP_INCLUDED

#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/global.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/optimization/options.hpp>

namespace nt2 { namespace details
{
  template<class T,  typename FLOAT = typename T::value_type >
  class nelder_impl
  {
    // sum(fvec^2) is minimized.
  public :

    typedef FLOAT                                     float_t;
//    typedef typename meta::as_logical<float_t>::type                 bool_t;
    typedef ptrdiff_t bool_t;
    typedef T                                         array_t;
    typedef nt2::container::table<FLOAT>              table_t;
    typedef nt2::container::table<bool_t>            btable_t;
    typedef details::optimization_settings<float_t>     otype;
    nelder_impl() : reqmin(Eps<float_t>()),
                    ynewlo(Nan<float_t>()),
                    konvge(10),
                    icount(0),
                    numres(0),
                    ifault(-1) {}
    ~nelder_impl() {}

    template < class FUNC, class S>
    void optimize( const FUNC& crit,
                   T &start,                //unkowns init values
                   const S & steps,   //unkowns initial step values
                   const otype & o);        //options

    size_t          nbiteration()  const { return icount;            }
    float_t         lasteval()     const { return ynewlo;            }
    bool            convok()       const { return ifault == 0;       }

  private :
    float_t                                          reqmin;
    float_t                                          ynewlo;
    size_t                           konvge, icount, numres;
    ptrdiff_t                                        ifault;
  };

  template<typename T, typename FLOAT>
  template < class FUNC, class S>
  void nelder_impl<T, FLOAT>::optimize( const FUNC& fn,
                                        T &start,
                                        const S & step,
                                        const otype& o)
  {
    float_t                     ccoeff, ecoeff, eps, rcoeff;
    size_t n = numel(start);
    icount = 0;
    numres = 0;
    ifault = 0;
    ccoeff = Half<float_t>();
    ecoeff = Two <float_t>();
    eps   =  float_t(0.001);
    rcoeff = One<float_t>();
    reqmin = o.absolute_tolerance;
    size_t kcount = o.maximum_iterations;
    ptrdiff_t jcount = konvge;
    float_t dn = n;
    size_t nn = n + 1;
    float_t del = One<float_t>();
    float_t rq = reqmin * dn;
    table_t p(nt2::of_size(n, nn));
    table_t xmin = start;
    table_t y(nt2::of_size(1, nn));

    for(;;)
    {
      p(nt2::_, nn) = start;
      y(nn) = fn ( start );
      ++icount;
      for(size_t j = 1; j <=  n; ++j)
      {
        float_t x = start(j);
        start(j) += step(j) * del;
        p(_, j) = nt2::colvect(start);
        y(j) = fn ( start );
        ++icount;
        start(j) = x;
      }

// The simplex construction is complete.
// Find highest and lowest y values.  ynewlo = y(ihi) indicates
// the vertex of the simplex to be replaced.

      size_t ilo;
      float_t ylo =  globalmin(y, ilo);
      for(;;)// Inner loop.
      {
        if ( kcount <= icount )  break;
        size_t ihi = 1;
        ynewlo =  globalmax(y, ihi);

// calculate pbar, the centroid of the simplex vertices
// excepting the vertex with y value ynewlo.

        table_t pbar =  (sum(p, 2) - p(_,ihi))/dn;

// Reflection through the centroid.

        table_t pstar = pbar + rcoeff*(pbar-p(_, ihi));
        float_t ystar = fn ( pstar );
        ++icount;
// Successful reflection, so extension.
        if ( ystar < ylo )
        {
          table_t p2star = pbar + ecoeff * ( pstar - pbar );
          float_t y2star = fn ( p2star );
          ++icount;
          if ( ystar < y2star )// Check extension.
          {
            p(_, ihi) = pstar;
            y(ihi) = ystar;
          }                    // Retain extension or contraction.
          else
          {
            p(_, ihi) = p2star;
            y(ihi) = y2star;
          }
        }
        else                 // No extension.
        {
          size_t l = inbtrue(lt(ystar, y));
          if ( l > 1 )
          {
             p(_, ihi) = pstar;
            y(ihi) = ystar;
          }
          else if ( l == 0 )  //%  Contraction on the Y(IHI) side of the centroid.
          {
            table_t p2star = pbar + ccoeff * ( p(_,ihi) - pbar );
            float_t y2star = fn ( p2star );
            ++icount;
            if ( y(ihi) < y2star )  // Contract the whole simplex.
            {
              for(size_t j = 1; j <= nn;  ++j)
              {
                for(size_t i = 1; i <=  n; ++i)
                {
                  p(i,j) = ( p(i,j) + p(i,ilo) ) * Half<float_t>();
                  xmin(i) = p(i,j);
                }
                y(j) = fn ( xmin );
                ++icount;
              }
              ylo = globalmin(y, ilo);
              continue;
            }
            else // Retain contraction.
            {
              p(_, ihi) = p2star;
              y(ihi) = y2star;
            }
          }
          else if ( l == 1 ) //%  Contraction on the reflection side of the centroid.
          {
            table_t p2star = pbar + ccoeff * ( pstar - pbar );
            float_t y2star = fn ( p2star );
            ++icount;
            if ( y2star <= ystar ) //%  Retain reflection?
            {
              p(_,ihi) = p2star;
              y(ihi) = y2star;
            }
            else
            {
              p(_,ihi) = pstar;
              y(ihi) = ystar;
            }
          }
        }
        if ( y(ihi) < ylo )  // Check if YLO improved.
        {
          ylo = y(ihi);
          ilo = ihi;
        }
        --jcount;
        if (jcount > 0) continue;
        if ( icount <= kcount )  //%  Check to see if minimum reached.
        {
          jcount = konvge;
          float_t z =  nt2::global(nt2::functor<nt2::tag::asum2_>(), nt2::center(y));
          if ( z <= rq ) break;
        }
      }
// Factorial tests to check that YNEWLO is a local minimum.
      xmin = p(_, ilo);
      ynewlo = y(ilo);
      if ( kcount < icount )
      {
        ifault = 2;
        break;
      }
      ifault = 0;
      for(size_t i = 1; i <= n; ++i)
      {
        del = step(i) * eps;
        xmin(i) = xmin(i) + del;
        float_t z = fn ( xmin );
        ++icount;
        if ( z < ynewlo )
        {
          ifault = 2;
          break;
        }
        xmin(i) -= del + del;
        z = fn ( xmin );
        ++icount;
        if ( z < ynewlo )
        {
          ifault = 2;
          break;
        }
        xmin(i) += del;
      }
      if ( ifault == 0 )  break;

//%  Restart the procedure.
      start =  nt2::rowvect(xmin);
      del = eps;
      ++numres;
    }

    return;
  }
} }

#endif

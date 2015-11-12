//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_COMMON_HJMIN_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_COMMON_HJMIN_HPP_INCLUDED

#include <nt2/optimization/functions/hjmin.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/oneo_10.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/optimization/output.hpp>
#include <nt2/optimization/options.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace details
{
  template < class T, class FLOAT, class FUNC> class fpoint
  {
    typedef T                                  matrix_t;
    typedef FLOAT                               float_t;
    typedef nt2::container::table<float_t>      table_t;
    typedef FUNC                                 func_t;
    typedef fpoint<T,float_t,func_t>             self_t;

    matrix_t& x;                                // A point in the function's domain.
    float_t fval;                               // Function value at the point.
    const func_t & fproc;                       // Procedure to compute that value
    const bool free_x_on_destructing;           // The flag telling if this fpoint
                                                // "owns" x, and has to dispose of
                                                // its dynamic memory on destruction.


  public:
    template < class M >
    fpoint(M& b, const func_t & f_)
      : x(b),
        fproc(f_),
        free_x_on_destructing(false)
    {
      fval = f_(b);
    }

    ~fpoint(){
      if( free_x_on_destructing ) delete &x;
    };

    float_t f() const { return fval; }

    fpoint(const fpoint& fp) :
      x(*(new matrix_t(fp.x))),
      fval(fp.fval),
      fproc(fp.fproc),
      free_x_on_destructing(true){}

    fpoint& operator = (const fpoint& fp){{
        if (&fp != this){
          x = fp.x;
          fval = fp.fval;
        }
        return *this;
      }
    };

    float_t fiddle_around(const matrix_t& h);
    // Examine the function in the
    // neighborhood of the current point.
    // h defines the radius of the region

    // Proceed in the direction the function
    // seems to decline
    template < class FPOINT >
    friend void update_in_direction(FPOINT & from, FPOINT & to);

    // Decide whether the region embracing
    // the local min is small enough
    bool isstep_relatively_small(const matrix_t& h, const float_t tau)
    {
      for(ptrdiff_t i=nt2::first_index<1>(nt2::colvect(x)); i <= nt2::last_index<1>(nt2::colvect(x)) ; ++i)
        {
          if (float_t(h(i)) >= float_t(tau*(One<float_t>()+nt2::abs(x(i))))) return false;
        }
      return true;
      //TODO nt2::all(h < tau*(One<float_t>()+nt2::abs(x)));
    }
  };


  /*
   * Examine the function f in the vicinity of the current point x
   * by making tentative steps fro/back along each coordinate.
   * Should the function decrease, x is updated to pinpoint thus
   * found new local min.
   * The procedure returns the minimal function value found in
   * the region.
   *
   */
  template < class T, class FLOAT, class FUNC  >
  FLOAT fpoint<T, FLOAT, FUNC >::fiddle_around(const matrix_t& h)
  {
    // Perform a step along each coordinate
    for(ptrdiff_t i = nt2::first_index<1>(nt2::colvect(x)); i <= nt2::last_index<1>(nt2::colvect(x)); ++i)
      {
        const float_t hi = h(i);
        const float_t xi_old = x(i);          // Old value of x[i]
        float_t fnew;
        x(i) = xi_old + hi;
        fnew = fproc(x);
        if ( fnew < fval )// Step caused f to decrease, OK
          {
            fval = fnew; return fval;
          }
        x(i) = xi_old - hi;
        fnew = fproc(x);
        if (fnew < fval )// Step caused f to decrease, OK
          {
            fval = fnew; return fval;
          }
        x(i) = xi_old; // No function decline has been found along this coord, back up
      }
    return fval;
  }

  // Proceed in the direction the function
  // seems to decline
  // to_new = (to - from) + to
  // from = to (before modification)
  template < class FPOINT  >
  void update_in_direction(FPOINT& from, FPOINT& to)
  {
    typedef typename FPOINT::float_t float_t_;
    for(ptrdiff_t i = nt2::first_index<1>(nt2::colvect(from.x)); i <= nt2::last_index<1>(nt2::colvect(from.x)); ++i)
      {
        const float_t_ t = to.x(i);
        to.x(i)  += (t - from.x(i));
        from.x(i) = t;
      }
    from.fval = to.fval;
    to.fval = to.fproc(to.x);
  }
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hjmin_, tag::cpu_
                              , (F)(A)(H)(O)
                            , (unspecified_< F >)
                              ((ast_< A, nt2::container::domain>))
                              ((ast_< H, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename A::value_type                                  value_type;
    typedef typename meta::as_real<value_type>::type                 real_type;
    typedef nt2::container::table<value_type>                            tab_t;
    typedef nt2::container::table<real_type>                            rtab_t;
    typedef optimization::output<tab_t,real_type>       result_type;

    result_type operator()(F crit, A const& aa, H const& hh, O const& o)
    {
      step_reduce_factor = Oneo_10<value_type>();
      iterdone = 0;
      tab_t a = aa;
      tab_t h = hh;
      const real_type tau = o.relative_tolerance;                    // Termination criterion.
      const real_type threshold = o.absolute_tolerance;
      details::fpoint < tab_t, real_type, F> pmin(a,crit);          // Point of min.
      details::fpoint < tab_t, real_type, F> pbase(pmin);           // Base point.
      for(size_t i = 1; i <= o.maximum_iterations ; ++i)            // Main iteration loop.
      {                                                             // pmin is the approximation to min so far.
        iterdone = i;
        if( pbase.fiddle_around(h) < pmin.f() - threshold )
        {                                                           // Function value dropped significantly
          do                                                        // from pmin to the point pbase
            update_in_direction(pmin,pbase);                        // Keep going in the same direction
          while( pbase.fiddle_around(h) < pmin.f() - threshold );   // while it works
          pbase = pmin;                                             // Save the best approx found
        }
        else                                                          // Function didn't fall significantly
        {                                                           // upon wandering around pbas
          h = h*step_reduce_factor;
          if( pbase.isstep_relatively_small(h,tau) )
          {
            valmin = pmin.f();
            result_type that = {a,valmin,iterdone,true,tab_t()};
            return that;
          }
        }
      }
      BOOST_ASSERT_MSG(false, "hjmin was not convergent");
      // We didn't converged -- add message for this
      result_type that = {a,pmin.f(),iterdone,false,tab_t()};
      return that;
    }

  private:
    real_type step_reduce_factor;
    size_t              iterdone;
    value_type            valmin;
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hjmin_, tag::cpu_
                              , (F)(A)(H)(O)
                            , (unspecified_< F >)
                              ((ast_< A, nt2::container::domain>))
                              (scalar_ < unspecified_ < H > > )
                              (unspecified_<O>)
                            )
  {
    typedef typename nt2::meta::call < nt2::tag::repnum_(size_t, size_t) > ::type T0;
    typedef typename nt2::meta::call < nt2::tag::hjmin_(F, A const &, T0, O const&)>::type result_type;
    result_type operator()(F f, A const& aa, H const& h0, O const& o)
    {
      return hjmin(f, aa, nt2::repnum(h0, size_t(1), nt2::numel(aa)), o);
    }
  };
} }
#endif

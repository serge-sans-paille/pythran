//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_MPOWER_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_MPOWER_HPP_INCLUDED

#include <nt2/linalg/functions/mpower.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/logm.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/modf.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/isdiagonal.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/power.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/sqrtm.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/utility/max_extent.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/assert.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mpower_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (scalar_<unspecified_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mpower_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      nt2::expm(nt2::log(a0)*a1)
    )
  };

  // mpower tag only used for matrix/scalar
  template<class Domain, int N, class Expr>
  struct size_of<tag::mpower_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename boost::proto::result_of::child_c<Expr&,1>::value_type  c1_t;
    typedef typename utility::result_of::max_extent<c0_t, c1_t, _2D>::type       result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      BOOST_ASSERT_MSG( isscalar(boost::proto::child_c<1>(e)) && issquare(boost::proto::child_c<0>(e)),
                       "mpower needs a square matrix and a scalar or a scalar and a square matrix");

      return nt2::utility::max_extent(boost::proto::child_c<0>(e), boost::proto::child_c<1>(e), _2D());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::mpower_, boost::mpl::long_<2>, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename A1::value_type                                  value_type;
    typedef typename meta::as_real<value_type>::type                     r_type;
    typedef std::complex<r_type>                                      cplx_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
    {
      typedef typename meta::is_complex<value_type>::type is_cplx;
      compute_power(boost::proto::child_c<0>(a1), value_type(boost::proto::child_c<1>(a1)), a0, is_cplx());
    }

  private:
    template < class T >
    BOOST_FORCEINLINE static void compute_power(const T& a, r_type b, A0& r, const boost::mpl::false_&)
    {
      r.resize(extent(a));
      typedef typename A1::index_type        index_type;
      typedef table<value_type, index_type> result_type;
      typedef table<cplx_type>                  ct_type;
      bool is_ltz_b = is_ltz(b);
      if(is_ltz_b) b = -b;
      r_type m = nt2::trunc(b);
      r_type f = b-m;
      ct_type q, t;
      nt2::tie(q, t) = schur(a, nt2::cmplx_);
      if(isdiagonal(t))
      {
        t = nt2::from_diag(nt2::pow(diag_of(t), m));
        if(is_ltz_b) t = nt2::inv(t);
        BOOST_AUTO_TPL(z, nt2::mtimes(q, nt2::mtimes(t, nt2::trans(nt2::conj(q)))));
        transtype(r, z, typename nt2::meta::is_complex<value_type>::type());
        return;
      }
      else
      { //use iterative method
        r = nt2::eye(nt2::size(a), meta::as_<r_type>());
        result_type rf = r;
        if(m)
        {
          result_type a00 = a;
          while (m >= nt2::One<r_type>())
          {
            if (nt2::is_odd(m))
            {
              r =  nt2::mtimes(a00, r);
            }
            a00 =  nt2::mtimes(a00, a00);
            m =  nt2::trunc(m/2);
          }
        }
        if(!f)
        {
          if(is_ltz_b) r = nt2::inv(r);
          return;
        }
        else
        {
          result_type a00 = nt2::sqrtm(a);
          r_type thresh = nt2::Half<r_type>();
          while(f > Zero<r_type>())
          {
            if(f >= thresh)
            {
              rf = nt2::mtimes(rf, a00);
              f -= thresh;
            }
            thresh *= nt2::Half<r_type>();
            a00 =  nt2::sqrtm(a00);
          }
        }
        r= nt2::mtimes(r, rf);
        if(is_ltz_b) r = nt2::inv(r);
      }
    }
    template < class T >
    BOOST_FORCEINLINE static void compute_power(const T& a, value_type b, A0& r, const boost::mpl::true_& )
    {
      if(is_real(b))
        compute_power(a, real(b), r, boost::mpl::false_());
      else
        r = nt2::expm(b*nt2::logm(a));
    }

    template < class T1, class T2>
    BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::true_ const &)
    {
      r = z;
    }
    template < class T1, class T2 >
    BOOST_FORCEINLINE static void transtype(T1& r, T2& z, boost::mpl::false_ const &)
    {
      r = real(z);
    }

  };

} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_COMMON_QMTC_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_COMMON_QMTC_HPP_INCLUDED

#include <nt2/integration/functions/qmtc.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/fifteen.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/globalmean.hpp>
#include <nt2/include/functions/globalstdev.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/quasi.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalprod.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/integration/output.hpp>
#include <nt2/integration/options.hpp>
#include <nt2/integration/waypoints.hpp>
#include <nt2/integration/fudge.hpp>

namespace nt2 { namespace details
{
  template<class T, class V> class qmtc_impl
  {
  public :
    typedef T                                              input_t;
    typedef V                                              value_t;
    typedef typename meta::as_real<value_t>::type           real_t;
    typedef details::integration_settings<T, V, tag::qmtc_>     o_t;
    typedef container::table<value_t>                       vtab_t;
    typedef container::table<input_t>                       itab_t;
    typedef container::table<real_t>                        rtab_t;
    typedef container::table<bool>                          btab_t;

    qmtc_impl() :   err_(Nan<real_t>()),
                    fcnt_(0),
                    res_(){}
    ~qmtc_impl() {}

    size_t    nbeval()  const { return fcnt_;  }
    real_t lasterror()  const { return err_;   }
    bool          ok()  const { return true;   }
    value_t   result()  const { return res_;   }
    size_t      warn()  const { return 0;      }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & ranges, const o_t & o)
    {
      init(o);
      itab_t facts =  ranges(nt2::_,begin_+1, nt2::_)-ranges(nt2::_,begin_, nt2::_);
      itab_t vols = nt2::prod(facts);
      input_t total_vol = globalasum1(vols);
      itab_t coefs = real_t(maxfunccnt_)*nt2::abs(vols)*nt2::rec(total_vol);
      BOOST_ASSERT_MSG(size(ranges, 2) == 2, "ranges must be a nx2xm expression");
      size_t l = size(ranges, 3);
      res_ = nt2::Zero<value_t>();
      for(size_t i=1; i <= l; ++i)
      {
        nbpts_ = coefs(i);
        res_ += compute(f, ranges(nt2::_,nt2::_,i), vols(i), facts(i));
        fcnt_+= nbpts_;
      }
    }
   private :
    real_t         err_;
    size_t  maxfunccnt_;
    size_t        fcnt_;
    value_t        res_;
    size_t       nbpts_;
    bool   compute_err_;

  private:
    inline void init( const o_t & o)
    {
      maxfunccnt_ = o.maxfunccnt;
      compute_err_ = o.compute_error;
      if (compute_err_) err_ = nt2::Zero<real_t>();
    }

    template <class FUNC, class X>
    value_t compute(const  FUNC &f, const X&ranges, const input_t & vol,  input_t fact)
    {
      size_t n = size(ranges, 1);
      BOOST_AUTO_TPL(r1, ranges(nt2::_, begin_));
      BOOST_AUTO_TPL(r1ex, nt2::expand_to(r1,   nt2::of_size(n, nbpts_)));
      BOOST_AUTO_TPL(r2ex, nt2::expand_to(fact, nt2::of_size(n, nbpts_)));
      rtab_t rnd = nt2::quasi(n, nbpts_, nt2::meta::as_<real_t>());
      BOOST_AUTO_TPL(x, nt2::fma(rnd, r2ex, r1ex));
      BOOST_AUTO_TPL(z, f(x));
      if (compute_err_)
      {
        real_t fnbpt = real_t(nbpts_);
        err_ += nt2::pow(nt2::log(fnbpt), real_t(n))*nt2::Three<real_t>()*vol*nt2::real(nt2::globalstdev(z))/fnbpt;
      }
      return vol*nt2::globalmean(z);
    }
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::qmtc_, tag::cpu_
                              , (F)(X)(O)
                              , (unspecified_< F >)
                              ((ast_<X, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename O::value_t                                             value_t;
    typedef typename O::input_t                                             input_t;
    typedef typename O::real_t                                               real_t;
    typedef typename O::result_t                                           result_t;
    typedef typename O::restab_t                                           restab_t;
    typedef typename boost::is_same<input_t,real_t>::type           input_is_real_t;
    typedef nt2::integration::output<restab_t,real_t>                   result_type;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::qmtc_impl<input_t, value_t> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok(), q.warn()};
      return that;
    }
  };
} }
#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_PRIMITIVE_HPP_INCLUDED
#define NT2_INTEGRATION_PRIMITIVE_HPP_INCLUDED
/*!
 * \file
 * \brief Defines and implements the nt2::primitive function
 */

#include <nt2/integration/interface.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/extremum/extremum.hpp>

namespace nt2
{
  template<class TAG, class F, class X> BOOST_FORCEINLINE
  typename details::integration<F, X, TAG>::result_type
  primitive(F f, X x)
  {
    typedef details::integration<F, X, TAG>        i_t;
    typedef typename i_t::input_t              input_t;
    typedef typename i_t::result_t            result_t;
    typedef typename i_t::real_t                real_t;
    typedef container::table<result_t>          rtab_t;
    typedef typename details::h2_t<input_t>::ab_t ab_t;
    typedef typename i_t::result_type      result_type;

    size_t nbres = nt2::numel(x);
    rtab_t res(of_size(1, nbres));
    real_t  err = Zero<real_t>();
    size_t warn = 0;
    size_t fcnt = 0;
    if (numel(x) == 0)
    {
      result_type r = { rtab_t(), err, 0, true, 0};
      return r;
    }
    res(1) =  nt2::Zero<result_t>();
    for(size_t i=2; i <= nbres; i++)
    {
      BOOST_AUTO_TPL(r, (details::integration<F, ab_t, TAG>::call(f, nt2::cath(x(i-1), x(i)))));
      res(i) = res(i-1)+r.integrals(end_);
      err  = nt2::max(err, r.errors);
      warn = nt2::max(warn, r.warning);
      fcnt += r.eval_count;
    }
    result_type r = { res, err, fcnt, warn == 0, warn};
    return r;
  }
}

#endif

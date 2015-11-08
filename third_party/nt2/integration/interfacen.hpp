//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_INTERFACEN_HPP_INCLUDED
#define NT2_INTEGRATION_INTERFACEN_HPP_INCLUDED


/*!
 * \file
 * \brief Defines and implements the calls for integration methods
 */

#include <nt2/include/functor.hpp>
#include <nt2/sdk/option/options.hpp>
#include <nt2/integration/options.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/sdk/meta/result_of.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2
{
  namespace details
  {
    template < class F,  class X,  class TAG> struct integration_n
    {
      typedef TAG                                                                          tag_t;
      typedef typename X::value_type                                                     input_t;
      typedef container::table<input_t>                                                   itab_t;
      typedef typename meta::result_of<F(itab_t)>::type                                   vtab_t;
      typedef typename vtab_t::value_type                                                value_t;
      typedef typename meta::as_real<input_t>::type                                       real_t;
      typedef typename details::integration_settings<input_t,value_t,tag_t>           settings_t;
      typedef typename boost::dispatch::meta::call<tag::horzcat_(input_t, input_t)>::type   ab_t;
      typedef typename meta::is_complex<value_t>::type                               v_is_cplx_t;
      typedef typename boost::mpl::if_<v_is_cplx_t,value_t,input_t>::type               result_t;
      typedef typename boost::dispatch::meta::call<tag_t(F,X,settings_t)>::type      result_type;

      static result_type call(F f, X const& x)
      {
        typename boost::dispatch::make_functor<tag_t, F>::type callee;
        return callee ( f,x, settings_t());
      }
      template<class Xpr>
      static result_type call(F f, X const& x, nt2::details::option_expr<Xpr> const& opt)
      {
        typename boost::dispatch::make_functor<tag_t, F>::type callee;
        return callee (f, x, settings_t(opt));
      }
    };
  }
}

#endif

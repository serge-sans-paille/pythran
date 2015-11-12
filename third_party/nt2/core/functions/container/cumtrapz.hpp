//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CONTAINER_CUMTRAPZ_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CONTAINER_CUMTRAPZ_HPP_INCLUDED

#include <nt2/core/functions/cumtrapz.hpp>
#include <nt2/include/functions/adjfun.hpp>
#include <nt2/include/functions/putalong.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/cumsum.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  meta::call<tag::cumtrapz_(const A0&, size_t)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& y) const
    {
      size_t dim = nt2::firstnonsingleton(y);
      return nt2::cumtrapz(y, dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename  meta::call<tag::cumtrapz_(const A0&, size_t)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const& y) const
    {
      size_t dim =  nt2::firstnonsingleton(y);
      return nt2::cumtrapz(x, y, dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_ < A0> >)
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename  meta::call<tag::cumtrapz_(const A1&, size_t)>::type          T0;
    typedef typename  meta::call<tag::multiplies_(T0, A0 const&)>::type   result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const& y) const
    {
      size_t dim =  nt2::firstnonsingleton(y);
      return nt2::cumtrapz(y, dim)*x;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_ < A0> >)
                              ((ast_<A1, nt2::container::domain>))
                               (scalar_<integer_<A2> > )
                            )
  {
    typedef typename  meta::call<tag::cumtrapz_(const A1&, size_t)>::type          T0;
    typedef typename  meta::call<tag::multiplies_(T0, A0 const&)>::type   result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const& y, const A2& dim) const
    {
      return nt2::cumtrapz(y, dim)*x;
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> > )
                            )
  {
    typedef typename A0::value_type                                                           value_type;
    typedef typename meta::as_real<value_type>::type                                           real_type;
    typedef typename A0::extent_type                                                         extent_type;
    typedef typename meta::call < tag::adjfun_(nt2::functor<tag::plus_>, A0 const&, const A1&)>::type T2;
    typedef typename meta::call < tag::cumsum_(T2,const A1&)>::type                                   T3;
    typedef typename meta::call < tag::multiplies_(real_type, T3)>::type                              T4;
    typedef typename meta::call < tag::Zero(extent_type,  nt2::meta::as_<value_type>)>::type          T5;
    typedef typename meta::call < tag::cat_(const A1&, T5, T4)>::type                        result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& y, const A1& dim) const
    {
      extent_type sizee = extent(y);
      if((size_t(dim) <= numel(sizee)) && sizee[dim-1]) sizee[dim-1] = 1;
      BOOST_AUTO_TPL(tmp2, nt2::adjfun(functor<nt2::tag::plus_>(), y, dim ));
      BOOST_AUTO_TPL(tmp3, nt2::cumsum(tmp2, dim));
      BOOST_AUTO_TPL(tmp4, nt2::multiplies(Half<real_type>(), tmp3));
      BOOST_AUTO_TPL(tmp5, nt2::zeros(sizee, nt2::meta::as_<value_type>()));
     return  nt2::cat(dim, tmp5, tmp4);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cumtrapz_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A2> > )
                            )
  {
    typedef typename A0::value_type                                                           value_type;
    typedef typename meta::as_real<value_type>::type                                           real_type;
    typedef typename A0::extent_type                                                         extent_type;
    typedef typename meta::call < tag::adjfun_(functor<nt2::tag::plus_>, const A1&, const A2&)>::type T1;
    typedef typename meta::call < tag::putalong_(const A0&, const A2&)>::type                         T2;
    typedef typename meta::call < tag::diff_(T2, size_t, const A2&)>::type                            T3;
    typedef typename meta::call < tag::extent_(T1)>::type                                            T1b;
    typedef typename meta::call < tag::expand_to_(T3, T1b)>::type                                     T4;
    typedef typename meta::call < tag::multiplies_(T4, T1)>::type                                     T5;
    typedef typename meta::call < tag::cumsum_(T5, const A2&)>::type                                  T6;
    typedef typename meta::call < tag::multiplies_(real_type, T6)>::type                              T7;
    typedef typename meta::call < tag::Zero(extent_type, nt2::meta::as_<value_type>)>::type           T8;
    typedef typename meta::call < tag::cat_(const A2&, T8, T7)>::type                        result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& x, const A1& y, const A2& dim) const
    {
      BOOST_ASSERT_MSG(size(y, dim) == numel(x), "x numel is not equal to y dimension in dim direction");
      extent_type sizee = extent(y);
      if((size_t(dim) <= numel(sizee))&&sizee[dim-1]) sizee[dim-1] = 1;
      BOOST_AUTO_TPL(tmp1, nt2::adjfun(functor<nt2::tag::plus_>(), y, dim ));
      BOOST_AUTO_TPL(tmp2, nt2::putalong(x, dim));
      BOOST_AUTO_TPL(tmp3, nt2::diff(tmp2, size_t(1), dim));
      BOOST_AUTO_TPL(tmp4, nt2::expand_to(tmp3, extent(tmp1)));
      BOOST_AUTO_TPL(tmp5, nt2::multiplies(tmp4,tmp1));
      BOOST_AUTO_TPL(tmp6, nt2::cumsum(tmp5, dim));
      BOOST_AUTO_TPL(tmp7, nt2::multiplies(Half<real_type>(), tmp6));
      BOOST_AUTO_TPL(tmp8, zeros(sizee, nt2::meta::as_<value_type>()));
      return  nt2::cat(dim, tmp8, tmp7);
    }
  };
} }

#endif

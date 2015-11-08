//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_VECNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_VECNORM_HPP_INCLUDED

#include <nt2/linalg/functions/vecnorm.hpp>
#include <nt2/include/functions/scalar/vecnorm.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/is_finite.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/functions/scalar/min.hpp>
#include <nt2/include/functions/scalar/max.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/norm2.hpp>
#include <nt2/include/functions/normp.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0),
                                     ((ast_<A0, nt2::container::domain>))
                                     )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>
                                          ::type  result_type;
    inline result_type operator()(A0 const &a0) const
      {
        return norm2(a0(_));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0)(A1),
                                     ((ast_<A0, nt2::container::domain>))
                                     (scalar_<arithmetic_<A1> > )
                                     )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>
                                          ::type  result_type;
    inline result_type operator()(A0 const &a0, A1 const& a1) const
      {
        result_type choice = result_type(a1);
        if (is_nan(choice)) return Nan<result_type>();
        if (choice == Two<result_type>()){
          return nt2::norm2(a0(_));
        } else if (choice == One<result_type>()){
          return nt2::norm1(a0(_));
        } else if (nt2::is_finite(choice)){
          return nt2::normp(a0(_), choice);
        } else if (is_gtz(choice)){
          return nt2::max(nt2::abs(a0(_)));
        } else {
          return nt2::min(nt2::abs(a0(_)));
        }
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0)(A1),
                                     (scalar_<arithmetic_<A0> > )
                                     (scalar_<arithmetic_<A1> > )
                                     )
  {
    typedef typename meta::as_real<A0>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>
                                          ::type  result_type;
    inline result_type operator()(A0 const &a0, A1 const& ) const
      {
        return result_type(nt2::abs(a0));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0),
                                     (scalar_<arithmetic_<A0> > )
                                     )
  {
    typedef typename meta::as_real<A0>::type rtype_t;
    typedef typename boost::dispatch::meta::as_floating<rtype_t>
                                          ::type  result_type;
    inline result_type operator()(A0 const &a0) const
      {
        return result_type(nt2::abs(a0));
      }
  };

} }

#endif

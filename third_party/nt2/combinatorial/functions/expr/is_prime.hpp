//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_EXPR_IS_PRIME_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_EXPR_IS_PRIME_HPP_INCLUDED

#include <nt2/combinatorial/functions/is_prime.hpp>
#include <nt2/include/functions/scalar/bitwise_cast.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/primes.hpp>
#include <nt2/include/functions/scalar/saturate.hpp>
#include <nt2/include/functions/scalar/rem.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/mpl/if.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::is_prime_, tag::cpu_,
                             (A0),
                             (unspecified_<A0>)
                             )
  {
    typedef typename A0::value_type                                   value_type;
    typedef typename meta::as_logical<value_type>::type              bvalue_type;
    typedef nt2::container::table<bvalue_type>                       result_type;
    typedef typename nt2::meta::as_integer<value_type>::type         ivalue_type;
    typedef typename boost::mpl::if_<meta::is_floating_point<value_type>,
                                     uint32_t, ivalue_type>::type          itype;
    NT2_FUNCTOR_CALL(1)
      {
        itype m = nt2::oneplus(nt2::sqrt(nt2::globalmax(a0)));
        nt2::container::table<itype> p = nt2::primes(m);
        result_type r(nt2::of_size(1, nt2::numel(a0)));

        for(size_t i=1; i <= numel(a0) ; i++)
          {
            r(i) = is_prime(a0(i), p);
          }
        return r;
      }
  };
} }
#endif

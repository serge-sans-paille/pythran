//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLPK_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLPK_HPP_INCLUDED

#include <nt2/elliptic/functions/ellpk.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellpk_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
        if (a0>One<A0>()||(is_ltz(a0)))
          return Nan<A0>();
        else if (a0<=Eps<A0>())
          return double_constant<A0,0x3ff62e42fefa39efll>() - Half<A0>()*nt2::log(a0);
        else
          return  horner< NT2_HORNER_COEFF(double, 11,
                ( 0x3f2215efc8230a6dll,0x3f62ae0bc8b87afall,0x3f8054b18cadb000ll
                , 0x3f84308b0e9b854fll,0x3f7c28da13d45e88ll,0x3f7959a5cfd45b0cll
                , 0x3f8200e6e2fae761ll,0x3f8e97d672352414ll,0x3f9fa05b1905c419ll
                , 0x3fb8b90bfbea387cll,0x3ff62e42fefa39efll
                ) ) > (a0)
                - log(a0)
                * horner< NT2_HORNER_COEFF(double, 11,
                ( 0x3efed61f30e56ff3ll,0x3f4df4bcbee9b2c2ll,0x3f7855271dd88f27ll
                , 0x3f8fb6a073d2d3f0ll,0x3f987b9729ca99fbll,0x3f9ed7e6a0857bd9ll
                , 0x3fa323227b179faall,0x3fa8fffcf8d1c38dll,0x3fb1fffffeb22f00ll
                , 0x3fbfffffffffdba4ll,0x3fe0000000000000ll
                ) ) > (a0);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellpk_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
        if (a0>One<A0>()||(is_ltz(a0)))
          return Nan<A0>();
        else if (a0<=Eps<A0>())
          return single_constant<A0,0x3fb17218>() - Half<A0>()*nt2::log(a0);
        else
          return  horner< NT2_HORNER_COEFF(float, 11,
                                  ( 0x3910af7e,0x3b15705e,0x3c02a58c,0x3c218458
                                  , 0x3be146d1,0x3bcacd2e,0x3c100737,0x3c74beb4
                                  , 0x3cfd02d9,0x3dc5c860,0x3fb17218
                                  )
                                )
                        > (a0)
          - nt2::log(a0)
                * horner< NT2_HORNER_COEFF(float, 11,
                                  ( 0x37f6b0fa,0x3a6fa5e6,0x3bc2a939,0x3c7db504
                                  , 0x3cc3dcb9,0x3cf6bf35,0x3d191914,0x3d47ffe8
                                  , 0x3d900000,0x3e000000,0x3f000000
                                  )
                                )
                        > (a0);
      }
  };
} }

#endif

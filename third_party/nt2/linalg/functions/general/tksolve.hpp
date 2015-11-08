//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_TKSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_TKSOLVE_HPP_INCLUDED

#include <nt2/linalg/functions/tksolve.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/conj.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tksolve_, tag::cpu_
                              , (A0)(A1)
                              , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    typedef table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return tksolve(a0, a1, 'N');
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tksolve_, tag::cpu_
                              , (A0)(A1)(A2)
                              , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              )
  {
    typedef typename A0::value_type       value_type;
    typedef typename A0::index_type       index_type;
    Typedef  nt2::table<value_type, index_type> result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef nt2::table<value_type > tab_t;
      size_t n =  length(a0);
      tab_t a00 = a0;
      tab_t x = nt2::zeros(nt2::sqr(n), 1, as_<value_type>());
      tab_t i = eye(n, nt2::as_<value_type>());

      if (a2 != 'T')
      {
        //    % Forward substitution.
        for (size_t i = 1; i <= n; ++i)
        {
          tab_t temp = a1(_(n*(i-1)+1, n*i));
          for (size_t j = 1; j <= i-1; ++j)
          {
            temp -= a00(j,i)*x(_(n*(j-1)+1, n*j));
          }
          x(_(n*(i-1)+1, n*i)) = nt2::linsolve((a00 + a00(i,i)*i), temp);
        }
      }
      else
      {
        //    Back substitution.
        for (size_t  i = n; i <= 1; --i)
        {
          temp = a1(_(n*(i-1)+1, n*i));
          for (size_t j = i+1; i <= n; ++i)
          {
            temp -= nt2::conj(a00(i,j))*x(_(n*(j-1)+1, n*j));
          }
          x(n*(i-1)+1:n*i) = nt2::linsolve((trans(a00) + conj(a00(i,i))*i), temp);
        }

      }
    }
  };
} }

#endif

// function x = tksolve(R, b, tran)
// %TKSOLVE     Solves block triangular Kronecker system.
// %            x = TKSOLVE(R, b, TRAN) solves
// %                  A*x = b  if TRAN = '',
// %                 A'*x = b  if TRAN = 'T',
// %            where A = KRON(EYE,R) + KRON(TRANSPOSE(R),EYE).
// %            Default: TRAN = ''.

// if nargin < 3, tran = ''; end

// n = max(size(R));
// x = zeros(n^2,1);

// I = eye(n);

// if isempty(tran)

//    % Forward substitution.
//    for i = 1:n
//        temp = b(n*(i-1)+1:n*i);
//        for j = 1:i-1
//            temp = temp - R(j,i)*x(n*(j-1)+1:n*j);
//        end
//        x(n*(i-1)+1:n*i) = (R + R(i,i)*I) \ temp;
//    end

// elseif strcmp(tran,'T')

//    % Back substitution.
//    for i = n:-1:1
//        temp = b(n*(i-1)+1:n*i);
//        for j = i+1:n
//            temp = temp - conj(R(i,j))*x(n*(j-1)+1:n*j);
//        end
//        x(n*(i-1)+1:n*i) = (R' + conj(R(i,i))*I) \ temp;
//    end

// end

// return

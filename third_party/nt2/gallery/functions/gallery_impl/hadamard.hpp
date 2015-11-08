//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HADAMARD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HADAMARD_HPP_INCLUDED
#include <nt2/gallery/functions/hadamard.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/hankel.hpp>
#include <nt2/include/functions/toeplitz.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hadamard_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::hadamard_
                                          , container::domain
                                          , std::size_t
                                          , T
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, T const& tgt) const
    {
      return  boost::proto::
              make_expr<nt2::tag::hadamard_, container::domain>
              ( std::size_t(a0)
              , tgt
              , _2D(a0,a0)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hadamard_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::hadamard_
                                          , container::domain
                                          , std::size_t
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return  boost::proto::
              make_expr<nt2::tag::hadamard_, container::domain>
              ( std::size_t(a0)
              , meta::as_<double>()
              , _2D(a0,a0)
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::hadamard_,N,nt2::container::domain>))
                            )
  {
    typedef A0&                                                          result_type;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type            p_type;
    typedef typename meta::strip<p_type>::type                             tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type>::type      t_type;
    typedef typename t_type::type                                         value_type;
    typedef typename boost::dispatch::meta::as_integer<value_type, signed>::type     i_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      value_type fn =  value_type(n);
      table<value_type> ns =  nt2::cons(of_size(1, 3), fn, fn/12, fn/20);
      table<i_type> ee(nt2::of_size(1, 3));
      table<value_type> ff(nt2::of_size(1, 3));
//      nt2::frexp(ns, ff, ee);
      nt2::frexp(ns(1), ff(1), ee(1));
      nt2::frexp(ns(2), ff(2), ee(2));
      nt2::frexp(ns(3), ff(3), ee(3));
      BOOST_AUTO_TPL(kk, nt2::find(nt2::logical_and(eq(ff, nt2::Half<value_type>()), is_gtz(ee))));
      BOOST_ASSERT_MSG(!nt2::isempty(kk), "n must be of form 2^m or  12*2^m or 20*2^m");
      size_t k =  kk(1);
      i_type e = nt2::minusone(ee(k));
      out.resize(nt2::of_size(n, n));
      table<value_type> h;
      if (k == 1) //    n = 1 * 2^e;
      {
        h = nt2::One<value_type>();
      }
      else if ( k == 2) // N = 12 * 2^e;
      {
        h = nt2::vertcat(nt2::ones(1,12,meta::as_<value_type>()),
                         nt2::horzcat(nt2::ones(11,1,meta::as_<value_type>()),
                                      nt2::toeplitz(cons<value_type>(of_size(1, 11), -1, -1,  1, -1, -1, -1,  1,  1,  1, -1,  1),
                                                    cons<value_type>(of_size(1, 11), -1,  1, -1,  1,  1,  1, -1, -1, -1,  1, -1)
                                        )
                           )
          );
      }
      else if ( k == 3) // N = 20 * 2^e;
      {
          h = vertcat(nt2::ones(1,20,meta::as_<value_type>()),
                      nt2::horzcat(nt2::ones(19,1,meta::as_<value_type>()),
                              nt2::hankel(cons<value_type>(of_size(1, 19),-1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1),
                                          cons<value_type>(of_size(1, 19),1, -1, -1, 1, 1, -1, -1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1)
                                )
                        )
            );
      }
      //  Kronecker product construction.
      for (i_type i = 1; i <= e; ++i)
      {
        table<value_type> h1 =  nt2::vertcat(nt2::horzcat(h, h), nt2::horzcat(h, -h));
        h =  h1;  //ALIASING
      }
      out =  h;
      return out;
    }
  };
} }

// function H = hadamard(n,classname)
// %HADAMARD Hadamard matrix.
// %   HADAMARD(N) is a Hadamard matrix of order N, that is,
// %   a matrix H with elements 1 or -1 such that H'*H = N*EYE(N).
// %   An N-by-N Hadamard matrix with N > 2 exists only if REM(N,4)=0.
// %   This function handles only the cases where N, N/12 or N/20
// %   is a power of 2.
// %
// %   HADAMARD(N,CLASSNAME) produces a matrix of class CLASSNAME.
// %   CLASSNAME must be either 'single' or 'double' (the default).

// %   Nicholas J. Higham
// %   Copyright 1984-2005 The MathWorks, Inc.
// %   $Revision: 5.10.4.4 $  $Date: 2010/09/02 13:35:31 $

// %   Reference:
// %   S. W. Golomb and L. D. Baumert, The search for Hadamard matrices,
// %   Amer. Math. Monthly, 70 (1963) pp. 12-17.

// if nargin < 2, classname = 'double'; end

// [f,e] = log2([n n/12 n/20]);
// k = find(f==1/2 & e>0);
// if min(size(n)) > 1 || isempty(k)
//    error(message('MATLAB:hadamard:InvalidInput'));
// end
// e = e(k)-1;

// if k == 1        % N = 1 * 2^e;
//    H = ones(classname);

// elseif k == 2    % N = 12 * 2^e;
//    H = [ones(1,12,classname); ones(11,1,classname) ...
//         toeplitz([-1 -1 1 -1 -1 -1 1 1 1 -1 1],[-1 1 -1 1 1 1 -1 -1 -1 1 -1])];

// elseif k == 3    % N = 20 * 2^e;
//    H = [ones(1,20,classname); ones(19,1,classname)   ...
//         hankel([-1 -1 1 1 -1 -1 -1 -1 1 -1 1 -1 1 1 1 1 -1 -1 1], ...
//                [1 -1 -1 1 1 -1 -1 -1 -1 1 -1 1 -1 1 1 1 1 -1 -1])];
// end

// %  Kronecker product construction.
// for i = 1:e
//     H = [H  H
//          H -H]; %#ok
// end

#endif

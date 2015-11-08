//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PASCAL_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PASCAL_HPP_INCLUDED

#include <nt2/gallery/functions/pascal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/rot90.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/mod.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  //1
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pascal_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pascal_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::pascal_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , meta::as_<double>()
          , sizee
          );
    }
  };

  //1bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pascal_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pascal_
                                          , container::domain
                                          , A0 const
                                          , size_t
                                          , meta::as_<double>
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::pascal_, container::domain>
        ( boost::cref(a0)
          , size_t(0)
          , meta::as_<double>()
          , sizee
          );
    }
  };
  //2
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pascal_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pascal_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , T
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::pascal_, container::domain>
        ( boost::cref(a0)
          , boost::cref(a1)
          , T()
          , sizee
          );
    }
  };

  //2bis
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pascal_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::pascal_
                                          , container::domain
                                          , A0 const&
                                          , size_t
                                          , T
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             T  const&) const
    {
      _2D sizee;
      sizee[0] = sizee[1] = a0;
      return  boost::proto::
        make_expr<nt2::tag::pascal_, container::domain>
        ( boost::cref(a0)
          , size_t(0)
          , T()
          , sizee
          );
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  //     pascal  Chebyshev spectral differentiation matrix.
  //////////////////////////////////////////////////////////////////////////////

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::pascal_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    typedef typename A0::value_type                                      v_type;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      size_t k =  boost::proto::child_c<1>(in);
      out.resize(of_size(n, n));
      BOOST_AUTO_TPL(d, nt2::minusone(Two<v_type>()*nt2::mod(nt2::_(v_type(1), v_type(n)), Two<v_type>())));
      out =  nt2::from_diag(d);
      out(nt2::_, 1) = One<v_type>();
      // Generate pascal(n,1): the Pascal Cholesky factor (up to signs).
      for(size_t j=2; j <= n-1; ++j)
      {
        // BOOST_AUTO_TPL(i, nt2::_(j+1, n));
        // out(i, j =  out(i-1,j) - out(minusone(i),j-1);
        for(size_t i=j+1; i <= n; ++i)
        {
          out(i,j) = out(i-1,j) - out(i-1,j-1);
        }
      }
      k =  k%3;
      if (k == 0)
      {
        out = nt2::mtimes(out, nt2::trans(out));
      }
      else if (k == 2)
      {
        nt2::container::table<v_type, _2D> p = nt2::rot90(out, 3);//ALIASING
        out =  (nt2::is_even(n))? -p: p;
      }
      return out;
    }
  };

} }

#endif

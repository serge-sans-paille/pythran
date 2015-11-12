//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED

#include <nt2/linalg/functions/lu.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/potrf.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //CHOL Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      BOOST_ASSERT_MSG(is_gtz(a0), "Matrix must be positive definite");
      return  nt2::sqrt(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      BOOST_ASSERT_MSG(is_gtz(a0), "Matrix must be positive definite");
      return nt2::sqrt(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      BOOST_ASSERT_MSG(is_gtz(a0), "Matrix must be positive definite");
      return nt2::sqrt(a0);
    }
  };
  //============================================================================
  //Cholesky factorization
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::chol_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::chol_
                                    , N0, nt2::container::domain
                                      >
                              ))
                              ((node_<A1, nt2::tag::tie_
                                    , N1, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type child0;
    typedef typename child0::value_type                                  type_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - R = chol(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0 ,  A1& a1
              , boost::mpl::long_<1> const& , boost::mpl::long_<1> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_LAPACK_VERIFY(nt2::potrf(boost::proto::value(a),'U'));
      boost::proto::child_c<0>(a1) = nt2::triu(a);
    }

    //==========================================================================
    /// INTERNAL ONLY - L = chol(A,lower_/upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              ) const
    {
      eval( a0, a1, N0(), N1()
          , boost::proto::value(boost::proto::child_c<1>(a0))
          );
    }

    //==========================================================================
    /// INTERNAL ONLY - L = chol(A,lower_)
    BOOST_FORCEINLINE
    void eval( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              , nt2::policy<ext::lower_> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_LAPACK_VERIFY(nt2::potrf(boost::proto::value(a),'L'));
      boost::proto::child_c<0>(a1) = nt2::tril(a);
    }


    //==========================================================================
    /// INTERNAL ONLY - R = chol(A,upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<1> const&
              , nt2::policy<ext::upper_> const&
              ) const
    {
      eval(a0,a1,boost::mpl::long_<1>(),N1());
    }


    //==========================================================================
    /// INTERNAL ONLY - [R,P] = chol(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<1> const& , boost::mpl::long_<2> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2_la_int info = nt2::potrf(boost::proto::value(a),'U');
      BOOST_ASSERT_MSG(info >= 0, "invalid parameter in potrf call");
      if (info == 0)
        boost::proto::child_c<0>(a1) = nt2::triu(a);
      else
        boost::proto::child_c<0>(a1) = nt2::triu(a(nt2::_(1, info-1), nt2::_(1, info-1)));
      boost::proto::child_c<1>(a1) = info;
    }

    //==========================================================================
    /// INTERNAL ONLY - [R,P] = chol(A,lower_/upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              ) const
    {
      eval( a0, a1, N0(), N1()
          , boost::proto::value(boost::proto::child_c<1>(a0))
          );
    }

    //==========================================================================
    /// INTERNAL ONLY - L = chol(A, raw_,lower_/upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<3> const& , boost::mpl::long_<2> const&
              ) const
    {
      eval( a0, a1, N0(), N1()
          , boost::proto::value(boost::proto::child_c<1>(a0))
          , boost::proto::value(boost::proto::child_c<2>(a0))
          );
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,lower_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::lower_> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2_la_int info = nt2::potrf(boost::proto::value(a),'L');
      BOOST_ASSERT_MSG(info >= 0, "invalid parameter in potrf call");
      if (info == 0)
        boost::proto::child_c<0>(a1) = nt2::tril(a);
      else
        boost::proto::child_c<0>(a1) = nt2::tril(a(nt2::_(1, info-1), nt2::_(1, info-1)));
      boost::proto::child_c<1>(a1) = info;
    }

    //==========================================================================
    /// INTERNAL ONLY - [R,P] = chol(A,upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::upper_> const&
              ) const
    {
      eval(a0,a1,
           boost::mpl::long_<1>(),N1());
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,raw_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<2> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::raw_> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2_la_int info = nt2::potrf(boost::proto::value(a),'U');
      BOOST_ASSERT_MSG(info >= 0, "invalid parameter in potrf call");
      assign_swap( boost::proto::child_c<0>(a1), a);
      boost::proto::child_c<1>(a1) = info;
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,raw_,lower_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<3> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::raw_> const&
              , nt2::policy<ext::lower_> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2_la_int info = nt2::potrf(boost::proto::value(a),'L');
      BOOST_ASSERT_MSG(info >= 0, "invalid parameter in potrf call");
      assign_swap( boost::proto::child_c<0>(a1), a);
      boost::proto::child_c<1>(a1) =  info;
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,raw_,upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<3> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::raw_> const&
              , nt2::policy<ext::upper_> const&
              ) const
    {
      eval(a0, a1
          , boost::mpl::long_<2>(), N1(), nt2::policy<ext::raw_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,upper_,raw_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<3> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::upper_> const&
              , nt2::policy<ext::raw_> const&
              ) const
    {
      eval(a0, a1
          , boost::mpl::long_<2>(), N1(), nt2::policy<ext::raw_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [L,P] = chol(A,lower_,raw_)
    BOOST_FORCEINLINE
    void eval ( A0& a0 , A1& a1
              , boost::mpl::long_<3> const& , boost::mpl::long_<2> const&
              , nt2::policy<ext::lower_> const&
              , nt2::policy<ext::raw_> const&
              ) const
    {
      eval(a0, a1
          , boost::mpl::long_<3>(),  boost::mpl::long_<2>()
          , nt2::policy<ext::raw_>(), nt2::policy<ext::lower_>());
    }


  };
} }

#endif



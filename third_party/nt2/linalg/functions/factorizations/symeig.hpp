//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_SYMEIG_HPP_INCLUDED

#include <nt2/include/functions/symeig.hpp>
#include <boost/dispatch/attributes.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/hsev_w.hpp>
#include <nt2/include/functions/hsev_wu.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/linalg/options.hpp>
#include <nt2/linalg/details/utility/lapack_verify.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  //SYMEIG Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return real(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return real(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename nt2::meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&, const A2&) const
    {
      return real(a0);
    }
  };


  //============================================================================
  //SYMEIG
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::symeig_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::symeig_
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
    typedef typename nt2::meta::as_real<type_t>::type                   rtype_t;
    typedef nt2::memory::container<tag::table_,  type_t, nt2::_2D>   o_semantic;
    typedef nt2::memory::container<tag::table_, rtype_t, nt2::_2D>   r_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }
  private:
    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A)
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>()
             , nt2::policy<ext::upper_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A, matrix_/vector_/upper_/lower_/raw_)
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
                , boost::mpl::long_<2> const&
                , boost::mpl::long_<1> const&
                ) const
    {
      eval1_2(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));
    }

    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                    , nt2::policy<ext::vector_>
                   ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>()
             , nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                    , nt2::policy<ext::raw_>
                   ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>()
             , nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                    , nt2::policy<ext::matrix_>
                   ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                    , nt2::policy<ext::upper_>
                   ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>()
             , nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                    , nt2::policy<ext::lower_>
                   ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>()
             , nt2::policy<ext::lower_>());
    }


    //==========================================================================
    /// INTERNAL ONLY - W = SYMEIG(A, matrix_/vector_, upper_/lower_)
    // returns eigenvalues as a vector
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<1> const&
              ) const
    {
      eval1_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0))
             , boost::proto::value(boost::proto::child_c<2>(a0))
             );
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 , nt2::policy<ext::lower_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (r_semantic, w
                           , boost::proto::child_c<0>(a1));
      w.resize(nt2::of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_w( boost::proto::value(a)
                                   , boost::proto::value(w)
                                   , 'L'));
      assign_swap(boost::proto::child_c<0>(a1), w);
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_> const &
                 , nt2::policy<ext::upper_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      NT2_AS_TERMINAL_OUT  (r_semantic, w
                           , boost::proto::child_c<0>(a1));
      w.resize(nt2::of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_w( boost::proto::value(a)
                                   , boost::proto::value(w)
                                   , 'U'));
      assign_swap(boost::proto::child_c<0>(a1), w);
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 , nt2::policy<ext::lower_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      nt2::container::table<rtype_t> w(of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_w( boost::proto::value(a)
                                   , boost::proto::value(w)
                                   , 'L'));
      boost::proto::child_c<0>(a1) = from_diag(w);
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_> const &
                 , nt2::policy<ext::upper_> const &
                 ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, a
                           , boost::proto::child_c<0>(a0), work);
      nt2::container::table<rtype_t>  w(of_size(height(a), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_w( boost::proto::value(a)
                                   , boost::proto::value(w)
                                   , 'U'));
      boost::proto::child_c<0>(a1) = from_diag(w);
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 , nt2::policy<ext::upper_>
                 ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>(), nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval1_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 , nt2::policy<ext::lower_>
                 ) const
    {
      eval1_3(a0, a1
             , nt2::policy<ext::vector_>(), nt2::policy<ext::lower_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [W, V]= SYMEIG(A, matrix_/vector_/upper_/lower_/raw_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_2(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));

    }

    //==========================================================================
    /// INTERNAL ONLY - [W, U]= SYMEIG(A)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_3(a0, a1, nt2::matrix_, nt2::upper_);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      nt2::container::table<rtype_t> w(of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'U'));
      boost::proto::child_c<0>(a1) = from_diag(w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, w, boost::proto::child_c<0>(a1));
      w.resize(nt2::of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'U'));
      assign_swap(boost::proto::child_c<0>(a1), w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 ) const
    {
      eval2_2(a0, a1, nt2::policy<ext::vector_>());
    }

    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::lower_>
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::lower_>());
    }


    BOOST_FORCEINLINE
    void eval2_2 ( A0& a0, A1& a1
                 , nt2::policy<ext::upper_>
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>()
             , nt2::policy<ext::upper_>());
    }

    //==========================================================================
    /// INTERNAL ONLY - [W, V]= SYMEIG(A, matrix_/vector_, lower_/upper_)
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<3> const&
              , boost::mpl::long_<2> const&
              ) const
    {
      eval2_3( a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0))
             , boost::proto::value(boost::proto::child_c<2>(a0))
             );

    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_>
                 , nt2::policy<ext::lower_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      nt2::container::table<rtype_t> w(of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'L'));
      boost::proto::child_c<0>(a1) = from_diag(w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::matrix_>
                 , nt2::policy<ext::upper_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      nt2::container::table<rtype_t> w(of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'U'));
      boost::proto::child_c<0>(a1) = from_diag(w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_>
                 , nt2::policy<ext::upper_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, w
                           , boost::proto::child_c<0>(a1));
      w.resize(of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'U'));
      assign_swap(boost::proto::child_c<0>(a1), w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 , nt2::policy<ext::upper_>
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::vector_>(), nt2::policy<ext::upper_>());
    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::raw_>
                 , nt2::policy<ext::lower_>
                 ) const
    {
      eval2_3(a0, a1
             , nt2::policy<ext::vector_>(), nt2::policy<ext::lower_>());
    }

    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                 , nt2::policy<ext::vector_>
                 , nt2::policy<ext::lower_>
                 ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, u
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT  (r_semantic, w
                           , boost::proto::child_c<0>(a1));
      w.resize(of_size(height(u), 1));
      NT2_LAPACK_VERIFY(nt2::hsev_wu( boost::proto::value(u)
                                    , boost::proto::value(w)
                                    , 'L'));
      assign_swap(boost::proto::child_c<0>(a1), w);
      assign_swap(boost::proto::child_c<1>(a1), u);
    }

#define MORE_OPTIONS(PARAM, OPT1, OPT2)        \
    BOOST_FORCEINLINE                          \
      void eval##PARAM( A0& a0, A1& a1         \
                      , nt2::policy<ext::OPT1> \
                      , nt2::policy<ext::OPT2> \
                      ) const                  \
    {                                          \
      eval##PARAM(a0, a1                       \
                 , nt2::policy<ext::OPT2>()    \
                 , nt2::policy<ext::OPT1>()    \
                 );                            \
    }                                          \
    /**/

    MORE_OPTIONS(2_3, lower_, raw_)
    MORE_OPTIONS(2_3, upper_, raw_)
    MORE_OPTIONS(2_3, lower_, vector_)
    MORE_OPTIONS(2_3, upper_, vector_)
    MORE_OPTIONS(2_3, lower_, matrix_)
    MORE_OPTIONS(2_3, upper_, matrix_)
    MORE_OPTIONS(1_3, lower_, vector_)
    MORE_OPTIONS(1_3, upper_, vector_)
    MORE_OPTIONS(1_3, lower_, raw_)
    MORE_OPTIONS(1_3, upper_, raw_)
    MORE_OPTIONS(1_3, lower_, matrix_)
    MORE_OPTIONS(1_3, upper_, matrix_)

#undef MORE_OPTIONS
  };
} }

#endif



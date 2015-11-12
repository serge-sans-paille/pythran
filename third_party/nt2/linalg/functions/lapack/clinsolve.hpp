//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_CLINSOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_CLINSOLVE_HPP_INCLUDED


#include <nt2/linalg/functions/clinsolve.hpp>

#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/gelsy.hpp>
#include <nt2/include/functions/gesv.hpp>
#include <nt2/include/functions/gbsv.hpp>
#include <nt2/include/functions/posv.hpp>
#include <nt2/include/functions/sysv.hpp>
#include <nt2/include/functions/lange.hpp>
#include <nt2/include/functions/lansy.hpp>
#include <nt2/include/functions/langb.hpp>
#include <nt2/include/functions/gecon.hpp>
#include <nt2/include/functions/sycon.hpp>
#include <nt2/include/functions/pocon.hpp>
#include <nt2/include/functions/gbcon.hpp>
#include <nt2/include/functions/trsolve.hpp>

#include <nt2/include/functions/tie.hpp>

#include <nt2/linalg/options.hpp>
#include <nt2/linalg/functions/details/eval_linsolve.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/core/container/table/table.hpp>



namespace nt2 { namespace ext
{
  //============================================================================
  // LINSOLVE classic
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::clinsolve_, tag::cpu_
                            , (A0)(A1)(A2)(N2)
                            , ((ast_<A0, nt2::container::domain>))   // A
                              ((ast_<A1, nt2::container::domain>))   // B
                              ((node_<A2, nt2::tag::tie_             // X-R
                                    , N2, nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef void  result_type;
    typedef typename A0::value_type ctype_t;
    typedef typename nt2::meta::as_real<ctype_t>::type   type_t;
    typedef typename meta::option<typename A0::proto_child0::settings_type,nt2::tag::shape_>::type shape;
    typedef nt2::memory::container<tag::table_, ctype_t, nt2::settings(nt2::_2D)> desired_semantic;
    typedef nt2::container::table<ctype_t>  entry_type;
    typedef nt2::container::table<ctype_t,shape>  matrix_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0, A1 const& a1, A2 const& a2  ) const
    {
      nt2::container::table<nt2_la_int> piv;
      eval(a0,a1,a2,piv,N2(),shape());
    }

    //==========================================================================
    /// INTERNAL ONLY - Shape analysis

    /// INTERNAL ONLY - X = LINSOLVE(A,B) - rectangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&, nt2::rectangular_ const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      entry_type entry(a0);
      eval_param( a0, a1, b);

      if (issquare(entry)) nt2::gesv(boost::proto::value(entry)
                           ,boost::proto::value(piv), boost::proto::value(b));

      else {
        nt2_la_int n = nt2::width(a0);
        piv = nt2::zeros(n,1, nt2::meta::as_<nt2_la_int>());
        nt2::gelsy( boost::proto::value(entry) ,boost::proto::value(piv)
                , boost::proto::value(b) );
      }
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& /*piv*/
              , boost::mpl::long_<1> const&, nt2::positive_definite_ const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      nt2::posv(boost::proto::value(entry), boost::proto::value(b));
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&, nt2::symmetric_ const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      nt2::sysv( boost::proto::value(entry),boost::proto::value(piv)
              , boost::proto::value(b));
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) - band shape
    template<int U, int L>
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<1> const&, nt2::band_diagonal_<U,L> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      nt2::gbsv( boost::proto::value(entry),boost::proto::value(piv)
              , boost::proto::value(b));
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) -- upper triangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>&
              , boost::mpl::long_<1> const&, nt2::upper_triangular_ const&
              ) const
    {
      boost::proto::child_c<0>(a2) = nt2::trsolve(a0,a1);
    }

    //==========================================================================
    /// INTERNAL ONLY - X = LINSOLVE(A,B) -- lower triangular shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>&
              , boost::mpl::long_<1> const&, nt2::lower_triangular_ const&
              ) const
    {
      boost::proto::child_c<0>(a2) = nt2::trsolve(a0,a1);
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- Rectangular shape
    BOOST_FORCEINLINE
    void eval( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      eval_param( entry, a1, boost::proto::child_c<0>(a2));

      if (issquare(entry))
      {
        nt2::gesv( boost::proto::value(entry), boost::proto::value(piv)
               , boost::proto::value(b) );
        char norm = '1';

        type_t anorm = nt2::lange(boost::proto::value(entry),norm);
        boost::proto::child_c<1>(a2) = nt2::gecon(boost::proto::value(entry),norm,anorm);
      }
      else
      {
        nt2_la_int rank;
        nt2_la_int n = nt2::width(entry);
        piv = nt2::zeros(n,1, nt2::meta::as_<nt2_la_int>());

        nt2::gelsy( boost::proto::value(entry), boost::proto::value(piv)
                , boost::proto::value(b), rank);
        boost::proto::child_c<1>(a2) = static_cast<type_t>(rank);
      }
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- symmetric shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&, nt2::symmetric_ const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);
      char norm = '1';

      piv = nt2::zeros(entry.leading_size(), 1, nt2::meta::as_<nt2_la_int>() );

      typedef typename meta::hierarchy_of<nt2::symmetric_>::stripped h_;

      type_t anorm = nt2::lange(boost::proto::value(entry), norm, h_());

      nt2::sysv( boost::proto::value(entry),boost::proto::value(piv)
              , boost::proto::value(b));
      boost::proto::child_c<1>(a2) = nt2::sycon( boost::proto::value(entry)
                                               , boost::proto::value(piv) ,anorm);
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- positive definite shape
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& /*piv*/
              , boost::mpl::long_<2> const&, nt2::positive_definite_ const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      char norm = '1';
      typedef typename meta::hierarchy_of<nt2::symmetric_>::stripped h_;
      type_t anorm = nt2::lange(boost::proto::value(entry) ,norm, h_());
      nt2::posv(boost::proto::value(entry), boost::proto::value(b));
      boost::proto::child_c<1>(a2) = nt2::pocon(boost::proto::value(entry),anorm);
    }

    //==========================================================================
    /// INTERNAL ONLY - [X,R] = LINSOLVE(A,B) -- general band shape
    template<int U, int L>
    BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , boost::mpl::long_<2> const&, nt2::band_diagonal_<U,L> const&
              ) const
    {
      NT2_AS_TERMINAL_INOUT(desired_semantic,b,a1,boost::proto::child_c<0>(a2) );
      matrix_type entry(a0);

      char norm = '1';

      type_t anorm = nt2::langb(boost::proto::value(entry),norm);
      nt2::gbsv( boost::proto::value(entry), boost::proto::value(piv)
              , boost::proto::value(b));
      boost::proto::child_c<1>(a2) = nt2::gbcon( boost::proto::value(entry)
                                               , boost::proto::value(piv),anorm);

    }

    /// INTERNAL ONLY - X = LINSOLVE(A,B) - default case
    template<typename N, typename sh> BOOST_FORCEINLINE
    void eval ( A0 const& a0, A1 const& a1 , A2 const& a2, nt2::container::table<nt2_la_int>& piv
              , N const&, sh const&
              ) const
    {
      eval(a0,a1,a2,piv,boost::mpl::long_<1>() ,nt2::rectangular_());
    }

  };
} }


#endif

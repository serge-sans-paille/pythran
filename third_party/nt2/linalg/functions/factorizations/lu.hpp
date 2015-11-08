//==============================================================================
//         Copyright 2014 - Jean-Thierry Lapresté
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LU_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_LU_HPP_INCLUDED

#include <nt2/linalg/functions/lu.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/getrf.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/error/warning.hpp>
#include <nt2/linalg/options.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <algorithm>

///Utilitary macro
/// INTERNAL ONLY undefined at end of file
#define CHECK_LAPACK_LU_SUCCESS(info)                        \
  {                                                          \
    nt2_la_int info_ = info;                                 \
    boost::dispatch::ignore_unused(info_);                   \
    NT2_WARNING(info_ <= 0                                   \
               , "LU factorization has been completed, "     \
                "but input matrix is exactly singular. "     \
                "Division by zero will occur if it is used " \
                "to solve a system of equations."            \
               );                                            \
  }                                                          \
  /**/

namespace nt2 { namespace ext
{
  //============================================================================
  //lu Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  //lu Scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&) const
    {
      return a0;
    }
  };

  //============================================================================
  //lu
  //============================================================================
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lu_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_ < A0, nt2::tag::lu_
                                      , N0, nt2::container::domain
                                      >
                              ))
                              ((node_ < A1, nt2::tag::tie_
                                      , N1, nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef void                                                        result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::value_type     child0;
    typedef typename child0::value_type                                      type_t;
    typedef typename meta::as_real<type_t>::type                            rtype_t;
    typedef nt2::memory::container<tag::table_, type_t, nt2::_2D>        o_semantic;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      eval(a0, a1, N0(), N1());
    }
  private:
    /// INTERNAL ONLY - y =  lu(a)
    /// y is the direct lapack return from ?getrf and permutation is lost
    /// only call for which raw_ is the default
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // # inputs
              , boost::mpl::long_<1> const& // # outputs
              ) const
    {
      //1_1 means 1 input 1 output
      eval1_1(a0, a1
             , nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY - y =  lu(a, raw_)
    /// y is the direct lapack return from ?getrf, and permutation is lost
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<1> const& // # outputs
              ) const
    {
      // 1_2 means 1 input 2 outputs
      eval1_2(a0, a1
             , nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY - [y, ls] =  lu(a, raw_)
    /// y is the direct lapack return from ?getrf
    /// permutation ls is in lapack swap lines indices form
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<2> const& // # outputs
              ) const
    {
      // 2_2 means 2 input 2 outputs
      eval1_2(a0, a1
             , nt2::policy<ext::raw_>());
    }

    /// INTERNAL ONLY - [pl, u] =  lu(a)
    /// pl is a permuted lower triangular matrix
    //  u  is an upper triangular matrix
    /// pl*u ==  a
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // # inputs
              , boost::mpl::long_<2> const& // # outputs
              ) const
    {
      // 1_2 means 1 input 2 outputs
      eval1_2(a0, a1
             , nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY - [l, u, p] =  lu(a)
    /// pl is a permuted lower triangular matrix
    //  u  is an upper triangular matrix
    /// pl*u ==  a
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<1> const& // # inputs
              , boost::mpl::long_<3> const& // # outputs
              ) const
    {
      // 2_3 means 2 input 3 outputs
      eval2_3(a0, a1
             , nt2::policy<ext::matrix_>());
    }

    /// INTERNAL ONLY - [l, u, p] =  lu(a, vector_/matrix_)
    /// pl is a permuted lower triangular matrix
    //  u  is an upper triangular matrix
    /// pl*u ==  a
    BOOST_FORCEINLINE
    void eval ( A0& a0, A1& a1
              , boost::mpl::long_<2> const& // # inputs
              , boost::mpl::long_<3> const& // # outputs
              ) const
    {
      // 2_3 means 2 input 3 outputs
      eval2_3(a0, a1
             , boost::proto::value(boost::proto::child_c<1>(a0)));
    }



    ///////////////////////////////////////////////////////////////////////////////
    // evali_j bunch
    ///////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 1i 1o raw_
    BOOST_FORCEINLINE
    void eval1_1 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , lu, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      nt2::container::table<nt2_la_int> ls(of_size(dim(lu), 1));
      CHECK_LAPACK_LU_SUCCESS((nt2::getrf( boost::proto::value(lu)
                                         , boost::proto::value(ls))));
      assign_swap(boost::proto::child_c<0>(a1), lu);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 1i 2o raw_
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                   , const nt2::policy<ext::raw_>&
                   ) const
    {
      typedef nt2::memory::container<tag::table_, nt2_la_int, nt2::_2D> i_semantic;
      NT2_AS_TERMINAL_INOUT(o_semantic
                           , lu, boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_OUT(i_semantic, ls
                         , boost::proto::child_c<1>(a1));

      ls.resize(of_size(dim(lu), 1));
      CHECK_LAPACK_LU_SUCCESS(nt2::getrf( boost::proto::value(lu)
                                        , boost::proto::value(ls)));
      assign_swap(boost::proto::child_c<0>(a1), lu);
      assign_swap(boost::proto::child_c<1>(a1), ls);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 1i 2o T other from raw_
    template < class T >
    BOOST_FORCEINLINE
    void eval1_2 ( A0& a0, A1& a1
                   , const T &
                   ) const
    {
      NT2_AS_TERMINAL_INOUT(o_semantic, lu
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      std::size_t d  = dim(lu);
      nt2::container::table<nt2_la_int> ls(of_size(d, 1));
      CHECK_LAPACK_LU_SUCCESS(nt2::getrf( boost::proto::value(lu)
                                        , boost::proto::value(ls)));
      nt2::container::table<nt2_la_int> ip;
      construct_ip(ls, ip, height(lu));
      boost::proto::child_c<0>(a1) = nt2::tri1l(lu(nt2::_, nt2::_(1, d) ) )(ip, nt2::_);
      boost::proto::child_c<1>(a1) = nt2::triu(lu( nt2::_(1, d), nt2::_) );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::vector_>&
                   ) const
    {
      typedef typename boost::proto::result_of::child_c<A1&,2>::value_type     child;
      typedef typename child::value_type                                     itype_t;
      NT2_AS_TERMINAL_INOUT(o_semantic, lu
                           , boost::proto::child_c<0>(a0)
                           , boost::proto::child_c<1>(a1));
      std::size_t d  = dim(lu);
      nt2::container::table<nt2_la_int> ls(of_size(d, 1));
      CHECK_LAPACK_LU_SUCCESS(nt2::getrf( boost::proto::value(lu)
                                        , boost::proto::value(ls)));
      nt2::container::table<itype_t> ip;
      construct_ip(ls, ip, height(lu));
      boost::proto::child_c<0>(a1) = nt2::tri1l(lu(nt2::_, nt2::_(1, d) ) );
      boost::proto::child_c<1>(a1) = nt2::triu(lu( nt2::_(1, d), nt2::_) );
      inverse(ip);
      assign_swap(boost::proto::child_c<2>(a1), ip);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY: 2i 3o
    BOOST_FORCEINLINE
    void eval2_3 ( A0& a0, A1& a1
                   , const nt2::policy<ext::matrix_>&
                   ) const
    {
      nt2::container::table<type_t> work;
      NT2_AS_TERMINAL_INOUT(o_semantic, lu
                           , boost::proto::child_c<0>(a0), work);
      std::size_t d  = dim(lu);
      nt2::container::table<nt2_la_int> ls(of_size(d, 1)), ip;
      CHECK_LAPACK_LU_SUCCESS(nt2::getrf( boost::proto::value(lu)
                                        , boost::proto::value(ls)));
      construct_ip(ls, ip, height(lu));
      boost::proto::child_c<1>(a1) = nt2::triu(lu( nt2::_(1, d), nt2::_) );
      boost::proto::child_c<0>(a1) = nt2::tri1l(lu(nt2::_, nt2::_(1, d) ) );
      boost::proto::child_c<2>(a1) = eye(height(lu), nt2::meta::as_<rtype_t>())(nt2::_, ip);
    }

    ////////////////////////////////////////////////////////////////////////////
    // some utilitaries
    ////////////////////////////////////////////////////////////////////////////
    /// INTERNAL ONLY - Size of L/U
    template<typename W>
    BOOST_FORCEINLINE std::size_t dim(W const& work) const
    {
      return nt2::min(nt2::height(work),nt2::width(work));
    }

    /// INTERNAL ONLY
    /// construct permutation vector from lapack swap vector
    template < class T1, class T2>
    BOOST_FORCEINLINE
    void construct_ip(T1& ls, T2& ips, size_t h) const
    {
      std::size_t d = nt2::numel(ls);
      ips = nt2::_(nt2_la_int(1), nt2_la_int(h));
      for(std::size_t i = d; i >= 1; --i)
      {
        std::swap(ips(i), ips(ls(i)));
      }
    }

    template < class T1>
    BOOST_FORCEINLINE
    void inverse(T1& ip) const
    {
      T1 inv(of_size(1, numel(ip)));
      inv(ip) =  nt2::_(nt2_la_int(1), nt2_la_int(numel(ip)));
      assign_swap(ip, inv);
    }
  };

} }

#undef CHECK_LAPACK_LU_SUCCESS

#endif

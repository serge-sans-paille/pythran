//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CTRANSPOSE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CTRANSPOSE_HPP_INCLUDED

#include <nt2/core/functions/ctranspose.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>

namespace nt2 { namespace ext
{
  // ctranspose scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctranspose_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), conj(a0))
  };

  // ctranspose optimizations
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctranspose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::transpose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), conj(boost::proto::child_c<0>(a0)))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctranspose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::ctranspose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), boost::proto::child_c<0>(a0))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ctranspose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::conj_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), transpose(boost::proto::child_c<0>(a0)))
  };

  // ctranspose vector
  template<class A0>
  struct ctranspose_row_vector
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), conj(colvect(a0)))
  };
  NT2_REGISTER_DISPATCH_TO_IF( nt2::tag::ctranspose_, tag::cpu_
                             , (A0)
                             , (nt2::details::is_definitely_row_vector<typename A0::extent_type>)
                             , ((ast_<A0, nt2::container::domain>))
                             , nt2::ext::ctranspose_row_vector<A0>
                             );

  template<class A0>
  struct ctranspose_col_vector
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), conj(rowvect(a0)))
  };
  NT2_REGISTER_DISPATCH_TO_IF( nt2::tag::ctranspose_, tag::cpu_
                             , (A0)
                             , (nt2::details::is_definitely_col_vector<typename A0::extent_type>)
                             , ((ast_<A0, nt2::container::domain>))
                             , nt2::ext::ctranspose_col_vector<A0>
                             );

  // ctranspose implementation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_<A0, nt2::tag::ctranspose_, boost::mpl::long_<1>, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              ((target_< unspecified_<Data> >))
                            )
  {
    typedef typename Data::type result_type;
    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      return conj( run( transpose( boost::proto::child_c<0>(a0) ), p, t ) );
    }
  };
} }

#endif

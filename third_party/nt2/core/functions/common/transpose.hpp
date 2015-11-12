//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRANSPOSE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRANSPOSE_HPP_INCLUDED

#include <nt2/core/functions/transpose.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <boost/utility/swap.hpp>

namespace nt2 { namespace ext
{
  // transpose scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transpose_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), a0)
  };

  // transpose optimizations
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transpose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::transpose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), boost::proto::child_c<0>(a0))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transpose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::ctranspose_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), conj(boost::proto::child_c<0>(a0)))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transpose_, tag::cpu_
                            , (A0)
                            , ((node_<A0, nt2::tag::conj_, boost::mpl::long_<1>, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), ctranspose(boost::proto::child_c<0>(a0)))
  };

  // transpose vector
  template<class A0>
  struct transpose_row_vector
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), colvect(a0))
  };
  NT2_REGISTER_DISPATCH_TO_IF( nt2::tag::transpose_, tag::cpu_
                             , (A0)
                             , (nt2::details::is_definitely_row_vector<typename A0::extent_type>)
                             , ((ast_<A0, nt2::container::domain>))
                             , nt2::ext::transpose_row_vector<A0>
                             );

  template<class A0>
  struct transpose_col_vector
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0), rowvect(a0))
  };
  NT2_REGISTER_DISPATCH_TO_IF( nt2::tag::transpose_, tag::cpu_
                             , (A0)
                             , (nt2::details::is_definitely_col_vector<typename A0::extent_type>)
                             , ((ast_<A0, nt2::container::domain>))
                             , nt2::ext::transpose_col_vector<A0>
                             );

  // transpose implementation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::transpose_
                                      , boost::mpl::long_<1>
                                      , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type           result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typedef typename meta::as_index<result_type>::type                i_t;
      typedef typename result_of::as_subscript<_2D,i_t>::type           sub_t;

      _2D sz(boost::proto::child_c<0>(a0).extent());

      sub_t pos = as_subscript( a0.extent(), nt2::enumerate<i_t>(p) );
      boost::swap(pos[0],pos[1]);

      return nt2::run ( boost::proto::child_c<0>(a0)
                      , as_index(sz, pos)
                      , t
                      );
    }
  };
} }

#endif

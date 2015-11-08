//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_MTIMES_HPP_INCLUDED

#include <nt2/linalg/functions/mtimes.hpp>
#include <nt2/linalg/details/blas/mm.hpp>
#include <nt2/core/functions/transpose.hpp>
#include <nt2/core/functions/ctranspose.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/value.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/alias.hpp>
#include <nt2/core/container/dsl/as_terminal.hpp>
#include <nt2/core/container/dsl/assign_swap.hpp>
#include <nt2/sdk/memory/forward/container.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <boost/proto/traits.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace tag
{
  struct blas_normal_
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'N';
    }
  };

  struct blas_transpose_
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'T';
    }
  };

  struct blas_ctranspose_
  {
    BOOST_FORCEINLINE static char call()
    {
      return 'C';
    }
  };
} }

namespace nt2 { namespace ext
{
  template<class Domain, int N,class Expr>
  struct size_of<tag::mtimes_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;

    typedef typename boost::proto::result_of::value< typename boost::proto::result_of::child_c<Expr&, 4>::value_type >::value_type trs0;
    typedef typename boost::proto::result_of::value< typename boost::proto::result_of::child_c<Expr&, 5>::value_type >::value_type trs1;

    typedef typename child0::extent_type sz0;
    typedef typename child1::extent_type sz1;

    static const std::size_t sz0_0 = boost::is_same<trs0, tag::blas_normal_>::value ? 0 : 1;
    static const std::size_t sz0_1 = boost::is_same<trs0, tag::blas_normal_>::value ? 1 : 0;
    static const std::size_t sz1_0 = boost::is_same<trs1, tag::blas_normal_>::value ? 0 : 1;
    static const std::size_t sz1_1 = boost::is_same<trs1, tag::blas_normal_>::value ? 1 : 0;

    typedef of_size_< mpl_value< typename boost::fusion::result_of::at_c<sz0, sz0_0>::type>::value
                    , mpl_value< typename boost::fusion::result_of::at_c<sz1, sz1_1>::type>::value
                    >  result_type;

    result_type operator()(Expr& e) const
    {
      sz0 const& size0 = boost::proto::child_c<0>(e).extent();
      sz1 const& size1 = boost::proto::child_c<1>(e).extent();

      BOOST_ASSERT_MSG( ndims(size0) <= 2 && ndims(size1) <= 2
                      , "Inputs must be 2-D, or at least one input must be scalar"
                      );

      BOOST_ASSERT_MSG( boost::fusion::at_c<sz0_1>(size0) == boost::fusion::at_c<sz1_0>(size1)
                      , "Inner dimensions must agree"
                      );

      return result_type( boost::fusion::at_c<sz0_0>(size0)
                        , boost::fusion::at_c<sz1_1>(size1)
                        );
    }
  };

  template<class Domain, int N,class Expr>
  struct value_type<tag::mtimes_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type child0;
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;
    typedef typename meta::call<tag::multiplies_(typename child0::value_type, typename child1::value_type)>::type type;
  };
} }

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef typename meta::call<tag::multiplies_(typename A0::value_type, typename A1::value_type)>::type T;
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      mtimes(a0, a1, Zero<T>(), One<T>(), tag::blas_normal_(), tag::blas_normal_())
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename meta::call<tag::multiplies_(typename A0::value_type, typename A1::value_type)>::type T;
    BOOST_DISPATCH_RETURNS(3, (A0 const& a0, A1 const& a1, A2 const& a2),
      mtimes(a0, a1, a2, One<T>(), tag::blas_normal_(), tag::blas_normal_())
    )
  };

  // Recognize scalar/matrix, matrix/scalar and scalar/scalar
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(T1)(N1)
                            , (scalar_< unspecified_<A0> >)
                              ((expr_< generic_< unspecified_<A1> >, T1, N1 >))
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(T0)(N0)(A1)
                            , ((expr_< generic_< unspecified_<A0> >, T0, N0 >))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef typename meta::call<tag::multiplies_(A0 const&, A1 const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return nt2::multiplies(a0, a1);
    }
  };

  // Recognize transpose
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const&, A5 const& a5),
      mtimes(boost::proto::child_c<0>(a0), a1, a2, a3, tag::blas_transpose_(), a5)
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((ast_< A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const&),
      mtimes(a0, boost::proto::child_c<0>(a1), a2, a3, a4, tag::blas_transpose_())
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((node_< A0, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((node_< A1, nt2::tag::transpose_, boost::mpl::long_<1> , nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const&, A5 const&),
      mtimes(boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1), a2, a3, tag::blas_transpose_(), tag::blas_transpose_())
    )
  };

  // Recognize ctranspose
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const&, A5 const& a5),
      mtimes(boost::proto::child_c<0>(a0), a1, a2, a3, tag::blas_ctranspose_(), a5)
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((ast_< A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const&),
      mtimes(a0, boost::proto::child_c<0>(a1), a2, a3, a4, tag::blas_ctranspose_())
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mtimes_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((node_< A0, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              ((node_< A1, nt2::tag::ctranspose_, boost::mpl::long_<1> , nt2::container::domain>))
                              (scalar_< unspecified_<A2> >)
                              (scalar_< unspecified_<A3> >)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(6, (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const& a4, A5 const& a5), (A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3, A4 const&, A5 const&),
      mtimes(boost::proto::child_c<0>(a0), boost::proto::child_c<0>(a1), a2, a3, tag::blas_ctranspose_(), tag::blas_ctranspose_())
    )
  };


  // Recognize alpha
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<6> , nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      mtimes(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), boost::proto::child_c<2>(a1), a0 * boost::proto::value(boost::proto::child_c<3>(a1)), boost::proto::child_c<4>(a1), boost::proto::child_c<5>(a1))
    )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::multiplies_, tag::cpu_
                            , (A0)(A1)
                            , ((node_< A0, nt2::tag::mtimes_, boost::mpl::long_<6> , nt2::container::domain>))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
      mtimes(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), boost::proto::child_c<2>(a0), a1 * boost::proto::value(boost::proto::child_c<3>(a0)), boost::proto::child_c<4>(a0), boost::proto::child_c<5>(a0))
    )
  };

  // run_assign
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_< A1, nt2::tag::mtimes_, boost::mpl::long_<6> , nt2::container::domain>))
                            )
  {
    typedef A0& result_type;

    result_type operator()(A0& a0, A1& a1) const
    {
      using boost::fusion::at_c;
      typedef typename A1::value_type value_type;

      if(at_c<1>(boost::proto::child_c<0>(a1).extent()) == 0u)
      {
        a0 = zeros(a1.extent(), meta::as_<value_type>());
        return a0;
      }

      typedef nt2::memory::container<tag::table_, value_type, nt2::_2D> desired_semantic;
      NT2_AS_TERMINAL_IN(desired_semantic, child0, boost::proto::child_c<0>(a1));
      NT2_AS_TERMINAL_IN(desired_semantic, child1, boost::proto::child_c<1>(a1));
      NT2_AS_TERMINAL_OUT(desired_semantic, result, a0);

      value_type alpha = boost::proto::value(boost::proto::child_c<3>(a1));
      value_type beta = boost::proto::value(boost::proto::child_c<2>(a1));

      char transA = A1::proto_child4::proto_child0::call();
      char transB = A1::proto_child5::proto_child0::call();

      nt2_la_int m = transA == 'N' ? nt2_la_int(at_c<0>(child0.extent())) : nt2_la_int(at_c<1>(child0.extent()));
      nt2_la_int n = transB == 'N' ? nt2_la_int(at_c<1>(child1.extent())) : nt2_la_int(at_c<0>(child1.extent()));
      nt2_la_int k = transA == 'N' ? nt2_la_int(at_c<1>(child0.extent())) : nt2_la_int(at_c<0>(child0.extent()));
      nt2_la_int lda = at_c<0>(child0.extent());
      nt2_la_int ldb = at_c<0>(child1.extent());
      nt2_la_int ldc = at_c<0>(a1.extent());

      typedef typename container::as_terminal<desired_semantic>::type dummy_type;
      typedef typename container::as_view_impl<dummy_type>::type view_type;

      dummy_type dummy;
      view_type result_view;
      bool swap = (void*)&result != (void*)&a0;

      if( swap || ( container::alias(result, child0) || container::alias(result, child1) ) )
      {
        // overlapping of input and output data
        // so we provide dummy space and put it back in result later
        dummy.resize(a1.extent());
        result_view.reset(dummy);
        swap = true;
      }
      else
      {
        result.resize(a1.extent());
        result_view.reset(result);
      }

      nt2::details::
      gemm( &transA, &transB
          , &m, &n, &k
          , &alpha
          , child0.raw(), &lda
          , child1.raw(), &ldb
          , &beta
          , result_view.raw(), &ldc
          );

      if(swap)
        container::assign_swap(a0, dummy);
      return a0;
    }
  };

} }

#endif


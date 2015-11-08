///==============================================================================
///         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
///         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
///         Copyright 2011 - 2012   MetaScale SAS
///
///          Distributed under the Boost Software License, Version 1.0.
///                 See accompanying file LICENSE.txt or copy at
///                     http:///www.boost.org/LICENSE_1_0.txt
///==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_CONSTRUCT_HPP_INCLUDED

#include <nt2/core/functions/construct.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/sdk/memory/copy.hpp>
#include <boost/simd/memory/iterator_category.hpp>

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::iterator_;

  /// INTERNAL ONLY
  /// Construct a terminal from a size
  ///  * Perform a resize on the table's container
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename A0::extent_type    extent_type;
    typedef typename A0::container_type container_type;
    typedef void                        result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      boost::proto::value(a0).resize(a1);
    }
  };

  /// INTERNAL ONLY
  /// Construct a terminal from a size and some unspecified allocator
  ///  * Construct a proper container from size and allocator
  ///  * Swap with the table's container
  ///
  /// This is done even if swap sounds bad with automatic storage table.
  /// Good news are that automatic_  table usually don't require allocators ;)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              (fusion_sequence_<A1>)
                              (unspecified_<A2>)
                            )
  {
    typedef typename A0::extent_type    extent_type;
    typedef typename A0::allocator_type allocator_type;
    typedef typename A0::container_type container_type;
    typedef void                        result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1, A2 const& a2) const
    {
      container_type that((extent_type(a1)),(allocator_type(a2)));
      boost::proto::value(a0).swap(that);
    }
  };

  /// INTERNAL ONLY
  /// Construct a terminal from another expression
  /// Non trivial assignment is passed to the parent expression type that will
  /// select how to perform the expression evaluation.
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      static_cast<typename A0::nt2_expression&>(a0) = a1;
    }
  };

  /// INTERNAL ONLY
  /// Construct a terminal from a scalar:
  ///  * Resize table to [1 1]
  ///  * Copy the scalar to the table memory (*raw() is the easiest way)
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0& a0, A1 const& a1) const
    {
      boost::proto::value(a0).resize(of_size_<1,1>());
      *(a0.raw()) = a1;
    }
  };

  /// INTERNAL ONLY
  /// Construct a terminal from a size and a Iterator pair
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::construct_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , ((node_ < A0,nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              (fusion_sequence_<A1>)
                              (iterator_< scalar_< unspecified_<A2> > >)
                              (iterator_< scalar_< unspecified_<A3> > >)
                            )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1 const& a1, A2 const& a2, A3 const& a3) const
    {
      BOOST_ASSERT_MSG
      ( nt2::numel(a1) >= (std::size_t)std::distance(a2,a3)
      , "Source range is larger than destination container."
      );

      boost::proto::value(a0).resize(a1);
      nt2::memory::copy( a2, a3, a0.raw() );
    }
  };
} }

#endif

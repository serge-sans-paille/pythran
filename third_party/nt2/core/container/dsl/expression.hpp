//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/dsl/domain.hpp>
#include <nt2/core/container/dsl/grammar.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/details/raw.hpp>
#include <nt2/core/container/dsl/details/resize.hpp>
#include <nt2/core/container/dsl/details/expression.hpp>
#include <nt2/core/container/dsl/details/expression_size.hpp>
#include <nt2/sdk/meta/container_traits.hpp>
#include <nt2/sdk/meta/settings_of.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>
#include <nt2/core/functions/function.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/memory/functions/assign.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <nt2/sdk/meta/fix_index.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/extends.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#if defined(BOOST_MSVC)
#pragma warning( push )
#pragma warning( disable : 4522 )
#endif

namespace nt2 { namespace container
{

  //==========================================================================
  // Conversion operator for integration with scalars:
  // - used for reductions that return scalars;
  // - used for table-to-scalar conversion.
  //==========================================================================
  template<class Expr, class Result, bool IsScalar>
  struct expression_scalar
  {
    BOOST_FORCEINLINE operator typename meta::value_type_<Result>::type() const
    {
      BOOST_ASSERT_MSG( nt2::numel( static_cast<expression<Expr, Result> const*>(this)->extent() ) == 1u
                      , "Table is not a scalar"
                      );
      return nt2::evaluate( static_cast<expression<Expr, Result> const&>(*this) ).raw()[0];
    }
  };

  template<class Expr, class Result>
  struct expression_scalar<Expr, Result, true>
  {
    BOOST_FORCEINLINE operator Result() const
    {
      return nt2::evaluate( static_cast<expression<Expr, Result> const&>(*this) );
    }
  };

  //============================================================================
  // proto expression wrapper for nt2 containers
  //============================================================================
  template<class Expr, class Result>
  struct expression : expression_scalar<Expr, Result, meta::is_scalar<Result>::value>
  {
    //==========================================================================
    // This type
    //==========================================================================
    typedef expression nt2_expression;

    //==========================================================================
    // Type of the parent expression
    //==========================================================================
    BOOST_PROTO_BASIC_EXTENDS(Expr, expression, domain)

    //==========================================================================
    // Extract Container information from Result
    //==========================================================================
    typedef typename meta::kind_<Result>::type              kind_type;
    typedef typename meta::value_type_<Result>::type        value_type;
    typedef typename meta::reference_<Result>::type         reference;
    typedef typename meta::const_reference_<Result>::type   const_reference;
    typedef typename meta::pointer_<Result>::type           pointer;
    typedef typename meta::const_pointer_<Result>::type     const_pointer;
    typedef typename meta::size_type_<Result>::type         size_type;

    typedef typename meta::settings_of<Result>::type        settings_type;

    typedef typename meta::option < Result
                                  , nt2::tag::index_
                                  >::type                   index_type;

    typedef typename meta::option < Result
                                  , nt2::tag::storage_order_
                                  >::type                   storage_order_type;

    //==========================================================================
    // Make the expression MPL-compatible
    //==========================================================================
    typedef boost::fusion::fusion_sequence_tag tag;

    //==========================================================================
    // Compute storage type for size
    //==========================================================================
    typedef typename size_transform<domain>::
            template result<size_transform<domain>(Expr&)>::type sizes_t;
    typedef typename meta::strip<sizes_t>::type                  extent_type;
    friend struct expression_size<sizes_t>;

    typedef typename index_type::index_type                      indexes_type;

    //==========================================================================
    // Default constructor required by table
    //==========================================================================
    BOOST_FORCEINLINE
    expression() : size_(size_transform<domain>()(proto_base())) {}

    //==========================================================================
    // Build an expression from a naked proto tree
    //==========================================================================
    BOOST_FORCEINLINE
    explicit  expression(Expr const& x)
            : proto_expr_(x)
            , size_(size_transform<domain>()(proto_base()))
    {}

    //==========================================================================
    // Copy construct from another expression
    //==========================================================================
    BOOST_FORCEINLINE
    expression( expression const& xpr )
              : proto_expr_(xpr.proto_base())
              , size_(proto_base(), xpr)
    {
    }

    //==========================================================================
    // Assignment operator forces evaluation
    //==========================================================================
    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<expression, Xpr>
                              , expression&
                              >::type
    operator=(Xpr const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    template<class Xpr> BOOST_FORCEINLINE
    typename boost::disable_if< boost::is_base_of<expression, Xpr>
                              , expression const&
                              >::type
    operator=(Xpr const& xpr) const
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    BOOST_FORCEINLINE expression& operator=(expression const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    BOOST_FORCEINLINE expression const& operator=(expression const& xpr) const
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    //==========================================================================
    // Expression indexing
    //==========================================================================
    #define M2(z,n,t)                                                     \
    fix_index<BOOST_PP_INC(n),t>( a##n, indexes_type(), this->extent() )  \
    /**/

    #define M1(z,n,t)                                             \
    typename result_of::fix_index < A##n,indexes_type,extent_type \
                                  , BOOST_PP_INC(n),t             \
                                  >::type                         \
    /**/

    #define M0(z,n,t)                                                 \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE       \
    typename meta::call                                               \
    < nt2::tag::function_                                             \
      ( expression const&, BOOST_PP_ENUM(n,M1,n) )                    \
    >::type                                                           \
    operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& a) ) const    \
    {                                                                 \
      return nt2::function(*this, BOOST_PP_ENUM(n,M2,n) );            \
    }                                                                 \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE       \
    typename meta::call                                               \
    < nt2::tag::function_                                             \
      ( expression&, BOOST_PP_ENUM(n,M1,n) )                          \
    >::type                                                           \
    operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A, const& a) )          \
    {                                                                 \
      return nt2::function(*this, BOOST_PP_ENUM(n,M2,n) );            \
    }                                                                 \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)
    #undef M0
    #undef M1
    #undef M2

    //==========================================================================
    // Idempotent operator() indexing
    //==========================================================================
    BOOST_FORCEINLINE expression&        operator()()        { return *this; }
    BOOST_FORCEINLINE expression const&  operator()() const  { return *this; }

    //==========================================================================
    // Return current expression extent
    //==========================================================================
    BOOST_FORCEINLINE extent_type const& extent() const { return size_.data(); }

    //==========================================================================
    // Return current expression extent
    //==========================================================================
    BOOST_FORCEINLINE std::size_t size() const
    {
      return nt2::numel(extent());
    }

    //==========================================================================
    // Return current expression base indexes
    //==========================================================================
    BOOST_FORCEINLINE indexes_type indexes() const { return indexes_type(); }

    //==========================================================================
    // Return current expression leading_size
    //==========================================================================
    BOOST_FORCEINLINE size_type leading_size() const
    {
      typedef typename boost::mpl
                            ::apply < storage_order_type
                                    , boost::mpl::size_t<extent_type::static_size>
                                    , boost::mpl::size_t<0U>
                                    >::type                     dim_t;
      return size_.data()[dim_t::value];
    }

    //==========================================================================
    // push_back through container
    //==========================================================================
    template<typename Data>
    void push_back(Data const& c)
    {
      //========================================================================
      //       ****NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL****
      // If this static assert triggers, push_back has been called onto
      // a non-terminal
      //       ****NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL
                          , (Expr&)
                          );

      boost::proto::value(*this).push_back(c);
    }

    template<typename Data>
    void push_back(Data const& c, std::size_t d)
    {
      //========================================================================
      //       ****NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL****
      // If this static assert triggers, push_back has been called onto
      // a non-terminal
      //       ****NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_PUSH_BACK_ON_NON_TERMINAL
                          , (Expr&)
                          );

      boost::proto::value(*this).push_back(c, d);
    }

    //==========================================================================
    // Access to raw data
    //==========================================================================
    pointer       raw()
    {
      //========================================================================
      //       ****NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL****
      // If this static assert triggers, the raw memory of a non terminal node
      // has been requested.
      //       ****NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                          , (Expr&)
                          );

      return nt2::details::raw(boost::proto::value(*this));
    }

    const_pointer raw() const
    {
      //========================================================================
      //          ***NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL****
      // If this static assert triggers, the raw memory of a non terminal node
      // has been requested.
      //          ****NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL****
      //========================================================================
      BOOST_MPL_ASSERT_MSG( (boost::proto::arity_of<Expr>::value == 0)
                          , NT2_INVALID_ACCESS_TO_RAW_DATA_ON_NON_TERMINAL
                          , (Expr&)
                          );

      return nt2::details::raw(boost::proto::value(*this));
    }

    //==========================================================================
    // Destructive resize of expression
    //==========================================================================
    template<class Sz> BOOST_FORCEINLINE void resize(Sz const& sz)
    {
      ext::resize< typename boost::dispatch::meta::
                   hierarchy_of<proto_tag>::type
                 , domain
                 , proto_arity_c
                 , expression<Expr, Result>
                 >
      ()(*this, sz);
    }

    template<class Sz> BOOST_FORCEINLINE void resize(Sz const& sz) const
    {
      ext::resize< typename boost::dispatch::meta::
                   hierarchy_of<proto_tag>::type
                 , domain
                 , proto_arity_c
                 , expression<Expr, Result> const
                 >
      ()(*this, sz);
    }

  protected:
    expression_size<sizes_t> size_;
  };
} }

#if defined(BOOST_MSVC)
#pragma warning( pop )
#endif

#endif

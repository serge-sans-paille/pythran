//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_FUNCTION_INDEX_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_FUNCTION_INDEX_HPP_INCLUDED

#include <nt2/core/functions/function_index.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/core/functions/table/details/reindex.hpp>
#include <nt2/core/functions/table/details/function_index_size.hpp>
#include <nt2/core/functions/table/details/function_index_value_type.hpp>
#include <nt2/core/functions/table/details/is_vectorizable_indexer.hpp>
#include <boost/fusion/include/zip_view.hpp>
#include <boost/fusion/include/transform_view.hpp>
#include <boost/mpl/if.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (Expr)(State)(Data)(Arity)
                            , ((expr_< unspecified_<Expr>
                                     , nt2::tag::function_index_
                                     , Arity
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (unspecified_<Data>)
                            )
  {
    // Get the indexed parameters
    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 2>::value_type
                 >::type                                      size_type;

    typedef typename boost::proto::result_of::
            value< typename boost::proto::result_of::
                   child_c<Expr&, 3>::value_type
                 >::type::type                                index_type;

    // Get the indexing expression pack
    typedef typename boost::proto::result_of::
                     child_c<Expr&, 0>::value_type            childN;

    // ... and computes its number of indexes
    static const long arity = childN::proto_arity_c;

    // Compute a type able to hold the position we look for
    typedef typename boost::mpl::
            if_< typename is_vectorizable_indexers<childN, Data>::type
               , State
               , typename details::as_integer_target<Data>::type
               >::type                                         i_t;
    typedef boost::array<i_t, arity>                         pos_type;

    // Once set, we build a type with evaluation targets
    typedef boost::array< boost::dispatch::meta::as_<i_t>
                        , arity
                        >                                     target_type;

    // We use a zip_view for passign all those informations to relative_index
    typedef boost::fusion::vector< childN const&
                                 , index_type const&
                                 , size_type const&
                                 , pos_type const&
                                 , target_type const&
                                 >                            seq;

    typedef boost::fusion::zip_view<seq>                      zipped;
    typedef boost::fusion::
            transform_view<zipped const, details::reindex>    transformed;

    typedef i_t result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, State const& state, Data const&) const
    {
      // Compute base index of the source expression
      index_type indexes;
      target_type targets;

      // Grab the destination subscript
      pos_type pos = as_subscript( typename make_size<arity>::type(expr.extent())
                                 , nt2::enumerate<i_t>(state)
                                 );

      // Apply index_t to each subscript value
      transformed trs = boost::fusion::
                        transform( zipped
                                   ( seq( boost::proto::child_c<0>(expr)
                                        , indexes
                                        , boost::proto::value(boost::proto::child_c<2>(expr))
                                        , pos
                                        , targets
                                        )
                                   )
                                 , details::reindex()
                                 );

      // Get the linear position from the transformed subscript and evaluate
      return nt2::as_index( boost::proto::value(boost::proto::child_c<2>(expr))
                          , trs
                          );
    }
  };
} }

#endif

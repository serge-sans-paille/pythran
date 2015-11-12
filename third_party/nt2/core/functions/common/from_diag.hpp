//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FROM_DIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FROM_DIAG_HPP_INCLUDED

#include <nt2/core/functions/from_diag.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/eq.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <nt2/sdk/meta/as_signed.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::from_diag_
                                      , boost::mpl::long_<1>
                                      ,nt2::container::domain>
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                       result_type;
    typedef typename meta::as_index<result_type>::type                      i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename result_of::as_subscript<_2D,p_t>::type                 s_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript( a0.extent()
                                  , enumerate<i_t>(p)
                                  );

      // Return a diagonal built from boost::proto::child_c<0>(a0)
      return nt2::if_else ( nt2::eq( pos[0], pos[1] )
                          , nt2::run(boost::proto::child_c<0>(a0), pos[1], t)
                          , Zero<result_type>()
                          );
    }
  };

  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct value_type<nt2::tag::from_diag_,Domain,2,Expr>
       : meta::value_as<Expr, 0>
  {
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::from_diag_
                                      , boost::mpl::long_<2>
                                      ,nt2::container::domain>
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename Data::type                                     result_type;
    typedef typename meta::as_index<result_type>::type                      i_t;
    typedef typename meta::as_signed<i_t>::type                             si_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename result_of::as_subscript<_2D,p_t>::type                 s_t;
    typedef typename s_t::value_type                                       sp_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const pos = as_subscript( a0.extent()
                                  , enumerate<i_t>(p)
                                  );

      // Compute the offset and new position
      std::ptrdiff_t o = boost::proto::value(boost::proto::child_c<1>(a0));
      si_t p0 = bitwise_cast<si_t>(pos[0]) + o;
      si_t p1 = bitwise_cast<si_t>(pos[1]);
      si_t pp = p1 - o + (o < 0 ? o : 0);
      si_t nz = splat<si_t>(numel(boost::proto::child_c<0>(a0))-1);

      return nt2::if_else ( nt2::eq( p0, p1 )
                          , nt2::run( boost::proto::child_c<0>(a0)
                                    , bitwise_cast<i_t> ( max ( min(pp,nz)
                                                              , Zero<si_t>()
                                                              )
                                                        )
                                    , t
                                    )
                          , Zero<result_type>()
                          );
    }
  };
} }

#endif

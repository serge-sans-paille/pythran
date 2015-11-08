//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_CDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_CDIFF_HPP_INCLUDED

#include <nt2/core/functions/cdiff.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/core/utility/as_index.hpp>
#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/sdk/meta/as_index.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::cdiff_, N, nt2::container::domain>))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                                     result_type;
    typedef typename A0::extent_type                                      ext_t;
    typedef typename meta::as_index<result_type>::type                    i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename result_of::as_subscript<ext_t,p_t>::type             sub_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      std::size_t along = boost::proto::child_c<1>(a0);
      ext_t ex0         = boost::proto::child_c<0>(a0).extent();

      sub_t pos0 = as_subscript(a0.extent(),enumerate<i_t>(p));
      sub_t pos1 = pos0;
      pos1[along] += Two<typename meta::scalar_of<p_t>::type>();

      return nt2::run(boost::proto::child_c<0>(a0),as_index(ex0, pos1),t)
           - nt2::run(boost::proto::child_c<0>(a0),as_index(ex0, pos0),t);
    }
  };
} }

#endif

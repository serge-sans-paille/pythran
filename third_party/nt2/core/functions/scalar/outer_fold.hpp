//==============================================================================
//        Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//        Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//         Distributed under the Boost Software License, Version 1.0.
//                See accompanying file LICENSE.txt or copy at
//                    http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_OUTER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/outer_fold.hpp>
#include <nt2/core/functions/details/outer_fold_step.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/include/functions/scalar/numel.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Global outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::outer_fold_, tag::cpu_
                             , (Out)(In)(Neutral)(Bop)(Uop)
                             , ((ast_< Out, nt2::container::domain>))
                               ((ast_< In, nt2::container::domain>))
                               (unspecified_<Neutral>)
                               (unspecified_<Bop>)
                               (unspecified_<Uop>)
                             )
  {
    typedef void                                                              result_type;
    typedef typename Out::value_type                                           value_type;
    typedef typename In::extent_type                                          extent_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Neutral const& neutral, Bop const& bop, Uop const&) const
    {
      extent_type ext = in.extent();
      std::size_t obound =  boost::fusion::at_c<2>(ext);
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t mbound =  boost::fusion::at_c<1>(ext);
      std::size_t iboundxmbound =  ibound * mbound;

      for(std::size_t o = 0, oout_ = 0, oin_ = 0;
         o < obound;
         ++o, oout_+=ibound, oin_+= iboundxmbound)
      {
        details::outer_fold_step<value_type,Out,In,Neutral,Bop>
        (out, in, neutral, bop, 0, ibound, oout_, oin_);
      }
    }
  };

}}

#endif

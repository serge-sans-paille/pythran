//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INNER_SCAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INNER_SCAN_HPP_INCLUDED

#include <nt2/core/functions/inner_scan.hpp>
#include <nt2/core/functions/details/scan_step.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // General inner_scan
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_scan_, tag::cpu_
                            , (Out)(In)(Neutral)(Bop)(Uop)
                            , ((ast_< Out, nt2::container::domain>))
                              ((ast_< In, nt2::container::domain>))
                              (unspecified_<Neutral>)
                              (unspecified_<Bop>)
                              (unspecified_<Uop>)
                            )
  {
    typedef void                                                              result_type;
    typedef typename Out::value_type                                          value_type;
    typedef typename In::extent_type                                          extent_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Neutral const& neutral, Bop const& bop, Uop const&) const
    {
      extent_type ext = in.extent();
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));
      std::size_t ibound  = boost::fusion::at_c<0>(ext);

      for(std::size_t j = 0, k = 0; j < obound; ++j, k+=ibound)
      {
        value_type res = details::scan_step(
                           neutral(nt2::meta::as_<value_type>())
                          ,out, in
                          ,bop
                          ,k, ibound, 1
                          ,false
                          );
        boost::dispatch::ignore_unused(res);
      }
    }
  };

} }

#endif

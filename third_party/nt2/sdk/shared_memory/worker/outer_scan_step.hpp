//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_OUTER_SCAN_STEP_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_OUTER_SCAN_STEP_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/core/functions/details/scan_step.hpp>
#include <nt2/sdk/shared_memory/details/target_type_from_site.hpp>
#include <nt2/include/functor.hpp>
#include <cstdio>

namespace nt2
{

  namespace tag
  {
    struct outer_scan_step_incache_;
    struct outer_scan_step_outcache_;
  }
  // Outer Scan Step worker incache
  template<class BackEnd, class Site, class Out, class In, class Neutral, class Bop>
  struct worker<tag::outer_scan_step_incache_,BackEnd,Site,Out,In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type extent_type;
    typedef typename Out::value_type value_type;

    worker(Out & out, In & in, Neutral const & neutral, Bop const & bop
          ,std::size_t o)
          :out_(out),in_(in),neutral_(neutral),bop_(bop),o_(o)
    {}

    void operator()(std::size_t begin, std::size_t size)
    {
       extent_type ext = in_.extent();
       std::size_t ibound = boost::fusion::at_c<0>(ext);
       std::size_t mbound = boost::fusion::at_c<1>(ext);

       for( std::size_t i=0, i_ = o_ + begin; i<size; ++i, ++i_)
       {
         value_type summary = neutral_(meta::as_<value_type>());
         summary = details::scan_step( summary
                                     , out_, in_
                                     , bop_
                                     , i_, mbound, ibound
                                     , false);
       }
    }

    Out & out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;
    std::size_t o_;

    private:
    worker& operator=(worker const&);
  };

  // Outer Scan Step worker outcache
  template<class BackEnd, class Site, class Out, class In, class Neutral, class Bop>
  struct worker<tag::outer_scan_step_outcache_,BackEnd,Site, Out, In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type extent_type;

    worker(Out & out, In & in, Neutral const & neutral, Bop const & bop, std::size_t o)
          :out_(out),in_(in),neutral_(neutral),bop_(bop),o_(o)
    {}

    template<class Summary>
    Summary operator()(Summary summary, std::size_t begin, std::size_t size, bool prescan)
    {
      extent_type ext = in_.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);

      return details::scan_step( summary
                               , out_, in_
                               , bop_
                               , o_ + begin*ibound, size, ibound
                               , prescan);
    };

    Out & out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;
    std::size_t o_;

    private:
    worker& operator=(worker const&);
  };

}
#endif

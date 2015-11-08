//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_OUTER_FOLD_STEP_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_OUTER_FOLD_STEP_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/core/functions/details/fold_step.hpp>
#include <nt2/core/functions/details/outer_fold_step.hpp>
#include <nt2/sdk/shared_memory/details/target_type_from_site.hpp>

namespace nt2
{

  namespace tag
  {
    struct outer_fold_step_incache_;
    struct outer_fold_step_outcache_;
  }
  // Outer Fold Step worker incache
  template<class BackEnd, class Site, class Out, class In, class Neutral, class Bop>
  struct worker<tag::outer_fold_step_incache_,BackEnd,Site,Out,In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type           extent_type;
    typedef typename Out::value_type                                          value_type;
    typedef typename details::target_type_from_site<Site,value_type>::type    target_type;

    worker(Out & out, In & in, Neutral const & neutral, Bop const & bop)
          :out_(out),in_(in),neutral_(neutral),bop_(bop)
    {}

    void operator()(std::size_t begin, std::size_t size)
    {
        details::outer_fold_step<target_type,Out,In,Neutral,Bop>
        (out_, in_, neutral_, bop_, begin, size, oout_, oin_);
    }

    void update(std::size_t oout, std::size_t oin)
    {
      oout_ = oout;
      oin_  = oin;
    }

    Out & out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;
    std::size_t oout_;
    std::size_t oin_;

    private:
    worker& operator=(worker const&);
  };

  // Outer Fold Step worker outcache
  template<class BackEnd, class Site, class In, class Neutral, class Bop>
  struct worker<tag::outer_fold_step_outcache_,BackEnd,Site,In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type extent_type;

    worker(In & in, Neutral const & neutral, Bop const & bop)
          :in_(in),neutral_(neutral),bop_(bop)
    {}

    template<class Out>
    Out operator()(Out const & out, std::size_t begin, std::size_t size)
    {
      extent_type ext = in_.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);

      return details::fold_step(out, in_, bop_, o_ + begin*ibound, size, ibound);
    };

    void update(std::size_t o)
    {
      o_ = o;
    }



    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;
    std::size_t o_;

    private:
    worker& operator=(worker const&);
  };

}
#endif

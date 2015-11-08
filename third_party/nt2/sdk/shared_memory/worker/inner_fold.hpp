//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_INNER_FOLD_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_INNER_FOLD_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/sdk/shared_memory/spawner.hpp>
#include <nt2/sdk/shared_memory/details/target_type_from_site.hpp>
#include <nt2/include/functor.hpp>

#include <nt2/sdk/config/cache.hpp>

namespace nt2
{

  namespace tag
  {
    struct inner_fold_step_;
    struct fold_;
  }

  // Inner Fold Step worker
  template<class BackEnd, class Site, class In, class Neutral, class Bop>
  struct worker<tag::inner_fold_step_,BackEnd,Site,In,Neutral,Bop>
  {
    worker(In & in, Neutral const & neutral, Bop const & bop)
          :in_(in),neutral_(neutral),bop_(bop)
    {}

    template<class Out>
    Out operator()(Out & out, std::size_t begin, std::size_t size)
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<Out>::value;
      return details::fold_step(out, in_, bop_, begin, size/N, N);
    };

    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;

    private:
    worker& operator=(worker const&);
  };

  // Inner Fold worker
  template<class BackEnd,class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::inner_fold_,BackEnd,Site,Out,In,Neutral,Bop,Uop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type           extent_type;
    typedef typename Out::value_type                                          value_type;
    typedef typename details::target_type_from_site<Site,value_type>::type    target_type;

    worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
    : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
    {}

    void operator()(std::size_t begin, std::size_t size) const
    {
      extent_type ext = in_.extent();
      std::size_t top_cache_line_size = config::top_cache_line_size(2)/sizeof(value_type);
      std::size_t grain  = top_cache_line_size;

      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t iibound = (ibound/grain) * grain;
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));

      nt2::worker<tag::inner_fold_step_,BackEnd,Site,In,Neutral,Bop>
      vec_w(in_,neutral_,bop_);

      nt2::worker<tag::inner_fold_step_,BackEnd,tag::cpu_,In,Neutral,Bop>
      scalar_w(in_,neutral_,bop_);

      nt2::spawner<tag::fold_, BackEnd, target_type> s;

      for(std::size_t j = begin, k=begin*ibound; j < begin+size; ++j, k+=ibound)
      {
        target_type vec_out = neutral_(nt2::meta::as_<target_type>());
        value_type s_out = neutral_(nt2::meta::as_<value_type>());

        if( (size == obound) && (grain < iibound) )
           vec_out = s( vec_w, k, iibound, grain );

        else if( iibound != 0 )
           vec_out = vec_w(vec_out, k, iibound);

        s_out = uop_( vec_out );
        s_out = scalar_w(s_out, k+iibound, ibound-iibound);

        nt2::run(out_, j, s_out);
      }
    }

    Out&                     out_;
    In&                      in_;
    Neutral const &          neutral_;
    Bop const &              bop_;
    Uop const &              uop_;

    private:
    worker& operator=(worker const&);
   };

}
#endif

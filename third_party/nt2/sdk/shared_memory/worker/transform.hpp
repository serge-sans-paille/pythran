//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_TRANSFORM_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_TRANSFORM_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{

  namespace tag
  {
    struct transform_;
  }

  // Transform Worker
  template<class BackEnd,class Site, class Out, class In>
  struct worker<tag::transform_,BackEnd,Site,Out,In>
  {
      worker(Out & out, In & in)
      :out_(out),in_(in)
      {}

      void operator()(std::size_t begin, std::size_t size)
      {
          work(out_,in_,std::make_pair(begin,size));
      };

      Out & out_;
      In & in_;

      nt2::functor<tag::transform_,Site> work;

  private:
  worker& operator=(worker const&);
  };

}
#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_SPAWNER_FOLD_HPP_INCLUDED
#define NT2_SDK_TBB_SPAWNER_FOLD_HPP_INCLUDED

#if defined(NT2_USE_TBB)

#include <tbb/tbb.h>
#include <nt2/sdk/tbb/blocked_range.hpp>
#include <nt2/sdk/shared_memory/spawner.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{

  namespace tag
  {
    struct fold_;
    template<class T> struct tbb_;
  }

  namespace details
  {
    template<class Worker, class result_type>
    struct Tbb_Folder
    {
        Tbb_Folder(Worker & w)
        :w_(w)
        {
            out_ = w.neutral_(nt2::meta::as_<result_type>());
        }

        Tbb_Folder(Tbb_Folder& src, tbb::split)
        : w_(src.w_)
        {
            out_ = w_.neutral_(nt2::meta::as_<result_type>());
        }

        void operator()(nt2::blocked_range<std::size_t> const& r)
        {
            out_ = w_(out_,r.begin(),r.size());
        };

        void join(Tbb_Folder& rhs) { out_ = w_.bop_(out_, rhs.out_); }

        Worker & w_;
        result_type out_;

    private:
        Tbb_Folder& operator=(Tbb_Folder const&);

    };
  }

  template<class Site, class result_type>
  struct spawner< tag::fold_, tag::tbb_<Site>, result_type>
  {

    spawner(){}

    template<typename Worker>
    result_type operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif

     BOOST_ASSERT_MSG( size % grain == 0, "Reduce size not divisible by grain");

     details::Tbb_Folder<Worker,result_type> tbb_w ( w );

#ifndef BOOST_NO_EXCEPTIONS
            try
            {
#endif
             tbb::parallel_reduce( nt2::blocked_range<std::size_t>(begin,begin+size,grain)
                                  ,tbb_w
                                 );

#ifndef BOOST_NO_EXCEPTIONS
            }
            catch(...)
            {
              exception = boost::current_exception();
            }
#endif

      return tbb_w.out_;
    }

};
}

#endif
#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_DETAILS_TARGET_TYPE_FROM_SITE_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_DETAILS_TARGET_TYPE_FROM_SITE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>

namespace nt2
{
  namespace details
  {
   template<class Site, class value_type>
   struct target_type_from_site
   {
     typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION> type;
   };

   template<class value_type>
   struct target_type_from_site<tag::cpu_,value_type>
   {
     typedef value_type type;
   };

  }
}
#endif

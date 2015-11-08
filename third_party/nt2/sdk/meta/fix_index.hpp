//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_FIX_INDEX_HPP_INCLUDED
#define NT2_SDK_META_FIX_INDEX_HPP_INCLUDED

namespace nt2
{
  namespace result_of
  {
    template< class Indexer, class Base, class Size
            , std::size_t I, std::size_t N
            >
    struct fix_index
    {
      typedef Indexer const& type;

      static BOOST_FORCEINLINE type
      call(Indexer const& i , Base const&, Size const&)
      {
        return i;
      }
    };
  }

  template<std::size_t I, std::size_t N,class Indexer, class Base, class Size>
  BOOST_FORCEINLINE
  typename result_of::fix_index<Indexer,Base,Size,I,N>::type
  fix_index(Indexer const& i, Base const& b, Size const& s)
  {
    return result_of::fix_index<Indexer,Base,Size,I,N>::call(i,b,s);
  }

}

#endif

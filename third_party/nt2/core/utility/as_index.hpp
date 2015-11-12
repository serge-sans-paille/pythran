//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_AS_INDEX_HPP_INCLUDED
#define NT2_CORE_UTILITY_AS_INDEX_HPP_INCLUDED

#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <cstddef>

namespace nt2 { namespace result_of
{
  template<class Seq>
  struct sequence_value
   : boost::dispatch::meta::
     strip< typename boost::mpl::
            eval_if_c< boost::fusion::result_of::size<Seq>::type::value == 0
                     , boost::mpl::identity<std::size_t>
                     , boost::fusion::result_of::value_at_c<Seq, 0>
                     >::type
          >
  {
  };

  template<class Size, class Position>
  struct as_index
  {
    typedef typename sequence_value<Position>::type               typeS;
    typedef typename meta::as_unsigned<typeS>::type               type;

    BOOST_FORCEINLINE type
    operator()(const Size& size, const Position& pos) const
    {
      typedef typename boost::fusion::result_of::size<Position>::type dims;
      return eval ( size, pos
                  , boost::mpl::int_<0>()
                  , boost::mpl::int_<dims::value-1>()
                  );
    }

    template<class Idx, class Sz>
    BOOST_FORCEINLINE type
    eval(const Size& s, const Position& p, const Idx&, const Sz& sz) const
    {
      return  splat<type>( boost::fusion::at_c<Idx::value>(p) )
            + splat<type>( boost::fusion::at_c<Idx::value>(s) )
            * eval(s,p,boost::mpl::int_<Idx::value+1>(),sz);
    }

    template<class Sz>
    BOOST_FORCEINLINE type
    eval(const Size& s,const Position& p,const boost::mpl::int_<0>&,const Sz& sz) const
    {
      return  splat<type>( boost::fusion::at_c<0>(p) )
            + splat<type>( boost::fusion::at_c<0>(s) )
            * eval(s,p,boost::mpl::int_<1>(),sz);
    }

    template<class Sz>
    BOOST_FORCEINLINE type
    eval(const Size&, const Position& p, const Sz&, const Sz&) const
    {
      return splat<type>( boost::fusion::at_c<Sz::value>(p) );
    }

    BOOST_FORCEINLINE type
    eval( const Size&, const Position& p
        , const boost::mpl::int_<0>&, const boost::mpl::int_<0>&
        ) const
    {
      return splat<type>( boost::fusion::at_c<0>(p) );
    }

    BOOST_FORCEINLINE type
    eval( const Size&, const Position&
        , const boost::mpl::int_<0>&, const boost::mpl::int_<-1>&
        ) const
    {
      return Zero<type>();
    }
  };
} }

namespace nt2
{
  template<class Size,class Position>
  typename result_of::as_index<Size,Position>::type
  as_index(Size const& sz, Position const& p)
  {
    return result_of::as_index<Size,Position>()(sz,p);
  }
}

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_SIZE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_SIZE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/comparison.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T1,class T2, class Tr, class Op>
  struct  size_check
        : boost::mpl::apply < Op
                            , boost::mpl::
                              sizeof_<typename boost::mpl::apply<Tr,T1>::type>
                            , boost::mpl::
                              sizeof_<typename boost::mpl::apply<Tr,T2>::type>
                            >
  {};
} } }

namespace boost { namespace simd { namespace meta
{
    template<class T1,class T2,class Transform = boost::mpl::_>
    struct  has_same_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::equal_to< boost::mpl::_1
                                                      , boost::mpl::_2
                                                      >
                                >
    {};

    template<class T1,class T2,class Transform = boost::mpl::_>
    struct  has_different_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::not_equal_to< boost::mpl::_1
                                                          , boost::mpl::_2
                                                          >
                                >
    {};

    template<class T1,class T2,class Transform = boost::mpl::_>
    struct  has_smaller_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::less< boost::mpl::_1
                                                  , boost::mpl::_2
                                                  >
                                >
    {};

    template<class T1,class T2,class Transform = boost::mpl::_>
    struct has_larger_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::greater < boost::mpl::_1
                                                      , boost::mpl::_2
                                                      >
                                >
    {};

    template<class T1,class T2,class Transform = boost::mpl::_>
    struct has_smaller_or_equal_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::less_equal< boost::mpl::_1
                                                        , boost::mpl::_2
                                                        >
                                >
    {};

    template<class T1,class T2,class Transform = boost::mpl::_>
    struct has_larger_or_equal_size
          : details::size_check < T1
                                , T2
                                , Transform
                                , boost::mpl::greater_equal < boost::mpl::_1
                                                            , boost::mpl::_2
                                                            >
                                >
    {};

} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED
#define NT2_SDK_MEMORY_COMPOSITE_REFERENCE_HPP_INCLUDED

#include <nt2/sdk/meta/container_traits.hpp>
#include <boost/simd/sdk/functor/proxy.hpp>
#include <boost/simd/sdk/tuple.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/copy.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/utility/enable_if.hpp>

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::composite_reference class
  **/
//==============================================================================
namespace nt2 { namespace container
{
  template<class T>
  class composite_reference
      : public  boost::mpl::
                transform < typename  boost::fusion::result_of::
                                      as_vector<T>::type
                          , boost::mpl::if_
                            < boost::is_const<T>
                            , meta::const_reference_<boost::mpl::_>
                            , meta::reference_<boost::mpl::_>
                            >
                          >::type
  {
    public:
    typedef typename boost::remove_const<T>::type                   value_type;
    typedef typename  boost::mpl::
            transform < typename boost::fusion::result_of::as_vector<T>::type
                      , boost::mpl::if_ < boost::is_const<T>
                                        , meta::const_reference_<boost::mpl::_>
                                        , meta::reference_<boost::mpl::_>
                                        >
                      >::type                 parent;

    template<class U>
    composite_reference ( U& src
                        , typename boost
                          ::enable_if< boost::is_convertible<U,parent> >::type* = 0
                        ) : parent( src )
    {}

    template<class U>
    composite_reference& operator=(U const& src)
    {
      boost::fusion::copy(src,*this);
      return *this;
    }

    operator value_type() const
    {
      return boost::simd::as_tuple<value_type>(*this);
    }
  };

  template<class T>
  std::ostream& operator<<(std::ostream& os,composite_reference<T> const& cr)
  {
    return boost::fusion::out(os, cr);
  }
} }

// composite_reference is a proxy type
namespace boost { namespace dispatch { namespace meta
{
  template<class T,class Origin>
  struct  hierarchy_of< nt2::container::composite_reference<T>
                      , Origin
                      >
  {
    typedef meta::proxy_<Origin>       type;
  };
} } }

// composite_reference is a pseudo-reference type, adapt meta-functions
// that removes reference qualifiers accordingly
namespace boost { namespace dispatch { namespace meta
{
  template<typename T>
  struct strip< nt2::container::composite_reference<T> >
  {
    typedef typename nt2::container::composite_reference<T>::value_type type;
  };

  template<typename T>
  struct value_of< nt2::container::composite_reference<T> >
       : add_reference<typename value_of<T>::type>
  {
  };

  template<typename T>
  struct scalar_of< nt2::container::composite_reference<T> >
       : mpl::if_< is_same< typename scalar_of<T>::type
                          , T
                          >
                 , nt2::container::composite_reference<T>
                 , typename add_reference<typename scalar_of<T>::type>::type
                 >
  {
  };

  template<typename T>
  struct model_of< nt2::container::composite_reference<T> >
  {
    template<class X>
    struct apply
    {
      typedef nt2::container::composite_reference<X> type;
    };
  };
} } }

namespace boost
{
  template<class T>
  struct remove_reference< nt2::container::composite_reference<T> >
  {
    typedef T type;
  };
}

// disable Fusion overloads, use our own
namespace boost { namespace simd
{
  template<class T>
  struct is_value;

  template<class T>
  struct is_value< nt2::container::composite_reference<T> >
       : is_value<T>
  {
  };
} }

namespace boost { namespace fusion { namespace traits
{
  template<typename T>
  struct  enable_equality < nt2::container::composite_reference<T>
                          , nt2::container::composite_reference<T>
                          >
        : mpl::not_< simd::is_value<T> >
  {};

  template<typename T>
  struct  enable_equality < nt2::container::composite_reference<T>
                          , T
                          >
        : mpl::not_< simd::is_value<T> >
  {};

  template<typename T>
  struct  enable_equality < T
                          , nt2::container::composite_reference<T>
                          >
        : mpl::not_< simd::is_value<T> >
  {};

  template<typename T>
  struct  enable_comparison < nt2::container::composite_reference<T>
                            , nt2::container::composite_reference<T>
                            >
        : mpl::not_< simd::is_value<T> >
  {};

  template<typename T>
  struct  enable_comparison < nt2::container::composite_reference<T>
                            , T
                            >
        : mpl::not_< simd::is_value<T> >
  {};

  template<typename T>
  struct  enable_comparison < T
                            , nt2::container::composite_reference<T>
                            >
        : mpl::not_< simd::is_value<T> >
  {};
} } }

#endif

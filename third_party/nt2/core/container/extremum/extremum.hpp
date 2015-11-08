//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_EXTREMUM_EXTREMUM_HPP_INCLUDED
#define NT2_CORE_CONTAINER_EXTREMUM_EXTREMUM_HPP_INCLUDED

#include <nt2/sdk/meta/fix_index.hpp>

namespace nt2 { namespace container
{
  //==========================================================================
  // extremum is an helper class that handles end_ and begin_ behavior
  //==========================================================================
  template<bool isEnd> struct extremum
  {
    std::ptrdiff_t offset_;

    template<class B, class Sz>
    BOOST_FORCEINLINE std::ptrdiff_t index(B const& b, Sz const& s) const
    {
      return index(b,s,boost::mpl::bool_<isEnd>());
    }

    private:
    BOOST_FORCEINLINE std::ptrdiff_t
    index(std::ptrdiff_t const& b, std::ptrdiff_t const& s, boost::mpl::true_) const
    {
      BOOST_ASSERT_MSG( (offset_ <= 0)
                      , "end_ is used with a non negative offset"
                      );
      return s + b - 1 + offset_;
    }

    BOOST_FORCEINLINE std::ptrdiff_t
    index(std::ptrdiff_t const& b, std::ptrdiff_t const&, boost::mpl::false_) const
    {
      BOOST_ASSERT_MSG( (offset_ >= 0)
                      , "begin_ is used with a non positive offset"
                      );
      return b + offset_;
    }
  };

  template<class T, bool B>
  BOOST_FORCEINLINE extremum<B> operator-(extremum<B> const& e, T o)
  {
    extremum<B> that = { e.offset_ - (std::ptrdiff_t)o };
    return that;
  }

  template<class T, bool B>
  BOOST_FORCEINLINE extremum<B> operator+(extremum<B> const& e, T o)
  {
    extremum<B> that = { e.offset_ + (std::ptrdiff_t)o };
    return that;
  }

  template<class T>
  BOOST_FORCEINLINE extremum<false> operator+(T o, extremum<false> const& e)
  {
    extremum<false> that = { e.offset_ + (std::ptrdiff_t)o };
    return that;
  }
} }

namespace nt2 { namespace meta
{
  template<class T>
  struct  is_extremum
        : boost::mpl::false_
  {};

  template<bool B>
  struct  is_extremum< container::extremum<B> >
        : boost::mpl::true_
  {};
} }

namespace nt2
{
  //============================================================================
  /*!
   * end_ acts as the latest index of a container along a given dimension in
   * array indexing
   **/
  //============================================================================
  container::extremum<true>   const end_    = {0};

  //============================================================================
  /*!
   * begin_ acts as the first index of a container along a given dimension in
   * array indexing
   **/
  //============================================================================
  container::extremum<false>  const begin_  = {0};

  //============================================================================
  // fix_index one extremum
  //============================================================================
  namespace result_of
  {
    template< bool B, class Base, class Size
            , std::size_t I, std::size_t N
            >
    struct fix_index<container::extremum<B>,Base,Size,I,N>
    {
      typedef std::ptrdiff_t type;

      static BOOST_FORCEINLINE type
      call(container::extremum<B> const& i , Base const&, Size const& s)
      {
        return i.index( boost::mpl::at_c<Base,I-1>::type::value
                      , s[I-1]
                      );
      }
    };

    template< bool B, class Base, class Size, std::size_t N>
    struct fix_index<container::extremum<B>,Base,Size,N,N>
    {
      typedef std::ptrdiff_t              type;
      typedef typename make_size<N>::type size_type;

      static BOOST_FORCEINLINE type
      call(container::extremum<B> const& i , Base const&, Size const& s)
      {
        return i.index( boost::mpl::at_c<Base,N-1>::type::value
                      , size_type(s)[N-1]
                      );
      }
    };
  }
}

#endif

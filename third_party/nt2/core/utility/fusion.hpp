//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_FUSION_HPP_INCLUDED
#define NT2_CORE_UTILITY_FUSION_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/advance.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/next_prior.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace details
{
  template<class Begin, class End>
  BOOST_FORCEINLINE
  boost::fusion::iterator_range<Begin const, End const>
  make_iterator_range(Begin const& begin, End const& end)
  {
    return boost::fusion::iterator_range<Begin const, End const>(begin, end);
  }

  template<class InB, class InE, class Out> BOOST_FORCEINLINE
  void copy(InB const& inb, InE const& inE, Out const& out);

  template<class InB, class InE, class Out> BOOST_FORCEINLINE
  void copy(InB const&, InE const&, Out const&, boost::mpl::true_)
  {
  }

  template<class InB, class InE, class Out> BOOST_FORCEINLINE
  void copy(InB const& inb, InE const& inE, Out const& out, boost::mpl::false_)
  {
    *out = *inb;
    return details::copy(boost::fusion::next(inb), inE, boost::next(out));
  }

  template<class InB, class InE, class Out> BOOST_FORCEINLINE
  void copy(InB const& inb, InE const& inE, Out const& out)
  {
    typename boost::fusion::result_of::equal_to<InB, InE>::type eq;
    return details::copy(inb, inE, out, eq);
  }

  template<class Src, class Dst> BOOST_FORCEINLINE
  void copy(Src const& src, Dst const& dst)
  {
    return details::copy(boost::fusion::begin(src), boost::fusion::end(src), dst);
  }

  template<class InB, class InE, class Value> BOOST_FORCEINLINE
  void check_all_equal(InB const& inb, InE const& inE, Value const& value);

  template<class InB, class InE, class Value> BOOST_FORCEINLINE
  void check_all_equal( InB const&, InE const&, Value const&
                      , boost::mpl::true_ const&
                      )
  {}

  template<class InB, class InE, class Value> BOOST_FORCEINLINE
  void check_all_equal( InB const& inb, InE const& inE, Value const& value
                      , boost::mpl::false_ const&
                      )
  {
    BOOST_ASSERT_MSG(Value(*inb) == value, "Incompatible size in of_size conversion");
    return details::check_all_equal(boost::fusion::next(inb), inE, value);
  }

  template<class InB, class InE, class Value> BOOST_FORCEINLINE
  void check_all_equal(InB const& inb, InE const& inE, Value const& value)
  {
    typename boost::fusion::result_of::equal_to<InB, InE>::type eq;
    return details::check_all_equal(inb, inE, value, eq);
  }

  template<class Src, class Value> BOOST_FORCEINLINE
  void check_all_equal(Src const& src, Value const& value)
  {
    details::check_all_equal(boost::fusion::begin(src), boost::fusion::end(src), value);
  }

  namespace result_of
  {
    template<class T, int Offset>
    struct pop_front_c
    {
      static const int seq_size = boost::fusion::result_of::size<T>::type::value;
      static const int min_size = (Offset < seq_size) ? Offset : seq_size;

      typedef typename  boost::fusion::result_of::
                        begin<T>::type                    begin;
      typedef typename  boost::fusion::result_of::
                        advance_c<begin, min_size>::type  begin2;
      typedef boost::fusion::
              iterator_range< begin2
                            , typename boost::fusion::result_of::end<T>::type
                            >                             type;
    };
  }

  template<int N, class T>
  typename result_of::pop_front_c<T const, N>::type
  pop_front_c(const T& t)
  {
    return typename result_of::pop_front_c<T const, N>::type
    ( boost::fusion::advance_c
      <result_of::pop_front_c<T const, N>::min_size>(boost::fusion::begin(t))
    , boost::fusion::end(t)
    );
  }

  namespace result_of
  {
    template<class T, int Offset>
    struct pop_back_c
    {
      static const int seq_size = boost::fusion::result_of::size<T>::type::value;
      static const int min_size = (Offset < seq_size) ? Offset : seq_size;

      typedef typename boost::fusion::result_of::end<T>::type       end;
      typedef typename  boost::fusion::
                        result_of::advance_c<end, -min_size>::type  end2;
      typedef boost::fusion::
              iterator_range< typename boost::fusion::result_of::begin<T>::type
                            , end2
                            >                                       type;
    };
  }

  template<int N, class T>
  typename result_of::pop_back_c<T const, N>::type
  pop_back_c(const T& t)
  {
    return typename result_of::pop_back_c<T const, N>::type
    (
      boost::fusion::begin(t)
    , boost::fusion::advance_c
      < -result_of::pop_back_c<T const, N>::min_size  >( boost::fusion::end(t) )
    );
  }

  template<typename A1, typename A2> BOOST_FORCEINLINE
  bool compare_equal(A1 const&, A2 const&, boost::mpl::size_t<0> const&)
  {
    return true;
  }

  template<typename A1, typename A2, std::size_t N> BOOST_FORCEINLINE
  bool compare_equal(A1 const& a1, A2 const& a2, boost::mpl::size_t<N> const&)
  {
    return (boost::fusion::at_c<N-1>(a1) == boost::fusion::at_c<N-1>(a2) )
        &&  compare_equal(a1,a2,boost::mpl::size_t<N-1>());
  }

  template<typename A1, typename A2> BOOST_FORCEINLINE
  bool compare_not_equal(A1 const&, A2 const&, boost::mpl::size_t<0> const&)
  {
    return false;
  }

  template<typename A1, typename A2, std::size_t N> BOOST_FORCEINLINE
  bool compare_not_equal(A1 const& a1, A2 const& a2, boost::mpl::size_t<N> const&)
  {
    return (boost::fusion::at_c<N-1>(a1) != boost::fusion::at_c<N-1>(a2) )
        ||  compare_not_equal(a1,a2,boost::mpl::size_t<N-1>());
  }
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_DEFINITELY_VECTOR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_IS_DEFINITELY_VECTOR_HPP_INCLUDED

#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/meta/safe_at.hpp>
#include <nt2/sdk/meta/tribool.hpp>
#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details
{
  template<class Seq>
  struct is_col_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool is_not = n < 1 || (n > 1 && meta::mpl_safe_at_c<typename Seq::values_type, 1, boost::mpl::long_<1> >::type::value != -1);
    typedef typename meta::indeterminate_false<!is_not>::type type;
  };

  template<std::ptrdiff_t N>
  struct is_col_vector< nt2::of_size_<N> >
       : meta::true_
  {
  };

  template<class Seq>
  struct is_row_vector
  {
    static const std::size_t n = Seq::static_size;
    static const bool is_not = n < 2 || (n > 2 && meta::mpl_safe_at_c<typename Seq::values_type, 2, boost::mpl::long_<1> >::type::value != -1);
    typedef typename meta::indeterminate_false<!is_not>::type type;
  };

  template<std::ptrdiff_t N>
  struct is_row_vector< nt2::of_size_<1, N> >
       : meta::true_
  {
  };

  template<class Seq>
  struct is_vector : meta::or_< is_col_vector<Seq>, is_row_vector<Seq> > {};

  template<class Seq>
  struct is_definitely_not_vector : boost::is_same<typename is_vector<Seq>::type, meta::false_> {};

  template<class Seq>
  struct is_definitely_vector : boost::is_same<typename is_vector<Seq>::type, meta::true_> {};

  template<class Seq>
  struct is_definitely_col_vector : boost::is_same<typename is_col_vector<Seq>::type, meta::true_> {};

  template<class Seq>
  struct is_definitely_row_vector : boost::is_same<typename is_row_vector<Seq>::type, meta::true_> {};
} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_GRIDS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_GRIDS_HPP_INCLUDED

#include <nt2/core/functions/meshgrid.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/putalong.hpp>
#include <nt2/include/functions/colvect.hpp>

namespace nt2 { namespace tag { struct meshgrid_; } }

namespace nt2 { namespace details
{
  // Prepare the data for the repetition in the grid
  template<int Dim, typename A0, typename Tag>
  BOOST_FORCEINLINE
  typename  meta::call< tag::putalong_
                                ( typename boost::proto::result_of
                                                       ::child_c<A0&,Dim>::type
                                , std::size_t
                                )
                      >::type
  values( A0& a0, Tag const& )
  {
    // meshgrid swap 0/1 dimension -- ask Mathworks
    static const std::size_t J  = (boost::is_same<Tag,tag::meshgrid_>::value)
                                ? !Dim ? 1 : (Dim==1 ? 0 : Dim)
                                : Dim;

    return putalong( boost::proto::child_c<Dim>(a0), J+1 );
  }

  // Iterate over the dimensions to generate grids for
  template<typename A0, typename A1, typename Tag, int N0, int N1>
  struct fill_grids
  {
    fill_grids(A0& a0, A1& a1) : a0_(a0), a1_(a1) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      eval<I>(boost::mpl::bool_<(N1 > I && N0 > I)>());
    }

    template<int I> BOOST_FORCEINLINE
    void eval(boost::mpl::true_ const&) const
    {
      boost::proto::child_c<I>(a1_) = expand_to ( values<I>(a0_,Tag() )
                                                , a0_.extent()
                                                );
    }

    template<int I> BOOST_FORCEINLINE
    void eval(boost::mpl::false_ const&) const {}

    private:
    A0& a0_;
    A1& a1_;
    fill_grids& operator=(fill_grids const&);
  };
} }

#endif

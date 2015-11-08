//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_IDX_LINEAR_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_IDX_LINEAR_HPP_INCLUDED

#include <nt2/interpol/functions/idx_linear.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/linear_interp.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/fusion/include/make_vector.hpp>
// #include <boost/assert.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::idx_linear_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type value_t;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type   idx_t;
    typedef typename value_t::value_type                              value_type;
    typedef typename meta::as_integer<value_type>::type               index_type;
    typedef typename A0::value_type                                    sale_type;
    typedef A0&                                                      result_type;
    typedef boost::fusion::vector<value_type, value_type>                 f_type;
    typedef typename A0::extent_type                                       ext_t;


    result_type operator()(A0& yi, A1& inputs) const
    {
      //      BOOST_ASSERT_MSG(are_sx_compatible(xi, y), "Inputs dimensions are not compatible");
      const idx_t & xi   =  boost::proto::child_c<1>(inputs);
      const value_t & y     =  boost::proto::child_c<0>(inputs);
      yi.resize(inputs.extent());
      bool extrap = false;
      std::size_t dim =nt2::firstnonsingleton(xi);
      value_type extrapval1 = Nan<value_type>();
      value_type extrapval2 = extrapval1;
      choices(inputs, extrap, extrapval1, extrapval2, dim, N1());
      ext_t sizee; sizee[0] = 1;
      sizee[dim-1] = numel(xi);
      const index_type il = nt2::last_index(y, dim);
      const value_type f = value_type(nt2::first_index(y, dim));
      const value_type l = value_type(il);
      table<value_type> index = nt2::min(nt2::max(f, nt2::floor(nt2::reshape(xi, sizee))), nt2::minusone(l));
      table<index_type> i_index = nt2::toint(index);
      table<value_type> dx    =  nt2::sx(nt2::tag::minus_(), nt2::reshape(xi, sizee), index);
      yi =  linear_interp(dx, nt2::along(y, i_index, dim), nt2::along(y, nt2::min(oneplus(i_index), il), dim));
      if (!extrap) {
        yi = nt2::sx(nt2::tag::if_else_(), nt2::reshape(boost::simd::is_nge(xi, value_type(f)), sizee),extrapval1, yi);
        yi = nt2::sx(nt2::tag::if_else_(), nt2::reshape(boost::simd::is_nle(xi, value_type(l)), sizee),extrapval2, yi);
      }
      return yi;
    }
  private :
    // Two inputs y and xi
    static void choices(const A1&, bool &,  value_type&, value_type& ,
                        std::size_t&, boost::mpl::long_<2> const &)  //nothing to get
      { }
    // Three inputs y and xi and a bool or a floating or a _ (meaning nothing here)
    static void choices(const A1& inputs,
                        bool & extrap, value_type& extrapval1, value_type& extrapval2,
                        std::size_t&, boost::mpl::long_<3> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval1, extrapval2, nt2::meta::as_<param_type>());
      }
    static void get(const A1& inputs, bool & extrap,
                    value_type&, value_type&, const nt2::meta::as_<bool> &) //get the bool
      {
        extrap =  boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval1, value_type& extrapval2,
                    const nt2::meta::as_<value_type> &)                     //get extrapval1,  compute extrapval2
      {
        extrapval1 =  extrapval2 = boost::proto::child_c<2>(inputs);
      }
//     static void get(const A1& inputs, bool &,  value_type& extrapval1, value_type& extrapval2,
//                     const nt2::meta::as_<f_type> &)                     //get extrapval1,  compute extrapval2
//       {
//         extrapval1 = boost::fusion::at_c<0>(boost::proto::child_c<2>(inputs));
//         extrapval2 = boost::fusion::at_c<1>(boost::proto::child_c<2>(inputs));
//       }
//     static void get(const A1& inputs, bool &,  value_type& extrapval1, value_type& extrapval2,
//                     const nt2::meta::as_<nt2::table<value_type> > &)                     //get extrapval1,  compute extrapval2
//       {
//         std::cout << "icitte" << std::endl;
//         std::cout << boost::proto::child_c<2>(inputs) << std::endl;
//         extrapval1 = boost::proto::child_c<2>(inputs)(begin_);
//         extrapval2 = boost::proto::child_c<2>(inputs)(begin_+1);
//       }
    static void get(const A1& , bool &, value_type&, value_type&,
                    const nt2::meta::as_<nt2::container::colon_> &)        //nothing to get
      {
      }
    // Four inputs y and xi and two floating or a _ and an integer
    static void choices(const A1& inputs,
                        bool &, value_type& extrapval1, value_type& extrapval2,
                        std::size_t& dim, boost::mpl::long_<4> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrapval1, extrapval2, dim,nt2::meta::as_<param_type>());
      }
    static void get(const A1& inputs, value_type& extrapval1, value_type& extrapval2, std::size_t&,
                    const nt2::meta::as_<value_type> &)          //get extrapval1 and extrapval2
      {
        extrapval1 = boost::proto::child_c<2>(inputs);
        extrapval2 = boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, value_type&, value_type&, std::size_t& dim,
                    const nt2::meta::as_<nt2::container::colon_> &)   //get dimension
      {
        dim =  boost::proto::child_c<3>(inputs);
      }
    // Five inputs y and xi, two floating  an integer
    static void choices(const A1& inputs,
                        bool & extrap, value_type& extrapval1, value_type& extrapval2,
                        std::size_t& dim, boost::mpl::long_<5> const &) //get extrapval1 and extrapval2 and dimension
      {
        dim =  boost::proto::child_c<4>(inputs);
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval1, extrapval2, dim, nt2::meta::as_<param_type>());
      }
    static void get(const A1& inputs, bool& extrap, value_type& , value_type&, std::size_t&,
                    const nt2::meta::as_<bool> &)          //get bool
      {
        extrap = boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool&, value_type& extrapval1, value_type& extrapval2 , std::size_t&,
                    const nt2::meta::as_<value_type> &)          //get two floating
      {
        extrapval1 = boost::proto::child_c<2>(inputs);
        extrapval2 = boost::proto::child_c<3>(inputs);
      }

  };
} }


#endif

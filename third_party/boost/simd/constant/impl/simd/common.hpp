//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_IMPL_SIMD_COMMON_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_IMPL_SIMD_COMMON_HPP_INCLUDED

#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/simd/tags.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/constant_value.hpp>
#include <boost/dispatch/attributes.hpp>

//==============================================================================
// Forward all constant call to the SIMD version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // By default we splat the constant contained into the extracted value from
  // the Tag over a given Target.
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( pure_constant_<Tag>, tag::cpu_
                                    , (Tag)(A0)
                                    , ((target_< scalar_< arithmetic_<A0> > >))
                                    )
  {
    typedef typename A0::type                                     base_type;
    typedef typename meta::constant_value<Tag, base_type>::type   mpl_type;
    typedef typename mpl_type::value_type                         result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return boost::simd::splat<result_type>( result_type(mpl_type()) );
    }
  };

  //============================================================================
  // In the SIMD case, if we generate an integral vector, we do a simple
  // splat from the Tag/Target bit pattern immediate, if not we add a bitwise
  // cast
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( pure_constant_<Tag>, tag::cpu_
                                    , (Tag)(A0)(X)
                                    , ((target_< simd_< arithmetic_<A0>,X> >))
                                    )
  {
    typedef typename A0::type                                     base_type;
    typedef typename meta::constant_value<Tag, base_type>::type   mpl_type;
    typedef typename mpl_type::value_type                         scalar_type;
    typedef typename meta::vector_of< scalar_type
                                    , meta::cardinal_of<base_type>::value
                                    >::type                       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      typedef typename dispatch::meta::
                       as_integer<scalar_type>::type              pattern_type;
      typedef boost::simd::native<pattern_type,X>                 tmp_type;

      return  bitwise_cast<result_type>
              ( boost::simd::
                splat<tmp_type>( pattern_type(mpl_type::value) )
              );
    }
  };
} } }

#endif

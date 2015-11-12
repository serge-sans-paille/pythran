//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_OPTION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_OPTION_HPP_INCLUDED

/*!
 * \file
 * \brief Defines NT2 container option base system
 **/

#include <boost/mpl/eval_if.hpp>
#include <nt2/core/settings/match_option.hpp>
#include <nt2/core/settings/details/no_semantic.hpp>

namespace nt2 { namespace meta
{
  /*!
   * @brief Extract an option value from a given type or type groups
   *
   * \tparam Settings Settings type to introspect
   * \tparam Option   Option tag to be retrieved
   * \tparam Semantic If no Option is found, use this semantic's guidelines
   **/
  template<class Settings, class Option, class Semantic = nt2::no_semantic_>
  struct  option
        : boost::mpl::eval_if < match_option<Settings,Option>
                              , typename Semantic::template option< Settings
                                                                  , Option
                                                                  >
                              , typename Semantic::template default_<Option>
                              >
  {};

  /// INTERNAL ONLY Forward option retrieval on S(*)(X) to S(X)
  template<class Settings, class Option, class Semantic>
  struct  option<Settings*,Option,Semantic>
        : option<Settings,Option,Semantic>
  {};

  /// INTERNAL ONLY Forward option retrieval for &
  template<class Settings, class Option, class Semantic>
  struct  option<Settings&,Option,Semantic>
        : option<Settings,Option,Semantic>
  {};

  /// INTERNAL ONLY Forward option retrieval for const
  template<class Settings, class Option, class Semantic>
  struct  option<Settings const,Option,Semantic>
        : option<Settings,Option,Semantic>
  {};
} }

#endif

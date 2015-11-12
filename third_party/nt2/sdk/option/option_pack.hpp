//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPTION_OPTION_PACK_HPP_INCLUDED
#define NT2_SDK_OPTION_OPTION_PACK_HPP_INCLUDED

#include <nt2/sdk/option/option_spec.hpp>
#include <nt2/sdk/option/option_not_found.hpp>

#include <boost/proto/transform/arg.hpp>
#include <boost/proto/matches.hpp>

namespace nt2 { namespace details
{
  struct option_pack
      : boost::proto::or_<
          boost::proto::when<
              boost::proto::comma<option_pack, option_spec>
            , boost::proto::if_<
                  boost::proto::matches < boost::proto::_left(boost::proto::_right)
                                        , boost::proto::_state
                                        >()
                , option_spec(boost::proto::_right)
                , option_pack(boost::proto::_left)
              >
          >
        , boost::proto::when<
              option_spec
            , boost::proto::if_<
                  boost::proto::matches < boost::proto::_left
                                        , boost::proto::_state
                                        >()
                , option_spec
                , option_not_found()
              >
          >
      >
  {};
} }

#endif

//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SETUP_REPEAT_HPP_INCLUDED
#define NT2_SDK_BENCH_SETUP_REPEAT_HPP_INCLUDED

#include <boost/fusion/include/vector.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace bench
{
  template<typename Repetition, typename Setup>
  struct repeat_
  {
    typedef boost::fusion::vector<Repetition,Setup> data_type;
    typedef boost::fusion::vector < typename Repetition::result_type
                                  , typename Setup::result_type
                                  > result_type;

    inline repeat_(Repetition const& r, Setup const& s) : steps_(r,s), base_(s)
    {}

    BOOST_FORCEINLINE result_type  operator()() const
    {
      return result_type( boost::fusion::at_c<0>(steps_)()
                        , boost::fusion::at_c<1>(steps_)()
                        );
    }

    BOOST_FORCEINLINE void step()
    {
      boost::fusion::at_c<1>(steps_).step();

      if(boost::fusion::at_c<1>(steps_).done())
      {
        boost::fusion::at_c<0>(steps_).step();
        if(!boost::fusion::at_c<0>(steps_).done())
          boost::fusion::at_c<1>(steps_) = base_;
      }
    }

    BOOST_FORCEINLINE bool done() const
    {
      return    boost::fusion::at_c<0>(steps_).done()
            &&  boost::fusion::at_c<1>(steps_).done();
    }

    private:
    data_type   steps_;
    Setup       base_;
  };

  template<typename Repetition, typename Setup>
  BOOST_FORCEINLINE repeat_<Repetition,Setup>
  repeat(Repetition const& r, Setup const& s)
  {
    return repeat_<Repetition,Setup>(r,s);
  }
} }

#endif

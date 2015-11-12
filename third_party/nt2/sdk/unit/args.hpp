//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_ARGS_HPP_INCLUDED
#define NT2_SDK_UNIT_ARGS_HPP_INCLUDED

#include <nt2/sdk/unit/config.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <map>

namespace nt2
{
  namespace details
  {
    // This string/string map contains the unprocessed name/value arguments
    extern NT2_TEST_UNIT_DECL std::map<std::string,std::string> args_map;

    // Fill the argument map from the command line contents
    void NT2_TEST_UNIT_DECL fill_args_map(int argc, char**argv);
  }

  namespace unit
  {
    /*!
      @brief Command line argument retrieval

      Benchmarks accept a variable number of optional values from the command
      line. Those value are passed using the -o markup followed by the name of
      the option and its value.

      args allows the retrieval of this value by name-lookup from within the
      benchmark code or, if the options requested is not present on the command
      line, returns a default value.

      When requested, the value is converted to the type of the potential
      default value. Upon error of conversion to requested type, the benchmark
      application will terminate with EXIT_FAILURE.

      @param  name  Name of option to be retrieved
      @param  d     Default value of the option

      @return A value of the same type than d.
    **/
    template<typename T> inline T args(std::string const& name, T d)
    {
      T value(d);

      std::map<std::string,std::string>::iterator
      it = details::args_map.find(name);

      if(it != details::args_map.end())
      {
        std::istringstream ss(it->second);
        ss >> value >> std::ws;

        if( ss.fail() || !ss.eof() )
        {
          std::cerr << "Invalid option format for option "
                    << it->first << " : " << it->second
                    << "\n";

          std::exit(EXIT_FAILURE);
        }
      }

      return value;
    }
  }
}

#endif

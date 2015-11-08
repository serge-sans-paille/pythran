//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DISPLAY_TYPE_HPP_INCLUDED
#define NT2_SDK_META_DISPLAY_TYPE_HPP_INCLUDED

/**
* @file
* @brief Defines types to string conversion utility functions
**/
#include <nt2/sdk/meta/type_id.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <iostream>

namespace nt2
{
  namespace details
  {
    // INTERNAL ONLY
    // Stream some indentation on a output stream
    inline std::ostream& indent(std::ostream& os, size_t depth)
    {
      for(size_t i=0; i<depth; ++i)
        os << ' ';

      return os;
    }
  }

  /**
  *
  * @brief Type name streaming function
  *
  * For any given type @c T, displays a human readable string containing the fully
  * qualified name of @c T on the standard output. Formatting is applied on this
  * output so template types and other complex structures are properly displayed.
  *
  * @tparam T   Type to display
  *
  * @usage
  * @include display_type.cpp
  *
  * This examples outpus:
  *
  * @code
  * char [21]
  * float
  * std::vector<
  *     long*
  *   , std::allocator<
  *         long*
  *     >
  * >
  * @endcode
  **/
  template<typename T> inline void display_type()
  {
    std::string s = type_id<T>();

    size_t depth = 0;
    size_t tab   = 4;
    bool prevspace = true;
    for(std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
      switch(*it)
      {
        case '<':
        case '(':
          depth += tab;
          std::cout << *it;
          std::cout << '\n';
          details::indent(std::cout, depth);
          prevspace = true;
          break;

        case '>':
        case ')':
          depth -= tab;
          std::cout << '\n';
          details::indent(std::cout, depth);
          std::cout << *it;
          prevspace = false;
          break;

        case ',':
          std::cout << '\n';
          details::indent(std::cout, depth-2);
          std::cout << ", ";
          prevspace = true;
          break;

        case ' ':
          if(!prevspace)
            std::cout << *it;
          break;

        default:
          std::cout << *it;
          prevspace = false;
      }
    }
    std::cout << std::endl;
  }

  /// @overload
  template<typename T> inline void display_type( const T& )
  {
    return display_type<T>();
  }
}

#endif

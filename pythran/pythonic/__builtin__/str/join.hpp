#ifndef PYTHONIC_STR_JOIN_HPP
#define PYTHONIC_STR_JOIN_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/__builtin__/len.hpp"

namespace pythonic { namespace __builtin__  {

    namespace str {
        // specialization for str.join(str)
        template <class S>
        types::str
        join(S const &s, types::str const& iterable) {
          long ssize = std::distance(std::begin(s), std::end(s)) - (std::is_same<S, types::str>::value ? 0 : 1);
          /* first iterate over iterable to gather sizes */
          size_t n = ssize * (iterable.size() - 1) + iterable.size();

          std::string out(n, 0);

          auto iter = iterable.begin();
          auto oter = out.begin();
          if (iter != iterable.end()) {
            *oter++ = *iter++;
            if (ssize)
              for (; iter != iterable.end(); ++iter) {
                oter = std::copy(std::begin(s), std::begin(s) + ssize, oter);
                *oter++ = *iter;
              }
            else
              return iterable;
          }
          return {std::move(out)};
        }

        // specialization when the iterable is a random access iterator
        template <class S, class Iterable>
        typename std::enable_if<
            not std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, types::str>::value and
            std::is_same<typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category, std::random_access_iterator_tag>::value,
            types::str
        >::type
        join(S const &s, Iterable &&iterable) {
          long ssize = std::distance(std::begin(s), std::end(s)) - (std::is_same<S, types::str>::value ? 0 : 1);
          /* first iterate over iterable to gather sizes */
          long iterable_size = std::distance(iterable.begin(), iterable.end());
          if(iterable_size == 0)
            return "";
          size_t n = ssize * (iterable_size - 1);
          for (auto const &iter : iterable)
            n += __builtin__::len(iter);

          std::string out(n, 0);

          auto iter = iterable.begin();
          auto oter = out.begin();
          if (iter != iterable.end()) {
            auto tmp = *iter;
            oter = std::copy(tmp.begin(), tmp.end(), oter);
            ++iter;
            if (ssize)
              for (; iter != iterable.end(); ++iter) {
                oter = std::copy(std::begin(s), std::begin(s) + ssize, oter);
                auto tmp = *iter;
                oter = std::copy(tmp.begin(), tmp.end(), oter);
              }
            else
              for (; iter != iterable.end(); ++iter) {
                auto tmp = *iter;
                oter = std::copy(tmp.begin(), tmp.end(), oter);
              }
          }
          return std::move(out);
        }

        // default implementation
        template<class S, class Iterable>
            typename std::enable_if<
            not std::is_same<
            typename std::iterator_traits<typename std::remove_reference<Iterable>::type::iterator>::iterator_category,
                     std::random_access_iterator_tag
                         > :: value,
                     types::str
                         >::type
          join(S const &s, Iterable &&iterable) {
            types::str out;
            auto iter = iterable.begin();
            if (iter != iterable.end()) {
              out += *iter;
              ++iter;
              for (; iter != iterable.end(); ++iter) {
                out += s;
                out += *iter;
              }
            }
            return out;
          }
        PROXY(pythonic::__builtin__::str, join);

    }

}

}
#endif


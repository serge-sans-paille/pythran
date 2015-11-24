#ifndef PYTHONIC_NUMPY_INTERSECT1D_HPP
#define PYTHONIC_NUMPY_INTERSECT1D_HPP

#include "pythonic/include/numpy/intersect1d.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/combined.hpp"
#include "pythonic/numpy/asarray.hpp"

#include <algorithm>
#include <set>

namespace pythonic
{

  namespace numpy
  {
    template <class E, class F>
    types::ndarray<
        typename __combined<typename E::dtype, typename F::dtype>::type, 1>
    intersect1d(E const &e, F const &f)
    {
      using T = typename __combined<typename E::dtype, typename F::dtype>::type;
      auto ae = asarray(e);
      auto af = asarray(f);
      std::set<T> sae(ae.fbegin(), ae.fend());
      std::set<T> found;
      types::list<T> lout(0);
      lout.reserve(sae.size());
      for (auto iter = af.fbegin(), end = af.fend(); iter != end; ++iter) {
        auto curr = *iter;
        if (sae.find(curr) != sae.end() and found.find(curr) == found.end()) {
          found.insert(curr);
          lout.push_back(curr);
        }
      }
      std::sort(lout.begin(), lout.end());
      return types::ndarray<T, 1>(lout);
    }

    DEFINE_FUNCTOR(pythonic::numpy, intersect1d);
  }
}

#endif

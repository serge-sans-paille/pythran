#ifndef PYTHONIC_NUMPY_UNIQUE_HPP
#define PYTHONIC_NUMPY_UNIQUE_HPP

#include "pythonic/include/numpy/unique.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/tuple.hpp"

#include <set>
#include <map>

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace
  {
    template <class I, class O>
    void _unique1(I begin, I end, O &out, utils::int_<1>)
    {
      out.insert(begin, end);
    }

    template <class I, class O, size_t N>
    void _unique1(I begin, I end, O &out, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _unique1((*begin).begin(), (*begin).end(), out, utils::int_<N - 1>());
    }

    template <class I, class O0, class O1>
    void _unique2(I begin, I end, O0 &out0, O1 &out1, long &i, utils::int_<1>)
    {
      for (; begin != end; ++begin, ++i) {
        auto pair = out0.insert(*begin);
        if (pair.second)
          out1.push_back(i);
      }
    }

    template <class I, class O0, class O1, size_t N>
    void _unique2(I begin, I end, O0 &out0, O1 &out1, long &i, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _unique2((*begin).begin(), (*begin).end(), out0, out1, i,
                 utils::int_<N - 1>());
    }
    template <class I, class O0, class O1, class O2>
    void _unique3(I begin, I end, O0 &out0, O1 &out1, O2 &out2, long &i,
                  utils::int_<1>)
    {
      for (; begin != end; ++begin, ++i) {
        auto pair = out0.insert(*begin);
        out2[i] = std::distance(out0.begin(), pair.first);
        if (pair.second)
          out1.push_back(i);
      }
    }
    template <class I, class O0, class O1, class O2, size_t N>
    void _unique3(I begin, I end, O0 &out0, O1 &out1, O2 &out2, long &i,
                  utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _unique3((*begin).begin(), (*begin).end(), out0, out1, out2, i,
                 utils::int_<N - 1>());
    }

    template <class I, class O1, class O2, class O3>
    void _unique4(I begin, I end, O1 &out1, O2 &out2, O3 &out3, long &i,
                  utils::int_<1>)
    {
      for (; begin != end; ++begin, ++i) {
        auto res = out3.insert(std::make_pair(*begin, 0));
        res.first->second += 1;
        out2[i] = std::distance(out3.begin(), res.first);
        if (res.second) {
          out1.push_back(i);
        }
      }
    }
    template <class I, class O1, class O2, class O3, size_t N>
    void _unique4(I begin, I end, O1 &out1, O2 &out2, O3 &out3, long &i,
                  utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _unique4((*begin).begin(), (*begin).end(), out1, out2, out3, i,
                 utils::int_<N - 1>());
    }
  }
  template <class E>
  types::ndarray<typename E::dtype, types::pshape<long>> unique(E const &expr)
  {
    std::set<typename E::dtype> res;
    _unique1(expr.begin(), expr.end(), res, utils::int_<E::value>());
    return {res};
  }

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, bool return_index)
  {
    std::set<typename E::dtype> res;
    std::vector<long> return_index_res;
    long i = 0;
    _unique2(expr.begin(), expr.end(), res, return_index_res, i,
             utils::int_<E::value>());
    return std::make_tuple(
        types::ndarray<typename E::dtype, types::pshape<long>>(res),
        types::ndarray<long, types::pshape<long>>(return_index_res));
  }

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, bool return_index, bool return_inverse)
  {
    assert(return_inverse && "invalid signature otherwise");

    std::set<typename E::dtype> res;
    std::vector<long> return_index_res;
    types::ndarray<long, types::pshape<long>> return_inverse_res(
        types::pshape<long>{expr.flat_size()}, __builtin__::None);
    long i = 0;
    _unique3(expr.begin(), expr.end(), res, return_index_res,
             return_inverse_res, i, utils::int_<E::value>());
    return std::make_tuple(
        types::ndarray<typename E::dtype, types::pshape<long>>(res),
        types::ndarray<long, types::pshape<long>>(return_index_res),
        return_inverse_res);
  }

  template <class E>
  std::tuple<types::ndarray<typename E::dtype, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>,
             types::ndarray<long, types::pshape<long>>>
  unique(E const &expr, bool return_index, bool return_inverse,
         bool return_counts)
  {
    assert(return_counts && "invalid signature otherwise");

    std::vector<long> return_index_res;
    types::ndarray<long, types::pshape<long>> return_inverse_res(
        types::pshape<long>{expr.flat_size()}, __builtin__::None);

    std::map<typename E::dtype, long> return_counts_map;
    {
      long i = 0;
      _unique4(expr.begin(), expr.end(), return_index_res, return_inverse_res,
               return_counts_map, i, utils::int_<E::value>());
    }

    types::pshape<long> shp{(long)return_counts_map.size()};

    types::ndarray<long, types::pshape<long>> unique_array(shp,
                                                           __builtin__::None);
    types::ndarray<long, types::pshape<long>> return_counts_array(
        shp, __builtin__::None);

    {
      long i = 0;
      for (auto it = return_counts_map.begin(); it != return_counts_map.end();
           ++i, ++it) {
        unique_array.fast(i) = it->first;
        return_counts_array.fast(i) = it->second;
      }
    }

    return std::make_tuple(
        unique_array,
        types::ndarray<long, types::pshape<long>>(return_index_res),
        return_inverse_res, return_counts_array);
  }

  DEFINE_FUNCTOR(pythonic::numpy, unique)
}
PYTHONIC_NS_END

#endif

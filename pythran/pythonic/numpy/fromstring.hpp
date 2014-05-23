#ifndef PYTHONIC_NUMPY_FROMSTRING_HPP
#define PYTHONIC_NUMPY_FROMSTRING_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/list.hpp"

#include <limits>
#include <sstream>

namespace pythonic {

    namespace numpy {
        template<class dtype=double>
            types::ndarray<typename types::numpy_type<dtype>::type,1> fromstring(types::str const& string, dtype d=dtype(), long count = -1 , types::str const& sep = "") {
                if(sep) {
                    types::list<typename types::numpy_type<dtype>::type> res(0);
                    if(count<0) count = std::numeric_limits<long>::max();
                    else res.reserve(count);
                    size_t current;
                    size_t next = -1;
                    long numsplit = 0;
                    do {
                        current = next + 1;
                        next = string.find_first_of( sep, current );
                        typename types::numpy_type<dtype>::type item;
                        std::istringstream iss(string.substr( current, next - current ).get_data());
                        iss >> item;
                        res.push_back(item);
                    }
                    while (next != types::str::npos && ++numsplit<count);
                    return types::ndarray<typename types::numpy_type<dtype>::type, 1>(res);
                }
                else {
                    if(count <0) count = string.size();
                    long shape[1] = { count };
                    typename types::numpy_type<dtype>::type* buffer = (typename types::numpy_type<dtype>::type*)malloc(shape[0] * sizeof(typename types::numpy_type<dtype>::type));
                    typename types::numpy_type<dtype>::type const* tstring = reinterpret_cast<typename types::numpy_type<dtype>::type const*>(string.c_str());
                    std::copy(tstring, tstring + shape[0], buffer);
                    return types::ndarray<typename types::numpy_type<dtype>::type,1>(buffer, shape);
                }
            }

        PROXY(pythonic::numpy, fromstring);

    }

}

#endif


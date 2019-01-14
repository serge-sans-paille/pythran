#ifndef PYTHONIC_NUMPY_INTERP_HPP
#define PYTHONIC_NUMPY_INTERP_HPP

#include "pythonic/include/numpy/interp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include <math.h>

PYTHONIC_NS_BEGIN

namespace numpy
{

    template <class T1, class T2, class T3, typename t1, typename t2, typename t3>
    T3 interp(T1 x, T2 xp, T3 fp, t1 left, t2 right, t3 period){

        assert(std::get<0>(xp.shape())==std::get<0>(fp.shape()));
        //long nPoints = sutils::array(xp.shape())[0];
        long nPoints = std::get<0>(x.shape());
        long nPointsXP = std::get<0>(xp.shape());
        typename T3::dtype foo1(0);
        printf("INTERP %d points %f\n",nPoints,foo1);

        T3 out = {x.shape(), foo1};

        for (long i=0; i<nPoints; i++) {
            float xx = x[i];
            long j=0;
            while(j<nPointsXP-1 && xp[j+1] < xx) j++;
            if (xp[j]>xx)
                out[i] = left;
            else if (xp[j+1]<xx)
                out[i] = right;
            else
                out[i] = fp[j] + (xx-xp[j]) * (fp[j+1]-fp[j])/(xp[j+1]-xp[j]);

        }
        
        return out;
    }

    template <class T1, class T2, class T3>
    T3 interp(T1 x, T2 xp, T3 fp, types::none_type left, types::none_type right, types::none_type period){
        auto _left = fp[0];
        auto _right = fp[-1];
        return interp(x, xp, fp, _left, _right, 0);
    }

    // left specified
    template <class T1, class T2, class T3, typename t1>
    T3 interp(T1 x, T2 xp, T3 fp, t1 left, types::none_type right, types::none_type period){
        auto _right = fp[-1];
        return interp(x, xp, fp, left, _right, 0);
    }
    // right specified
    template <class T1, class T2, class T3, typename t1>
    T3 interp(T1 x, T2 xp, T3 fp, types::none_type left, t1 right, types::none_type period){
        auto _left = fp[0];
        return interp(x, xp, fp, _left, right, 0);
    }
    // period specified
    template <class T1, class T2, class T3, typename t1>
    T3 interp(T1 x, T2 xp, T3 fp, types::none_type left, types::none_type right, t1 period){
        assert(period != 0);
        return interp(x, xp, fp, 0, 0, period);
    }

    // left and right specified
    template <class T1, class T2, class T3, typename t1, typename t2>
    T3 interp(T1 x, T2 xp, T3 fp, t1 left, t2 right, types::none_type period){
        return interp(x, xp, fp, left, right, 0);
    }


  NUMPY_EXPR_TO_NDARRAY0_IMPL(interp);
}
PYTHONIC_NS_END

#endif

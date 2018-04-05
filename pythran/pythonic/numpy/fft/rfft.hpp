#ifndef PYTHONIC_NUMPY_FFT_RFFT_HPP
#define PYTHONIC_NUMPY_FFT_RFFT_HPP

#include "pythonic/include/numpy/fft/rfft.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/include/utils/array_helper.hpp"
#include <array>
#include <map>
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/__builtin__/ValueError.hpp"
#include "pythonic/numpy/swapaxes.hpp"
#include <string.h>
#include <math.h>
#include <vector>

#include <stdio.h>
#include "pythonic/numpy/fft/fftpack.c"


PYTHONIC_NS_BEGIN

namespace numpy
{
    namespace fft
    {
        // Aux function
        template<class T, size_t N>
        types::ndarray<std::complex<typename std::common_type<T, double>::type>, N> _rfft(types::ndarray<T, N> const &in_array, long NFFT, bool norm)
        {
            long i;
            auto shape = in_array.shape();
            T* dptr = (T*)in_array.buffer;
            long npts = shape.back();
            
            // Create output array.
            long out_size = NFFT/2+1;
            auto out_shape = shape;
            out_shape.back() = out_size;
            types::ndarray<std::complex<typename std::common_type<T, double>::type>, N> out_array(out_shape,__builtin__::None);
            
//            printf("Shape %d %d N = %d -- Flat size: %d NFFT = %d npts = %d out_size %d\n",
//                   shape[0],shape[1],N,in_array.flat_size(),NFFT,npts,out_size);
//            for (i = 0; i < NFFT; i++)
//                printf("in: %.4f\n",dptr[i]);
            
            // Create the twiddle factors. These must be kept from call to call as it's very wasteful to recompute them.
            // This is from fftpack_litemodule.c
            static std::map<long, types::ndarray<double, 1>> all_twiddles;
            if (all_twiddles.find(NFFT) == all_twiddles.end()) {
//                printf("CREATING TWIDDLE FOR %d\n",NFFT);
                types::array<long, 1> twiddle_shape = {(long)(2*NFFT+15)};
                // Insert a new twiddle array into our map
                all_twiddles.insert(std::make_pair(NFFT,types::ndarray<double, 1>(twiddle_shape,__builtin__::None)));
                // Then initialize it.
                npy_rffti(NFFT, (double *)all_twiddles[NFFT].buffer);
            }
            else {
                //printf("RECALLING TWIDDLE FOR %d\n",NFFT);
            }
            
            // Call fft (fftpack.py) r = work_function(in_array, wsave)
            // This is translated from https://raw.githubusercontent.com/numpy/numpy/master/numpy/fft/fftpack_litemodule.c
            
            double* rptr            = (double*) out_array.buffer;
            double* twiddle_buffer  = (double*) all_twiddles[NFFT].buffer;
            long nrepeats           = in_array.flat_size()/npts;
            long to_copy            = (NFFT <= npts) ? NFFT : npts;
            for (i = 0; i < nrepeats; i++) {
                rptr[2*out_size-1] = 0.0; // We didn't zero the array upon allocation. Make sure the last element is 0.
                std::copy(dptr,dptr+to_copy,rptr+1);
                // Zero padding if the FFT size is > the number points
                memset((char *)(rptr+1+to_copy),0,(NFFT-to_copy)*sizeof(double));
                npy_rfftf(NFFT, rptr+1, twiddle_buffer);
                rptr[0] = rptr[1];
                rptr[1] = 0.0;
                rptr += 2*out_size;
                dptr += npts;
            }
            if(norm) {
                double scale = 1. / sqrt(NFFT);
                rptr = (double*)out_array.buffer;
                long count = 2*out_array.flat_size();
                // Remember that these are complex numbers!
                for (i=0;i<count;i++){
                    rptr[i] *= scale;
                }
            }
            
//            for (i = 0; i < out_size; i++) {
//                printf("out_array: %.4f %.4f\n",out_array[i].real(),out_array[i].imag());
//            }
            return out_array;
        }
        
        template<class T, size_t N>
        types::ndarray<std::complex<typename std::common_type<T, double>::type>, N> rfft(types::ndarray<T, N> const &in_array, long NFFT, long axis)
        {
            return rfft(in_array,NFFT,axis,"");
        }

        // This is kludgy, and I'm sure there's a better way to do this. Jeanl
        bool testThis(types::none_type param) { return false;}
        bool testThis(types::str param) { return param=="ortho";}
        
        template<class T, size_t N, typename U>
        types::ndarray<std::complex<typename std::common_type<T, double>::type>, N> rfft(types::ndarray<T, N> const &in_array, long NFFT, long axis, U normalize)
        {
            bool norm = testThis(normalize);
//            printf("NORMALIZE = %s!\n",norm?"TRUE":"FALSE");

            if(NFFT == -1) NFFT = in_array.shape().back();
            if(axis != -1 && axis != N-1) {
                // Swap axis if the FFT must be computed on an axis that's not the last one.
                auto swapped_array = swapaxes(in_array, axis, N-1);
                return swapaxes(_rfft(swapped_array,NFFT,norm),axis,N-1);
            }
            else{
                return _rfft(in_array,NFFT,norm);
            }
        }

        NUMPY_EXPR_TO_NDARRAY0_IMPL(rfft);
        DEFINE_FUNCTOR(pythonic::numpy::fft, rfft);
    }
}
PYTHONIC_NS_END

#endif

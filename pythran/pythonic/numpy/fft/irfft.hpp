#ifndef PYTHONIC_NUMPY_FFT_IRFFT_HPP
#define PYTHONIC_NUMPY_FFT_IRFFT_HPP

#include "pythonic/include/numpy/fft/irfft.hpp"
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


#include <stdio.h>
#include "pythonic/numpy/fft/fftpack.c"


PYTHONIC_NS_BEGIN

namespace numpy
{
    namespace fft
    {
        
        // Aux function
        template<class T, size_t N>
        types::ndarray<double, N> _irfft(types::ndarray<T, N> const &in_array, long NFFT, bool norm)
        {
            long i;
            auto shape = in_array.shape();
            long npts = shape.back();
            // Create output array.
            long out_size = NFFT;
            auto out_shape = shape;
            out_shape.back() = out_size;
            types::ndarray<double, N> out_array(out_shape,__builtin__::None);
            
            // Create the twiddle factors. These must be kept from call to call as it's very wasteful to recompute them.
            // This is from fftpack_litemodule.c
            static std::map<long, types::ndarray<double, 1>> all_twiddles;
            if (all_twiddles.find(NFFT) == all_twiddles.end()) {
                types::array<long, 1> twiddle_shape = {(long)(2*NFFT+15)};
                // Insert a new twiddle array into our map
                all_twiddles.insert(std::make_pair(NFFT,types::ndarray<double, 1>(twiddle_shape,__builtin__::None)));
                // Then initialize it.
                npy_rffti(NFFT, (double *)all_twiddles[NFFT].buffer);
            }
            
            // Call fft (fftpack.py) r = work_function(in_array, wsave)
            // This is translated from https://raw.githubusercontent.com/numpy/numpy/master/numpy/fft/fftpack_litemodule.c
            
            double* rptr            = (double*) out_array.buffer;
            double* twiddle_buffer  = (double*) all_twiddles[NFFT].buffer;
            typename T::value_type* dptr =  (typename T::value_type*) in_array.buffer;
            long nrepeats           = out_array.flat_size()/out_size;
            long to_copy            = (NFFT/2+1 <= npts) ? (NFFT-1) : (2*npts-2);
            for (i = 0; i < nrepeats; i++) {
                // By default npts = floor(NFFT/2)+1.
                if(std::is_same<std::complex<double>, T>::value) {
                    memcpy((char *)(rptr+1), (dptr+2), to_copy*sizeof(double));
                }
                else {
                    for (int j=0; j<to_copy; j++)
                        rptr[j+1]=dptr[j+2];
               }
                rptr[0]=dptr[0];
                // Zero padding if necessary
                memset((char *)(rptr+1+to_copy),0,(NFFT-1-to_copy)*sizeof(double));
                npy_rfftb(NFFT, rptr, twiddle_buffer);
                rptr += out_size;
                dptr += 2*npts;     // These are comlex numbers.
            }
            
            double scale = (norm)? 1. / sqrt(NFFT) : 1./NFFT;
            rptr = (double*)out_array.buffer;
            long count = out_array.flat_size();
            for (i=0;i<count;i++){
                rptr[i] *= scale;
            }

            return out_array;
        }
        
        
        template<class T, size_t N>
        types::ndarray<double, N> irfft(types::ndarray<T,N> const &in_array, long NFFT, long axis, types::str normalize)
        {
            bool norm = (normalize == "ortho");
            if(NFFT == -1) NFFT = 2*(in_array.shape().back()-1);
            if(axis != -1 && axis != N-1) {
                // Swap axis if the FFT must be computed on an axis that's not the last one.
                auto swapped_array = swapaxes(in_array, axis, N-1);
                return swapaxes(_irfft(swapped_array,NFFT,norm),axis,N-1);
            }
            else{
                return _irfft(in_array,NFFT,norm);
            }
        }

        
        NUMPY_EXPR_TO_NDARRAY0_IMPL(irfft);
        DEFINE_FUNCTOR(pythonic::numpy::fft, irfft);
    }
}
PYTHONIC_NS_END

#endif

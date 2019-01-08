#ifndef PYTHONIC_NUMPY_STACK_HPP
#define PYTHONIC_NUMPY_STACK_HPP

#include <pythonic/include/numpy/stack.hpp>
#include <pythonic/numpy/concatenate.hpp>

PYTHONIC_NS_BEGIN

namespace numpy
{

    template <class E>
    types::ndarray<typename E::dtype, types::array<long, E::value+1>>
    stack(types::list<E> const &args, long axis)
    {
        int i;
        auto shape = args[0].shape();
        const int N = std::tuple_size<decltype(shape)>::value;  // The length of the shape array.
        auto values = shape.array();                            // You can't do shape[i] but you can do shape.array()[i]
        // sutils::array(shape); would have worked too
        std::array<long,N+1> dim_array;                         // A new array that's 1 element longer than shape.
        // Insert a "0" at the position indicated by axis.
        for(i=0;i<N+1;i++) {
            if(i<axis) dim_array[i] = values[i];
            if(i==axis) dim_array[i] = 1;
            if(i>axis) dim_array[i] = values[i-1];
        }
        // Create a new pshape with the right length
        sutils::push_front_t<decltype(shape), long> new_shape;
        // Assign the values array to a tuple created from dim_array. I'm sure there's a shortcut for these two operations.
        new_shape.values = types::make_tuple(dim_array);
      
        // Create a new empty list.
        types::list<types::ndarray<typename E::dtype, types::array<long, E::value+1>>> bi(0);
        // Push the resized arrays into the list.
        for (i=0;i<args.size();i++) {
            bi.push_back(args[i].reshape(new_shape));
        }
        // Call concatenate on this list.
        return concatenate(bi,axis);
    }

}
PYTHONIC_NS_END

#endif

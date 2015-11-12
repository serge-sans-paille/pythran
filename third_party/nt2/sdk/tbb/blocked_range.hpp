//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_BLOCKED_RANGE_HPP_INCLUDED
#define NT2_SDK_TBB_BLOCKED_RANGE_HPP_INCLUDED

#include <tbb/tbb_stddef.h>

namespace nt2 {

template<typename Value>
class blocked_range {
public:
    //! Type of a value
    /** Called a const_iterator for sake of algorithms that need to treat a blocked_range
        as an STL container. */
    typedef Value const_iterator;

    //! Type for size of a range
    typedef std::size_t size_type;

    //! Construct range with default-constructed values for begin and end.
    /** Requires that Value have a default constructor. */
    blocked_range() : my_end(), my_begin() {}

    //! Construct range over half-open interval [begin,end), with the given grainsize.
    blocked_range( Value begin_, Value end_, size_type grainsize_=1 ) :
        my_end(end_), my_begin(begin_), my_grainsize(grainsize_)
    {}

    //! Beginning of range.
    const_iterator begin() const {return my_begin;}

    //! One past last value in range.
    const_iterator end() const {return my_end;}

    //! Size of the range
    /** Unspecified if end()<begin(). */
    size_type size() const {
        return size_type(my_end-my_begin);
    }

    //! The grain size for this range.
    size_type grainsize() const {return my_grainsize;}

    //------------------------------------------------------------------------
    // Methods that implement Range concept
    //------------------------------------------------------------------------

    //! True if range is empty.
    bool empty() const {return !(my_begin<my_end);}

    //! True if range is divisible.
    /** Unspecified if end()<begin(). */
    bool is_divisible() const {
        return ( size() >= (2*my_grainsize) );
    }

    //! Split range.
    /** The new Range *this has the second half, the old range r has the first half.
        Unspecified if end()<begin() or !is_divisible(). */
    blocked_range( blocked_range& r, tbb::split ) :
        my_end(r.my_end),
        my_begin(do_split(r)),
        my_grainsize(r.my_grainsize)
    {}

private:
    /** NOTE: my_end MUST be declared before my_begin, otherwise the forking constructor will break. */
    Value my_end;
    Value my_begin;
    size_type my_grainsize;

    //! Auxiliary function used by forking constructor.
    /** Using this function lets us not require that Value support assignment or default construction. */
    static Value do_split( blocked_range& r ) {
        Value middle = r.my_begin + ((r.my_end-r.my_begin)/(2*r.my_grainsize))*r.my_grainsize;
        r.my_end = middle;
        return middle;
    }

};

} // namespace nt2

#endif

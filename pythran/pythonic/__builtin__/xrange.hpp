#ifndef PYTHONIC_BUILTIN_XRANGE_HPP
#define PYTHONIC_BUILTIN_XRANGE_HPP

#include <iterator>

namespace pythonic {

    namespace __builtin__ {

        struct xrange_iterator : std::iterator< std::random_access_iterator_tag, long, ptrdiff_t, long*, long/*no ref here*/ >{
            long value;
            long step;
            long sign;
            xrange_iterator() {}
            xrange_iterator(long v, long s) : value(v), step(s), sign(s<0?-1:1) {}
            reference operator*() const { return value; }
            xrange_iterator& operator++() { value+=step; return *this; }
            xrange_iterator operator++(int) { xrange_iterator self(*this); value+=step; return self; }
            xrange_iterator& operator+=(long n) { value+=step*n; return *this; }
            bool operator!=(xrange_iterator const& other) const { return value != other.value; }
            bool operator==(xrange_iterator const& other) const { return value == other.value; }
            bool operator<(xrange_iterator const& other) const { return sign*value < sign*other.value; }
            long operator-(xrange_iterator const& other) const { return (value - other.value)/step; }
        };
        struct xrange_riterator : std::iterator< std::random_access_iterator_tag, long, ptrdiff_t, long*, long/*no ref here*/ >{
            long value;
            long step;
            long sign;
            xrange_riterator() {}
            xrange_riterator(long v, long s) : value(v), step(s), sign(s<0?1:-1) {}
            long operator*() { return value; }
            xrange_riterator& operator++() { value+=step; return *this; }
            xrange_riterator operator++(int) { xrange_riterator self(*this); value+=step; return self; }
            xrange_riterator& operator+=(long n) { value+=step*n; return *this; }
            bool operator!=(xrange_riterator const& other) const { return value != other.value; }
            bool operator==(xrange_riterator const& other) const { return value == other.value; }
            bool operator<(xrange_riterator const& other) const { return sign*value > sign*other.value; }
            long operator-(xrange_riterator const& other) const { return (value - other.value)/step; }
        };

        struct xrange {
            long _begin;
            long _end;
            long _step;
            long _last;
            typedef long value_type;
            typedef xrange_iterator iterator;
            typedef xrange_iterator const_iterator;
            typedef xrange_riterator reverse_iterator;
            typedef xrange_riterator const_reverse_iterator;
            void _init_last() {
                if(_step>0) _last= _begin + std::max(0L,_step * ( (_end - _begin + _step -1)/ _step));
                else _last= _begin + std::min(0L,_step * ( (_end - _begin + _step +1)/ _step)) ;
            }
            xrange(){}
            xrange( long b, long e , long s=1) : _begin(b), _end(e), _step(s) { _init_last(); }
            xrange( long e ) : _begin(0), _end(e), _step(1) { _init_last(); }
            xrange_iterator begin() const { return xrange_iterator(_begin, _step); }
            xrange_iterator end() const { return xrange_iterator(_last, _step); }
            reverse_iterator rbegin() const { return reverse_iterator(_last - _step, -_step); }
            reverse_iterator rend() const { return reverse_iterator(_begin - _step, -_step) ;}
        };

        // clang++ is not happy with PROXY
        namespace proxy {
            struct xrange {
                template<class... Types>
                    pythonic::__builtin__::xrange operator()(Types &&... args) {
                        return pythonic::__builtin__::xrange(std::forward<Types>(args)...);
                    }
            };
        }


    }

}
#endif


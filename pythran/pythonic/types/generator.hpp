#ifndef PYTHONIC_TYPES_GENERATOR_HPP
#define PYTHONIC_TYPES_GENERATOR_HPP

#include "pythonic/types/exceptions.hpp"
#include <iterator>

namespace pythonic {

    namespace types {
        template <class T>
            struct generator_iterator : std::iterator<std::forward_iterator_tag, typename T::result_type, ptrdiff_t, typename T::result_type*, typename T::result_type /* no ref */>
        {

            T the_generator;
            generator_iterator() : the_generator() { the_generator.__generator_state = -1 ;} // this represents the end
            generator_iterator(T const& a_generator) : the_generator(a_generator) {
            }
            generator_iterator& operator++() {
                try { the_generator.next(); }
                catch(types::StopIteration const&) {
                    the_generator.__generator_state = -1;
                }
                return *this;
            }
            typename T::result_type operator*() const {
                return *the_generator;
            }
            bool operator!=(generator_iterator<T> const & other) const {
                assert( other.the_generator.__generator_state == -1);
                return the_generator.__generator_state != other.the_generator.__generator_state ;
            }
            bool operator<(generator_iterator<T> const & other) const {
                assert( other.the_generator.__generator_state == -1);
                return the_generator.__generator_state != other.the_generator.__generator_state ;
            }
        };

    }

}

#endif


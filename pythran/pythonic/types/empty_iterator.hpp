#ifndef PYTHONIC_TYPES_EMPTY_ITERATOR_HPP
#define PYTHONIC_TYPES_EMPTY_ITERATOR_HPP

namespace pythonic {

    namespace types {

        struct empty_iterator : std::iterator< std::forward_iterator_tag, int > {
            // Empty iterator used, among other things, by empty_set
            empty_iterator() {};
            empty_iterator(empty_iterator const&) {};
            bool operator==(empty_iterator const&) const{
                return true;
            }
            bool operator!=(empty_iterator const&) const{
                return false;
            }
            bool operator<(empty_iterator const&) const{
                return false;
            }
            empty_iterator& operator++(){
                return *this;
            }
            empty_iterator& operator++(int){
                return *this;
            }
            void operator*() const{
                return;
            }
            void operator->() const{
                return;
            }
        };

    }

}

#endif

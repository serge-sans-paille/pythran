#ifndef PYTHONIC_ITERATOR_H
#define PYTHONIC_ITERATOR_H
namespace pythonic {

    template <class T>
        struct generator_iterator : std::iterator<std::forward_iterator_tag, typename T::result_type> {
            T the_generator;
            long step;
            generator_iterator() : the_generator(), step(std::numeric_limits<long>::max()) { the_generator.__generator_state = -1 ;} // this represents the end
            generator_iterator(T const& a_generator) : the_generator(a_generator), step(0) {}
            generator_iterator& operator++() { ++step; the_generator.next(); return *this; }
            typename T::result_type operator*() {
                 return *the_generator;
            }
            bool operator!=(generator_iterator<T> const & other) const {
                if( the_generator.__generator_state == other.the_generator.__generator_state and the_generator.__generator_state == -1 )
                    return false;
                else
                    return step != other.step;
            }
            bool operator==(generator_iterator<T> const & other) const {
                return ! ((*this) == other);
            }
            bool operator<(generator_iterator<T> const & other) const {
                if( the_generator.__generator_state == other.the_generator.__generator_state and the_generator.__generator_state == -1 )
                    return false;
                else
                    return step < other.step;
            }
        };

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
#endif

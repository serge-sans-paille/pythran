#ifndef PYTHONIC_ITERATOR_H
#define PYTHONIC_ITERATOR_H
namespace pythonic {

    template <class T>
        struct generator_iterator : std::iterator<std::forward_iterator_tag, typename T::result_type, ptrdiff_t, typename T::result_type*, typename T::result_type /* no ref */>
    {

            T the_generator;
            generator_iterator() : the_generator() { the_generator.__generator_state = -1 ;} // this represents the end
            generator_iterator(T const& a_generator) : the_generator(a_generator) {
            }
            generator_iterator& operator++() {
                try { the_generator.next(); }
                catch(core::StopIteration const&) {
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

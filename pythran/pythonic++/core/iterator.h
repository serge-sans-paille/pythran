#ifndef PYTHONIC_ITERATOR_H
#define PYTHONIC_ITERATOR_H
namespace pythonic {

    template <class T>
        struct generator_iterator : std::iterator<std::forward_iterator_tag, typename T::result_type> {
            T * the_generator;
            generator_iterator() : the_generator(nullptr) {}
            generator_iterator(T* a_generator) : the_generator(a_generator) {}
            generator_iterator& operator++() { assert(the_generator); the_generator->next(); return *this; }
            typename T::result_type operator*() { assert(the_generator); return **the_generator; }
            bool operator!=(generator_iterator<T> const & other) const {
                return (other.the_generator and (*the_generator) != (*other.the_generator) )
                    or the_generator->__generator_state != -1 ;
            }
            bool operator==(generator_iterator<T> const & other) const {
                return (other.the_generator and (*the_generator) == (*other.the_generator) );
            }
            bool operator<(generator_iterator<T> const & other) const {
                assert(not other.the_generator);
                return the_generator-> __generator_state != -1; // kind of a hack.
            }
        };

    //    typedef struct empty_iterator empty_iterator;
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

    template<class T>
    struct loop_iterator : std::iterator< typename T::iterator::iterator_category, typename T::iterator::value_type > {
        T container;
        typename T::const_iterator iter;
        typename T::const_iterator end;
        //loop_iterator(T&& container) : 
        //    container(container), iter(container.begin()), end(container.end()) {
        //}
        loop_iterator(T const& container) : 
            container(container), iter(container.begin()), end(container.end()) {
        }

        loop_iterator& operator++() {
            ++iter;
            return *this;
        }

        typename T::const_iterator::reference operator*() {
            return *iter;
        }

        bool operator!=(typename T::const_iterator const& other) {
            return iter != other;
        }
        bool operator<(typename T::const_iterator const& other) {
            return iter < other;
        }

    };

}
#endif

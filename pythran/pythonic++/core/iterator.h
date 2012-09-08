#ifndef PYTHONIC_ITERATOR_H
#define PYTHONIC_ITERATOR_H
namespace pythonic {

    template <class T>
        struct generator_iterator : std::iterator<std::forward_iterator_tag, typename T::return_type> {
            T * the_generator;
            generator_iterator() : the_generator(nullptr) {}
            generator_iterator(T* a_generator) : the_generator(a_generator) {}
            generator_iterator& operator++() { assert(the_generator); the_generator->next(); return *this; }
            typename T::return_type operator*() { assert(the_generator); return **the_generator; }
            bool operator!=(generator_iterator<T> const & other) {
                return (other.the_generator and (*the_generator) != (*other.the_generator) )
                    or the_generator->__generator_state != -1 ;
            }
            bool operator<(generator_iterator<T> const & other) {
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

}
#endif

#ifndef PYTHONIC_SEQUENCE_H
#define PYTHONIC_SEQUENCE_H
#include <vector>
#include <memory>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <boost/pool/object_pool.hpp>

namespace  pythonic {

    struct empty_sequence;
    template <class T> class sequence;


    struct slice {
        long lower, upper, step;
        slice(long lower=0, long upper=std::numeric_limits<long>::max(), long step=1)
            : lower(lower), upper(upper), step(step) {}
    };

    template<class T>
        class sequence_view {

            // data holder
            typedef std::vector< typename std::remove_cv< typename std::remove_reference<T>::type>::type > container_type;
            size_t* refcount;
            container_type* data; 

            template<class U>
                friend class sequence;

            slice slicing;

            public:
            //  types
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::allocator_type allocator_type;
            typedef typename container_type::pointer pointer;
            typedef typename container_type::const_pointer const_pointer;
            typedef typename container_type::reverse_iterator reverse_iterator;
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;

            // constructor
            sequence_view(): data(nullptr),refcount(nullptr) {}
            sequence_view(sequence<T> & , slice const &);
            ~sequence_view() {
                if(refcount) {
                    --*refcount;
                    assert(*refcount);
                }
            }

            // assignment
            sequence_view& operator=(sequence<T> const & );
            sequence_view& operator=(sequence_view<T> const & );
            sequence<T> operator+(sequence_view<T> const & );

            // iterators
            iterator begin() { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
            const_iterator begin() const { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
            iterator end() { assert(slicing.step==1) ; return data->begin()+slicing.upper; }
            const_iterator end() const { assert(slicing.step==1) ; return data->begin()+slicing.upper; }

        };

    /* the container type */
    template<class T>
        class sequence {

            // data holder
            typedef std::vector< typename std::remove_cv< typename std::remove_reference<T>::type>::type > container_type;
            size_t* refcount;
            container_type* data; 

            struct memory_size { size_t refcount; container_type data; };


            template<class U>
                friend struct _id;

            template<class U>
                friend class sequence_view;

            static boost::object_pool<memory_size> pool;

            public:

            // types
            typedef typename container_type::reference reference;
            typedef typename container_type::const_reference const_reference;
            typedef typename container_type::iterator iterator;
            typedef typename container_type::const_iterator const_iterator;
            typedef typename container_type::size_type size_type;
            typedef typename container_type::difference_type difference_type;
            typedef typename container_type::value_type value_type;
            typedef typename container_type::allocator_type allocator_type;
            typedef typename container_type::pointer pointer;
            typedef typename container_type::const_pointer const_pointer;
            typedef typename container_type::reverse_iterator reverse_iterator;
            typedef typename container_type::const_reverse_iterator const_reverse_iterator;


            // constructors
            sequence() :
                data(nullptr),refcount(nullptr) {}
            sequence(empty_sequence const &) :
                refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; }
            sequence(size_type sz) :
                refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(sz)) { *refcount=1; }
            sequence(std::initializer_list<value_type> l) :
                refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type(l)) { *refcount=1; }
            sequence(sequence<T> const & other) :
                data(const_cast<sequence<T>*>(&other)->data), refcount(const_cast<sequence<T>*>(&other)->refcount) { ++*refcount; }
            template<class F>
                sequence(sequence<F> const & other) :
                    refcount(reinterpret_cast<size_t*>(pool.malloc())), data(new (refcount+1) container_type()) { *refcount=1; std::copy(other.begin(), other.end(), std::back_inserter(*data)); }
            ~sequence() {
                if(refcount and not --*refcount) { pool.free( reinterpret_cast<memory_size*>(refcount)); }
            }

            sequence<T>& operator=(sequence<T> const & other) {
                if(other.data != data) {
                    if(refcount and not --*refcount) { pool.free( reinterpret_cast<memory_size*>(refcount) ); }
                    data=const_cast<sequence<T>*>(&other)->data;
                    refcount=const_cast<sequence<T>*>(&other)->refcount;
                    ++*refcount;
                }
                return *this;

            }
            sequence<T>& operator=(sequence_view<T> const & other) {
                if(other.data == data ) {
                    auto it = std::copy(other.begin(), other.end(), data->begin());
                    data->resize(it - data->begin());
                }
                else {
                    if(refcount and not --*refcount) {
                        /* should free the memory then reallocate it, so do nothing */
                    }
                    else {
                        refcount=reinterpret_cast<size_t*>(pool.malloc());
                        data=new (refcount+1) container_type(other.end() - other.begin());
                    }
                    std::copy(other.begin(), other.end(), data->begin());
                }
                return *this;
            }
            sequence<T>& operator+=(sequence_view<T> const & other) {
                std::copy(other.begin(), other.end(), std::back_inserter(*data));
                return *this;
            }

            // iterators
            iterator begin() { return data->begin(); }
            const_iterator begin() const { return data->begin(); }
            iterator end() { return data->end(); }
            const_iterator end() const { return data->end(); }
            reverse_iterator rbegin() { return data->rbegin(); }
            const_reverse_iterator rbegin() const { return data->rbegin(); }
            reverse_iterator rend() { return data->rend(); }
            const_reverse_iterator rend() const { return data->rend(); }

            // element access
            reference operator[]( long n ) {
#ifndef NDEBUG
                return (*data)[(n>=0)?n : (data->size() + n)];
#else
                return (*data).at((n>=0)?n : (data->size() + n));
#endif
            }
            const_reference operator[]( long n ) const {
#ifndef NDEBUG
                return (*data)[(n>=0)?n : (data->size() + n)];
#else
                return (*data).at((n>=0)?n : (data->size() + n));
#endif
            }

            sequence<T> operator[]( slice const &s ) {
                sequence<T> out(0);
                long lower, upper;
                if(s.step<0) {
                    if( s.lower == std::numeric_limits<long>::max() )
                        lower = data->size();
                    else
                        lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + data->size());
                    upper = std::min(upper, (long)data->size());
                    for(long iter = lower+s.step; iter >= upper ; iter+=s.step)
                        out.push_back((*data)[iter]);
                }
                else {
                    lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + data->size());
                    upper = std::min(upper, (long)data->size());
                    for(long iter = lower; iter < upper ; iter+=s.step)
                        out.push_back((*data)[iter]);
                }
                return out;
            }

            sequence_view<T> operator()( slice const &s) {
                return sequence_view<T>(*this, s);
            }

            // modifiers
            void push_back( const T& x) { data->push_back(x); }
            void insert(size_t i, const T& x) { data->insert(data->begin()+i, x); }
            void reserve(size_t n) { data->reserve(n); }
            void resize(size_t n) { data->resize(n); }

            // list interface
            operator bool() { return not data->empty(); }

            template <class F>
                sequence<decltype(std::declval<T>()+std::declval<typename sequence<F>::value_type>())> operator+(sequence<F> const & s) const {
                    sequence<decltype(std::declval<T>()+std::declval<typename sequence<F>::value_type>())> clone(*this);
                    std::copy(s.begin(), s.end(), std::back_inserter(clone));
                    return clone;
                }

            template <class F>
                sequence<decltype(std::declval<T>()+std::declval<typename sequence_view<F>::value_type>())> operator+(sequence_view<F> const & s) const {
                    sequence<decltype(std::declval<T>()+std::declval<typename sequence_view<F>::value_type>())> clone(*this);
                    std::copy(s.begin(), s.end(), std::back_inserter(clone));
                    return clone;
                }

            sequence<T> operator+(empty_sequence const &) const {
                return *this;
            }
            template<class F>
            sequence<T> operator*(F const& t) const {
                size_t n = t;
                sequence<T> r(r.data->size()*n);
                for(size_t i=0;i<n;i++)
                    std::copy(this->begin(), this->end(),r.begin());
                return r;
            }

            template <class F>
                sequence<T>& operator+=(sequence<F> const & s) {
                    std::copy(s.begin(), s.end(), std::back_inserter(*this));
                    return *this;
                }

        };
    template<class T>
        boost::object_pool<typename sequence<T>::memory_size> sequence<T>::pool;


    /* empty sequence implementation */
    struct empty_sequence {
        template<class T> // just for type inference, should never been instantiated
            sequence<T> operator+(sequence<T> const & s) { return s; }
        empty_sequence operator+(empty_sequence const &) { return empty_sequence(); }
    };

    /* sequence_view implementation */
    template<class T>
        sequence_view<T>::sequence_view(sequence<T> & other, slice const &s):
            refcount(other.refcount), data(other.data), slicing(s) {
                ++*refcount;
                long lower, upper;
                if(slicing.step<0) {
                    if( slicing.lower == std::numeric_limits<long>::max() )
                        lower = data->size();
                    else
                        lower = s.lower >= 0L ? s.lower : ( s.lower + data->size());
                    slicing.lower = std::max(0L,lower);
                    upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                    slicing.upper = std::min(upper, (long)data->size());
                }
                else {
                    lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
                    slicing.lower = std::max(0L,lower);
                    upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                    slicing.upper = std::min(upper, (long)data->size());
                }
            }
    template<class T>
        sequence_view<T>& sequence_view<T>::operator=(sequence_view<T> const & s) {
                slicing=s.slicing;
                if(data != s.data) {
                    refcount=s.refcount;
                    data=s.data;
                    ++*refcount;
                }
                return *this;
        }

    template<class T>
        sequence_view<T>& sequence_view<T>::operator=(sequence<T> const & seq) {
                sequence<T> out;
                long lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
                lower = std::max(0L,lower);
                long upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
                upper = std::min(upper, (long)data->size());
                typename sequence<T>::iterator it = data->begin(); 
                if( slicing.step == 1) {
                    data->erase(it+lower, it + upper);
                    data->insert(it+lower, seq.begin(), seq.end());
                }
                else {
                    assert("not implemented yet");
                }
                if( data!= seq.data ) ++*refcount;
                return *this;
        }
    template<class T>
        sequence<T> sequence_view<T>::operator+(sequence_view<T> const & s) {
            sequence<T> out;
            out=*this;
            out+=s;
            return out;
        }

}
#endif

#ifndef PYTHONIC_TYPES_STR_HPP
#define PYTHONIC_TYPES_STR_HPP

#include "pythonic/types/slice.hpp"
#include "pythonic/types/long.hpp"
#include "pythonic/types/tuple.hpp"

#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/int_.hpp"

#include <boost/format.hpp>
#include <cassert>
#include <string>
#include <cstring>
#include <sstream>
#include <stdexcept>

namespace pythonic {

    namespace types {

        class str;

        struct const_sliced_str_iterator : std::iterator< std::random_access_iterator_tag, char, ptrdiff_t, char*, char >
        {
            const char * data;
            long step;
            const_sliced_str_iterator(char const *data, long step) : data(data), step(step) {
            }
            const_sliced_str_iterator operator++() { data +=step; return *this; }
            bool operator<(const_sliced_str_iterator const& other) const { return (step>0)?(data < other.data):(data > other.data); }
            bool operator==(const_sliced_str_iterator const& other) const { return data == other.data; }
            bool operator!=(const_sliced_str_iterator const& other) const { return data != other.data; }
            char operator*() const { return *data; }
            const_sliced_str_iterator operator-(long n) const { const_sliced_str_iterator other(*this); other.data -= step * n; return other; }
            long operator-(const_sliced_str_iterator const & other) const { return (data - other.data)/step; }
        };

        template<class S=slice>
        class sliced_str {
            typedef std::string container_type;
            utils::shared_ref<container_type> data;

            typename S::normalized_type slicing;

            public:
            //  types
            typedef container_type::reference reference;
            typedef container_type::const_reference const_reference;
            typedef const_sliced_str_iterator iterator;
            typedef const_sliced_str_iterator const_iterator;
            typedef container_type::size_type size_type;
            typedef container_type::difference_type difference_type;
            typedef container_type::value_type value_type;
            typedef container_type::allocator_type allocator_type;
            typedef container_type::pointer pointer;
            typedef container_type::const_pointer const_pointer;

            // constructor
            sliced_str(): data(utils::no_memory()) {}
            sliced_str(sliced_str const & s): data(s.data), slicing(s.slicing) {}

            sliced_str(sliced_str const & s, typename S::normalized_type const& sl): data(s.data), slicing(s.slicing * sl) {}
            sliced_str(types::str const & other, typename S::normalized_type const & s);

            // const getter
            container_type const & get_data() const { return *data; }
            typename S::normalized_type const & get_slice() const { return slicing; }

            // assignment
            sliced_str& operator=(str const & );
            sliced_str& operator=(sliced_str const & );
            str operator+(sliced_str const & );

            // iterators
            const_iterator begin() const { return const_iterator(data->c_str() + slicing.lower, slicing.step); }
            const_iterator end() const { return const_iterator(data->c_str() + slicing.upper, slicing.step); }

            // size
            size_type size() const { return slicing.size(); }

            // accessor
            char const & operator[](long i) const { return (*data)[slicing.get(i)];}
            char & operator[](long i) { return (*data)[slicing.get(i)];}
            sliced_str<slice> operator[](slice const& s) const { return sliced_str<slice>(*this, s.normalize(size())); }
            sliced_str<contiguous_slice> operator[](contiguous_slice const& s) const { return sliced_str<contiguous_slice>(*this, s.normalize(size())); }

            // conversion
            operator long();
            explicit operator bool() const {return size() > 0;}
            bool operator!() const { return not bool();}

            // io
            friend  std::ostream& operator<<(std::ostream& os, types::sliced_str<S> const & v) {
                for(auto b = v.begin(); b != v.end(); ++b)
                    os << *b;
                return os;
            }
        };

        class str {
            template<class S> friend class sliced_str;
            typedef std::string container_type;
            utils::shared_ref<container_type> data;

            public:

            static const size_t npos = std::string::npos;

            typedef types::str value_type;
            typedef container_type::iterator iterator;
            typedef container_type::reverse_iterator reverse_iterator;
            typedef container_type::const_reverse_iterator const_reverse_iterator;

            str() : data() {}
            str(std::string const & s) : data(s) {}
            str(std::string && s) : data(std::move(s)) {}
            str(const char*s) : data(s) {}
            str(const char*s, size_t n) : data(s,n) {}
            str(char c) : data(1,c) {}
            template<class S>
            str(sliced_str<S> const & other) : data( other.begin(), other.end()) {}
            template<class T>
                str(T const& begin, T const& end) : data( begin, end) {}

            explicit operator char() const {
                assert(size() == 1);
                return (*data)[0];
            }

            operator long int() const { // Allows implicit conversion without loosing bool conversion
                char *endptr;
                auto dat = data->data();
                long res = strtol(dat, &endptr,10);
                if(endptr == dat) {
                    std::ostringstream err;
                    err << "invalid literal for long() with base 10:"
                        "'" << c_str() << '\'';
                    throw std::runtime_error(err.str());
                }
                return res;
            }

            operator pythran_long_t() const {
#ifdef USE_GMP
                return pythran_long_t(*data);
#else
                char *endptr;
                auto dat = data->data();
                pythran_long_t res = strtoll(dat, &endptr,10);
                if(endptr == dat) {
                    std::ostringstream err;
                    err << "invalid literal for long() with base 10:"
                        "'" << c_str() << '\'';
                    throw std::runtime_error(err.str());
                }
                return res;
#endif
            }

            explicit operator double() const {
                char *endptr;
                auto dat = data->data();
                double res = strtod(dat, &endptr);
                if(endptr == dat) {
                    std::ostringstream err;
                    err << "invalid literal for double():"
                        << "'" << c_str() << "'";
                    throw std::runtime_error(err.str());
                }
                return res;
            }
            template<class S>
            str& operator=(sliced_str<S> const & other) {
                if(other.get_data() == *data ) {
                    auto it = std::copy(other.begin(), other.end(), begin());
                    resize(it - this->begin());
                }
                else {
                    *this=other.get_data();
                }
                return *this;
            }

            types::str& operator+=(types::str const& s) {
                *data += *s.data;
                return *this;
            }

            container_type const & get_data() const { return *data; }

            size_t size() const { return data->size(); }
            auto begin() const -> decltype(data->begin()) { return data->begin(); }
            auto begin() -> decltype(data->begin()) { return data->begin(); }
            auto rbegin() const -> decltype(data->rbegin()) { return data->rbegin(); }
            auto rbegin() -> decltype(data->rbegin()) { return data->rbegin(); }
            auto end() const -> decltype(data->end()) { return data->end(); }
            auto end() -> decltype(data->end()) { return data->end(); }
            auto rend() const -> decltype(data->rend()) { return data->rend(); }
            auto rend() -> decltype(data->rend()) { return data->rend(); }
            auto c_str() const -> decltype(data->c_str()) { return data->c_str(); }
            auto resize(long n) -> decltype(data->resize(n)) { return data->resize(n); }
            size_t find(str const &s, size_t pos = 0) const {
                const char * res =  strstr(c_str() + pos, s.c_str());
                return res ? res - c_str() : npos;
            }
            bool contains(str const& v) const { return find(v) != npos; }
            size_t find_first_of(str const &s, size_t pos = 0) const { return data-> find_first_of(*s.data, pos); }
            size_t find_first_of(const char* s, size_t pos = 0) const { return data-> find_first_of(s, pos); }
            size_t find_first_not_of(str const &s, size_t pos = 0) const { return data->find_first_not_of(*s.data, pos); }
            size_t find_last_not_of(str const &s, size_t pos = npos) const { return data-> find_last_not_of(*s.data, pos); }
            str substr(size_t pos = 0, size_t len = npos) const { return data->substr(pos, len); }
            bool empty() const { return data->empty(); }
            int compare(size_t pos, size_t len, str const & str) const { return data->compare(pos, len, *str.data); }
            void reserve(size_t n) { data->reserve(n); }
            str& replace(size_t pos,  size_t len,  str const & str) { data->replace(pos, len, *str.data); return *this; }

            template<class S>
            str& operator+=(sliced_str<S> const & other) {
                resize(size() + other.get_data().size());
                std::copy(other.begin(), other.end(), begin());
                return *this;
            }
            bool operator==(str const& other) const { return *data == *other.data; }
            bool operator!=(str const& other) const { return *data != *other.data; }
            bool operator<=(str const& other) const { return *data <= *other.data; }
            bool operator<(str const& other) const { return *data < *other.data; }
            bool operator>=(str const& other) const { return *data >= *other.data; }
            bool operator>(str const& other) const { return *data > *other.data; }
            template<class S>
            bool operator==(sliced_str<S> const & other) const {
                if(size() != other.size())
                    return false;
                for(size_t i=other.get_slice().lower, j=0L;
                        j<size();
                        i= i + other.get_slice().step, j++)
                    if(other.get_data()[i] != (*this)[j])
                        return false;
                return true;
            }
            sliced_str<slice> operator()( slice const &s) const {
                return operator[](s);
            }
            sliced_str<contiguous_slice> operator()( contiguous_slice const &s) const {
                return operator[](s);
            }

            char operator[]( long i) const {
                if(i<0) i+= size();
                return (*data)[i];
            }

            char& operator[]( long i) {
                if(i<0) i+= size();
                return (*data)[i];
            }
            sliced_str<slice> operator[]( slice const &s ) const {
                return sliced_str<slice>(*this, s.normalize(size()));
            }
            sliced_str<contiguous_slice> operator[]( contiguous_slice const &s ) const {
                return sliced_str<contiguous_slice>(*this, s.normalize(size()));
            }
#ifdef USE_GMP
            char operator[](pythran_long_t const &m) const { return (*this)[m.get_si()];}
            char & operator[](pythran_long_t const& m) { return (*this)[m.get_si()];}
#endif


            explicit operator bool() const{
                return not data->empty();
            }
            template<class A>
                types::str operator%(A const & a) const {
                    const boost::format fmter(*data);
                    return (boost::format(fmter) % a ).str();
                }
            template<class ...A>
                types::str operator%(std::tuple<A...> const & a) const {
                    boost::format fmter(*data);
                    (fmt(fmter, a, utils::int_<sizeof...(A)>() ));
                    return fmter.str();
                }
            template<size_t N, class T>
                types::str operator%(types::array<T, N> const & a) const {
                    boost::format fmter(*data);
                    (fmt(fmter, a, utils::int_<N>() ));
                    return fmter.str();
                }

            long count(types::str const & sub) const {
                long counter = 0;
                for(size_t z = find(sub);           // begin by looking for sub
                    z != npos;                      // as long as we don't reach the end
                    z = find(sub, z + sub.size()))  // look for another one
                {
                    ++counter;
                }
                return counter;
            }

            private:
            template<class Tuple, size_t I>
                void fmt(boost::format & f, Tuple const & a, utils::int_<I>) const {
                    fmt(f % std::get<std::tuple_size<Tuple>::value-I>(a), a, utils::int_<I-1>());
                }
            template<class Tuple>
                void fmt(boost::format & f, Tuple const & a, utils::int_<1>) const {
                    f % std::get<std::tuple_size<Tuple>::value-1>(a);
                }

        };

        template<class S>
        str sliced_str<S>::operator+(sliced_str<S> const & s) {
            str out(*data);
            std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
            return out;
        }

        str operator+(str const& self, str const& other) {
            return str(self.get_data() + other.get_data());
        }

        str operator+(str const& self, char const *s) {
            return str(self.get_data() + s);
        }

        str operator+(char const *s, str const& other) {
            return str(s + other.get_data());
        }
        bool operator==(char c, str const& s) {
            return s.size() == 1 and s[0] == c;
        }
        bool operator==(str const& s, char c) {
            return s.size() == 1 and s[0] == c;
        }
        bool operator!=(char c, str const& s) {
            return s.size() != 1 or s[0] != c;
        }
        bool operator!=(str const& s, char c) {
            return s.size() != 1 or s[0] != c;
        }
        std::ostream& operator<<(std::ostream& os, str const & s) {
            return os << s.c_str();
        }

    }


}

pythonic::types::str operator*(pythonic::types::str const & s, long n) {
    if(n<0)
        return pythonic::types::str();
    pythonic::types::str other;
    other.resize(s.size()*n);
    auto where = other.begin();
    for(long i=0;i<n; i++, where+=s.size())
        std::copy(s.begin(), s.end(), where);
    return other;
}

pythonic::types::str operator*(long t, pythonic::types::str const & s) {
    return s*t;
}

template<class S>
pythonic::types::sliced_str<S>& pythonic::types::sliced_str<S>::operator=(pythonic::types::sliced_str<S> const & s) {
    slicing=s.slicing;
    data=s.data;
    return *this;
}

template<class S>
pythonic::types::sliced_str<S>& pythonic::types::sliced_str<S>::operator=(pythonic::types::str const & s) {
    if( slicing.step == 1) {
        data->erase(slicing.lower, slicing.upper);
        data->insert(slicing.lower, s.get_data());
    }
    else {
        assert("not implemented yet");
    }
    return *this;
}

template<class S>
pythonic::types::sliced_str<S>::sliced_str(pythonic::types::str const& other, typename S::normalized_type const & s) : data(other.data), slicing(s){}


template<class S>
pythonic::types::sliced_str<S>::operator long() {
    long out;
    std::istringstream iss(pythonic::types::str(*this).get_data());
    iss >> out;
    return out;
}

namespace std {
    template <> struct hash<pythonic::types::str>
    {
        size_t operator()(const pythonic::types::str & x) const
        {
            return hash<std::string>()(x.get_data());
        }
    };
}

namespace pythonic {
    namespace types {
        std::size_t hash_value(str  const &x) {
            return std::hash<str>()(x);
        }
    }
}

/* std::get overload */
namespace std {
    template <size_t I>
        typename pythonic::types::str get( pythonic::types::str const &t) { return pythonic::types::str(t[I]); }

    template <size_t I>
        class tuple_element<I, pythonic::types::str > {
            public:
                typedef typename pythonic::types::str type;
        };
    template <size_t I, class S>
        class tuple_element<I, pythonic::types::sliced_str<S> > {
            public:
            typedef typename pythonic::types::str type;
        };
}
#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"

namespace pythonic {
    template<>
        struct python_to_pythran< types::str >{
            python_to_pythran(){
                static bool registered =false;
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::insert(&convertible,&construct,boost::python::type_id<types::str>());
                }
            }
            static void* convertible(PyObject* obj_ptr){
                if( !PyString_Check(obj_ptr) ) return 0;
                return obj_ptr;
            }
            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<types::str >*)(data))->storage.bytes;
                char* s=PyString_AS_STRING(obj_ptr);
                new (storage) types::str(s, PyString_GET_SIZE(obj_ptr));
                data->convertible=storage;
            }
        };
    struct custom_pythran_string_to_str{
        static PyObject* convert(const types::str& v){
            return PyString_FromStringAndSize(v.c_str(), v.size());
        }
    };

    template<>
        struct pythran_to_python< types::str > {
            pythran_to_python() {
                register_once< types::str, custom_pythran_string_to_str >();
            }
        };

    struct custom_pythran_sliced_str_to_str {
        static PyObject* convert(const types::sliced_str<types::contiguous_slice>& v){
            return custom_pythran_string_to_str().convert(v);
        }
        static PyObject* convert(const types::sliced_str<types::slice>& v){
            return custom_pythran_string_to_str().convert(v);
        }
    };

    template<class S>
    struct pythran_to_python< types::sliced_str<S> > {
        pythran_to_python() {
            register_once< types::sliced_str<S>, custom_pythran_sliced_str_to_str >();
        }
    };

}

#endif

#endif

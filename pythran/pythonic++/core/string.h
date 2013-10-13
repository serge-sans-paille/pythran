#ifndef PYTHONIC_STRING_H
#define PYTHONIC_STRING_H
#include "slice.h" // for slices
#include "shared_ref.h"
#include <boost/format.hpp>
#include <cassert>
#include <string>
#include <sstream>
#include <stdexcept>

namespace pythonic {
    namespace core {
        class string;

        struct const_string_view_iterator : std::iterator< std::random_access_iterator_tag, char >
        {
            const char * data;
            long step;
            const_string_view_iterator(char const *data, long step) : data(data), step(step) {
            }
            const_string_view_iterator operator++() { data +=step; return *this; }
            bool operator<(const_string_view_iterator const& other) const { return (step>0)?(data < other.data):(data > other.data); }
            bool operator==(const_string_view_iterator const& other) const { return data == other.data; }
            bool operator!=(const_string_view_iterator const& other) const { return data != other.data; }
            char operator*() const { return *data; }
            char operator*() { return *data; }
            const_string_view_iterator operator-(long n) const { const_string_view_iterator other(*this); other.data += step * n; return other; } 
            long operator-(const_string_view_iterator const & other) const { return (data - other.data)/step; }
        };

        class string_view {
            typedef std::string container_type;
            impl::shared_ref<container_type> data;

            normalized_slice slicing;

            public:
            //  types
            typedef container_type::reference reference;
            typedef container_type::const_reference const_reference;
            typedef const_string_view_iterator iterator;
            typedef const_string_view_iterator const_iterator;
            typedef container_type::size_type size_type;
            typedef container_type::difference_type difference_type;
            typedef container_type::value_type value_type;
            typedef container_type::allocator_type allocator_type;
            typedef container_type::pointer pointer;
            typedef container_type::const_pointer const_pointer;

            // constructor
            string_view(): data(impl::no_memory()) {}
            string_view(string_view const & s): data(s.data), slicing(s.slicing) {}
            string_view(string_view const & s, normalized_slice const& sl): data(s.data), slicing(s.slicing.lower + sl.lower, s.slicing.lower + sl.upper, s.slicing.step * sl.step) {}
            string_view(core::string & other, normalized_slice const & s);

            // const getter
            container_type const & get_data() const { return *data; }
            normalized_slice const & get_slice() const { return slicing; }

            // assignment
            string_view& operator=(string const & );
            string_view& operator=(string_view const & );
            string operator+(string_view const & );

            // iterators
            const_iterator begin() const { return const_iterator(data->c_str() + slicing.lower, slicing.step); }
            const_iterator end() const { return const_iterator(data->c_str() + slicing.upper, slicing.step); }

            // size
            size_type size() const { return slicing.size(); }

            // accessor
            char const & operator[](long i) const { return (*data)[slicing.lower + i*slicing.step];}
            char & operator[](long i) { return (*data)[slicing.lower + i*slicing.step];}
            string_view operator[](slice const& s) const { return string_view(*this, s.normalize(size())); }

            // conversion
            operator long();
            explicit operator bool() const {return size() > 0;}
            bool operator!() const { return not bool();}

            // io
            friend std::ostream& operator<<(std::ostream& os, core::string_view const & v) {
                for(auto b = v.begin(); b != v.end(); ++b)
                    os << *b;
                return os;
            }
        };

        class string {
            friend class string_view;
            typedef std::string container_type;
            impl::shared_ref<container_type> data;

            public:

            static const size_t npos = std::string::npos;

            typedef core::string value_type;
            typedef container_type::iterator iterator;

            string() : data() {}
            string(std::string const & s) : data(s) {}
            string(std::string && s) : data(std::move(s)) {}
            string(const char*s) : data(s) {}
            string(const char*s, size_t n) : data(s,n) {}
            string(char c) : data(1,c) {}
            string(string_view const & other) : data( other.begin(), other.end()) {}
            template<class T>
                string(T const& begin, T const& end) : data( begin, end) {}

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
            string& operator=(string_view const & other) {
                if(other.get_data() == *data ) {
                    auto it = std::copy(other.begin(), other.end(), begin());
                    resize(it - this->begin());
                }
                else {
                    *this=other.get_data();
                }
                return *this;
            }

            core::string& operator+=(core::string const& s) {
                *data += *s.data;
                return *this;
            }

            container_type const & get_data() const { return *data; }

            size_t size() const { return data->size(); }
            auto begin() const -> decltype(data->begin()) { return data->begin(); }
            auto begin() -> decltype(data->begin()) { return data->begin(); }
            auto end() const -> decltype(data->end()) { return data->end(); }
            auto end() -> decltype(data->end()) { return data->end(); }
            auto c_str() const -> decltype(data->c_str()) { return data->c_str(); }
            auto resize(long n) -> decltype(data->resize(n)) { return data->resize(n); }
            size_t find(string const &s, size_t pos = 0) const {
                const char * res =  strstr(c_str() + pos, s.c_str());
                return res ? res - c_str() : npos;
            }
            size_t find_first_of(string const &s, size_t pos = 0) const { return data-> find_first_of(*s.data, pos); }
            size_t find_first_of(const char* s, size_t pos = 0) const { return data-> find_first_of(s, pos); }
            size_t find_first_not_of(string const &s, size_t pos = 0) const { return data->find_first_not_of(*s.data, pos); }
            size_t find_last_not_of(string const &s, size_t pos = npos) const { return data-> find_last_not_of(*s.data, pos); }
            string substr(size_t pos = 0, size_t len = npos) const { return data->substr(pos, len); }
            bool empty() const { return data->empty(); }
            int compare(size_t pos, size_t len, string const & str) const { return data->compare(pos, len, *str.data); }
            void reserve(size_t n) { data->reserve(n); }
            string& replace(size_t pos,  size_t len,  string const & str) { data->replace(pos, len, *str.data); return *this; }

            string& operator+=(string_view const & other) {
                resize(size() + other.get_data().size());
                std::copy(other.begin(), other.end(), begin());
                return *this;
            }
            bool operator==(string const& other) const { return *data == *other.data; }
            bool operator!=(string const& other) const { return *data != *other.data; }
            bool operator<=(string const& other) const { return *data <= *other.data; }
            bool operator<(string const& other) const { return *data < *other.data; }
            bool operator>=(string const& other) const { return *data >= *other.data; }
            bool operator>(string const& other) const { return *data > *other.data; }
            bool operator==(string_view const & other) const {
                if(size() != other.size())
                    return false;
                for(size_t i=other.get_slice().lower, j=0L;
                        j<size();
                        i= i + other.get_slice().step, j++)
                    if(other.get_data()[i] != (*this)[j])
                        return false;
                return true;
            }
            string_view operator()( slice const &s) const {
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
            string_view operator[]( slice const &s ) const {
                return string_view(*const_cast<string*>(this), s.normalize(size())); // SG: ugly !
            }
#ifdef USE_GMP
            char operator[](pythran_long_t const &m) const { return (*this)[m.get_si()];}
            char & operator[](pythran_long_t const& m) { return (*this)[m.get_si()];}
#endif


            explicit operator bool() const{
                return not data->empty();
            }
            template<class A>
                core::string operator%(A const & a) const {
                    const boost::format fmter(*data);
                    return (boost::format(fmter) % a ).str();
                }
            template<class ...A>
                core::string operator%(std::tuple<A...> const & a) const {
                    boost::format fmter(*data);
                    (fmt(fmter, a, int_<sizeof...(A)>() ));
                    return fmter.str();
                }
            template<size_t N, class T>
                core::string operator%(core::array<T, N> const & a) const {
                    boost::format fmter(*data);
                    (fmt(fmter, a, int_<N>() ));
                    return fmter.str();
                }
            private:
            template<class Tuple, size_t I>
                void fmt(boost::format & f, Tuple const & a, int_<I>) const {
                    fmt(f % std::get<std::tuple_size<Tuple>::value-I>(a), a, int_<I-1>());
                }
            template<class Tuple>
                void fmt(boost::format & f, Tuple const & a, int_<1>) const {
                    f % std::get<std::tuple_size<Tuple>::value-1>(a);
                }

        };
        pythonic::core::string pythonic::core::string_view::operator+(pythonic::core::string_view const & s) {
            pythonic::core::string out(*data);
            std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
            return out;
        }

        pythonic::core::string operator+(pythonic::core::string const& str, pythonic::core::string const& str2) {
            return pythonic::core::string(str.get_data() + str2.get_data());
        }

        pythonic::core::string operator+(pythonic::core::string const& str, char const *s) {
            return pythonic::core::string(str.get_data() + s);
        }

        pythonic::core::string operator+(char const *s, pythonic::core::string const& str) {
            return pythonic::core::string(s + str.get_data());
        }
        bool operator==(char c, pythonic::core::string const& s) {
            return s.size() == 1 and s[0] == c;
        }
        bool operator==(pythonic::core::string const& s, char c) {
            return s.size() == 1 and s[0] == c;
        }
        bool operator!=(char c, pythonic::core::string const& s) {
            return s.size() != 1 or s[0] != c;
        }
        bool operator!=(pythonic::core::string const& s, char c) {
            return s.size() != 1 or s[0] != c;
        }

    }
}

pythonic::core::string operator*(pythonic::core::string const & s, long n) {
    if(n<0)
        return pythonic::core::string();
    pythonic::core::string other;
    other.resize(s.size()*n);
    auto where = other.begin();
    for(long i=0;i<n; i++, where+=s.size())
        std::copy(s.begin(), s.end(), where);
    return other;
}

pythonic::core::string operator*(long t, pythonic::core::string const & s) {
    return s*t;
}

pythonic::core::string_view& pythonic::core::string_view::operator=(pythonic::core::string_view const & s) {
    slicing=s.slicing;
    data=s.data;
    return *this;
}

pythonic::core::string_view& pythonic::core::string_view::operator=(pythonic::core::string const & s) {
    if( slicing.step == 1) {
        data->erase(slicing.lower, slicing.upper);
        data->insert(slicing.lower, s.get_data());
    }
    else {
        assert("not implemented yet");
    }
    return *this;
}

pythonic::core::string_view::string_view(pythonic::core::string & other, normalized_slice const & s) : data(other.data), slicing(s){}


pythonic::core::string_view::operator long() {
    long out;
    std::istringstream iss(pythonic::core::string(*this).get_data());
    iss >> out;
    return out;
}

namespace std {
    template <> struct hash<pythonic::core::string>
    {
        size_t operator()(const pythonic::core::string & x) const
        {
            return hash<std::string>()(x.get_data());
        }
    };
}

namespace pythonic {
    namespace core {
        std::size_t hash_value(string  const &x) {
            return std::hash<string>()(x);
        }
    }
}

/* std::get overload */
namespace std {
    template <size_t I>
        typename pythonic::core::string get( pythonic::core::string const &t) { return pythonic::core::string(t[I]); }

    template <size_t I>
        struct tuple_element<I, pythonic::core::string > {
            typedef typename pythonic::core::string type;
        };
    template <size_t I>
        struct tuple_element<I, pythonic::core::string_view > {
            typedef typename pythonic::core::string type;
        };
}

#endif

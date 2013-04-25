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

        class string_view {
            typedef std::string container_type;
            impl::shared_ref<container_type> data;

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
            string_view(): data(impl::no_memory()) {}
            string_view(string_view const & s): data(s.data), slicing(s.slicing) {}
            string_view(string & , slice const &);

            // const getter
            container_type const & get_data() const { return *data; }
            slice const & get_slice() const { return slicing; }

            // assignment
            string_view& operator=(string const & );
            string_view& operator=(string_view const & );
            string operator+(string_view const & );

            // iterators
            iterator begin() { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
            const_iterator begin() const { assert(slicing.step==1) ; return data->begin()+slicing.lower; }
            iterator end() { assert(slicing.step==1) ; return data->begin()+slicing.upper; }
            const_iterator end() const { assert(slicing.step==1) ; return data->begin()+slicing.upper; }

            // size
            size_type size() const { assert(slicing.step!=0); return (slicing.upper - slicing.lower)/slicing.step ; }

            // accessor
            char const & operator[](long i) const { return (*data)[slicing.lower + i*slicing.step];}
            char & operator[](long i) { return (*data)[slicing.lower + i*slicing.step];}

            // conversion
            operator long();
        };

        class string : public std::string {

            friend class string_view;

            public:
            string() : std::string() {}
            string(std::string const & s) : std::string(s) {}
            string(std::string && s) : std::string(std::move(s)) {}
            string(const char*s) : std::string(s) {}
            string(const char*s, size_t n) : std::string(s,n) {}
            string(char c) : std::string(1,c) {}
            string(string_view const & other) : std::string( other.begin(), other.end()) {}
            core::string operator+(core::string const& s) const {
                return core::string( (*(std::string*)this)+(std::string const&)s );
            }

            operator char() const {
                assert(size() == 1);
                return (*this)[0];
            }

            operator long int() const { // Allows implicit conversion without loosing bool conversion
                char *endptr;
                long int res = strtol(data(), &endptr,10);
                if(endptr == data()) {
                    std::ostringstream err;
                    err << "invalid literal for long() with base 10:"
                        << "'" << *this << "'";
                    throw std::runtime_error(err.str());
                }
                return res;
            }
            operator double() const {
                char *endptr;
                double res = strtod(data(), &endptr);
                if(endptr == data()) {
                    std::ostringstream err;
                    err << "invalid literal for double():"
                        << "'" << *this << "'";
                    throw std::runtime_error(err.str());
                }
                return res;
            }
            string& operator=(string_view const & other) {
                if(other.get_data() == *this ) {
                    auto it = std::copy(other.begin(), other.end(), this->begin());
                    this->resize(it - this->begin());
                }
                else {
                    *this=other.get_data();
                }
                return *this;
            }
            using std::string::operator+=;
            string& operator+=(string_view const & other) {
                resize(size() + other.get_data().size());
                std::copy(other.begin(), other.end(), begin());
                return *this;
            }
            bool operator==(string_view const & other) {
                if(length() != other.size())
                    return false;
                for(int i=other.get_slice().lower, j=0;i<other.get_slice().upper;i+=other.get_slice().step, j++)
                    if(other.get_data()[i] != (*this)[j])
                        return false;
                return true;
            }
            string_view operator()( slice const &s) const {
                return string_view(*const_cast<string*>(this), s); // SG: ugly !
            }

            using std::string::operator[];
            string operator[]( slice const &s ) const {
                string out;
                out.reserve(size());
                long lower, upper;
                if(s.step<0) {
                    if( s.lower == std::numeric_limits<long>::max() )
                        lower = size()-1;
                    else
                        lower = s.lower >= 0L ? s.lower : ( s.lower + size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + size());
                    upper = std::min(upper, (long)size());
                    for(long iter = lower; iter >= upper ; iter+=s.step)
                        out.push_back((*this)[iter]);
                }
                else {
                    lower = s.lower >= 0L ? s.lower : ( s.lower + size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + size());
                    upper = std::min(upper, (long)size());
                    for(long iter = lower; iter < upper ; iter+=s.step)
                        out.push_back((*this)[iter]);
                }
                return out;
            }

            explicit operator bool() const{
                return not empty();
            }
            template<class A>
                core::string operator%(A const & a) const {
                    const boost::format fmter(*this);
                    return (boost::format(fmter) % a ).str();
                }
            template<class ...A>
                core::string operator%(std::tuple<A...> const & a) const {
                    boost::format fmter(*this);
                    (fmt(fmter, a, int_<sizeof...(A)>() ));
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
    }
}

pythonic::core::string operator*(pythonic::core::string const & s, long t) {
    size_t n=t;
    pythonic::core::string other;
    other.resize(s.size()*n,'a');
    auto where = other.begin();
    for(size_t i=0;i<n; i++, where+=s.size())
        std::copy(s.begin(), s.end(), where);
    return other;
}

pythonic::core::string operator*(long t, pythonic::core::string const & s) {
    return s*t;
}

/* string_view implementation */
pythonic::core::string_view::string_view(string & other, slice const &s) :
    data(other), slicing(s)
{
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
    else
    {
        lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
        slicing.lower = std::max(0L,lower);
        upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
        slicing.upper = std::min(upper, (long)data->size());
    }
}

pythonic::core::string_view& pythonic::core::string_view::operator=(pythonic::core::string_view const & s) {
    slicing=s.slicing;
    data=s.data;
    return *this;
}

pythonic::core::string_view& pythonic::core::string_view::operator=(pythonic::core::string const & seq) {
    long lower = slicing.lower >= 0L ? slicing.lower : ( slicing.lower + data->size());
    lower = std::max(0L,lower);
    long upper = slicing.upper >= 0L ? slicing.upper : ( slicing.upper + data->size());
    upper = std::min(upper, (long)data->size());
    typename pythonic::core::string::iterator it = data->begin(); 
    if( slicing.step == 1) {
        data->erase(it+lower, it + upper);
        data->insert(it+lower, seq.begin(), seq.end());
    }
    else {
        assert("not implemented yet");
    }
    return *this;
}

pythonic::core::string pythonic::core::string_view::operator+(pythonic::core::string_view const & s) {
    pythonic::core::string out(*data);
    std::copy(s.begin(), s.end(), std::copy(begin(), end(), out.begin()));
    return out;
}

pythonic::core::string_view::operator long() {
    long out;
    std::istringstream iss(pythonic::core::string(*this));
    iss >> out;
    return out;
}

namespace std {
    template <> struct hash<pythonic::core::string>
    {
        size_t operator()(const pythonic::core::string & x) const
        {
            return hash<std::string>()(x);
        }
    };
}

/* std::get overload */
namespace std {
    template <size_t I>
        typename pythonic::core::string get( pythonic::core::string const &t) { return pythonic::core::string(t[I]); }

    template <size_t I>
        struct tuple_element<I, pythonic::core::string > {
            typedef typename pythonic::core::string type;
        };
}

#endif

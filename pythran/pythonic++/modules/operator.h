#ifndef PYTHONIC_MODULE_OPERATOR_H
#define PYTHONIC_MODULE_OPERATOR_H

#define WRAPPER(fname, lname) \
        template <class ... C> auto fname(C... args) -> decltype(lname(args...)) { return lname(args...); } \
        PROXY(pythonic::operator_, fname);\
        PROXY(pythonic::operator_, lname);

namespace pythonic {
    namespace operator_ {
        template <class A, class B>
            bool lt(A const& a, B const& b) {
                return a<b;
            }

        WRAPPER(__lt__, lt)

        template <class A, class B>
            bool le(A const& a, B const& b) {
                return a<=b;
            }

        WRAPPER(__le__, le)

        template <class A, class B>
            bool eq(A const& a, B const& b) {
                return a==b;
            }

        WRAPPER(__eq__, eq)

        template <class A, class B>
            bool ne(A const& a, B const& b) {
                return         a!=b;
            }

        WRAPPER(__ne__, ne)

        template <class A, class B>
            bool ge(A const& a, B const& b) {
                return a>=b;
            }

        WRAPPER(__ge__, ge)

        template <class A, class B>
            bool gt(A const& a, B const& b) {
                return a>b;
            }

        WRAPPER(__gt__, gt)

        bool not_(bool const& a) {
            return !a;
        }

        WRAPPER(__not__, not_)

        bool truth(bool const& a) {
            return a;
        }

        template <class A, class B>
            bool is_(A const& a, B const& b) {
                return a==b;
            }

        template <class A, class B>
            bool is_not(A const& a, B const& b) {
                return a != b;
            }

        template <class A>
            auto __abs__(A const& a) -> decltype(abs(a)) {
                return abs(a);
            }

        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a+b) {
                return a+b;
            }

        WRAPPER(__add__, add)

        template <class A, class B>
            auto and_(A const& a, B const& b) -> decltype(a&b){
                return a&b;
            }

        WRAPPER(__and__, and_)

        template <class A, class B>
            auto div(A const& a, B const& b) -> decltype(a/b){
                if (b==0)
                {
                    throw __builtin__::ZeroDivisionError("Division by zero !");
                }
                return a/b;
            }

        WRAPPER(__div__, div)

        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(a/b){
                if (b==0)
                {
                    throw __builtin__::ZeroDivisionError("Division by zero !");
                }
                return (a-(a % b))/b;
            }

        WRAPPER(__floordiv__, floordiv)

        template <class A>
            A inv(A const& a) {
                return ~a;
            }

        WRAPPER(__inv__, inv)

        template <class A>
            A invert(A const& a) {
                return ~a;
            }

        WRAPPER(__invert__, invert)

        template <class A>
            A lshift(A const& a, int const& b) {
                return a<<b;
            }

        WRAPPER(__lshift__, lshift)

        template <class A, class B>
            int mod(A const& a, B const& b) {
                return a%b;
            }

        WRAPPER(__mod__, mod)

        template <class A, class B>
            auto mul(A const& a, B const& b) -> decltype(a*b) {
                return a*b;
            }

        WRAPPER(__mul__, mul)

        template <class A>
            A neg(A const& a) {
                return -a;
            }

        WRAPPER(__neg__, neg)

        template <class A, class B>
            auto or_(A const& a, B const& b) -> decltype(a|b) {
                return a|b;
            }

        WRAPPER(__or__, or_)

        template <class A>
            A pos(A const& a) {
                return +a;
            }

        WRAPPER(__pos__, pos)

        template <class A, class B>
            auto rshift(A const& a, B const& b) -> decltype(a>>b) {
                return a>>b;
            }

        WRAPPER(__rshift__, rshift)

        template <class A, class B>
            auto sub(A const& a, B const& b) -> decltype(a-b) {
                return a-b;
            }

        WRAPPER(__sub__, sub)

        template <class A, class B>
            auto truediv(A const& a, B const& b) -> decltype(a/(double)b) {
                return a/((double)b);
            }

        WRAPPER(__truediv__, truediv)

        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b) {
                return a^b;
            }

        template <class A, class B>
            auto concat(A const& a, B const& b) -> decltype(a+b) {
                return a+b;
            }

        WRAPPER(__concat__, concat)

        template <class A, class B>
            A iadd(A a, B const& b) {
                return a+=b;
            }

        template <class A>
        auto iadd(pythonic::core::empty_list a, pythonic::core::list<A> b) -> decltype(b) {
            return b;
        }

        template <class K, class V>
        auto iadd(pythonic::core::empty_dict a, pythonic::core::dict<K, V> b) -> decltype(b) {
            return b;
        }

        template <class A>
        auto iadd(pythonic::core::empty_set a, pythonic::core::set<A> b) -> decltype(b) {
            return b;
        }


        WRAPPER(__iadd__, iadd)

        template <class A, class B>
            A iand(A  a, B const& b) {
                return a&=b;
            }

        WRAPPER(__iand__, iand)

        template <class A, class B>
            A iconcat(A  a, B const& b) {
                return a+=b;
            }

        template <class A>
        auto iconcat(pythonic::core::empty_list a, pythonic::core::list<A> b) -> decltype(b) {
            return b;
        }

        template <class K, class V>
        auto iconcat(pythonic::core::empty_dict a, pythonic::core::dict<K, V> b) -> decltype(b) {
            return b;
        }

        template <class A>
        auto iconcat(pythonic::core::empty_set a, pythonic::core::set<A> b) -> decltype(b) {
            return b;
        }


        WRAPPER(__iconcat__, iconcat)

        template <class A, class B>
            A idiv(A a, B const& b) {
                return a /= b;
            }

        WRAPPER(__idiv__, idiv)

        template <class A, class B>
            A ifloordiv(A a, B const& b) {
                A tmp = (a-(a % b))/b;
                a = tmp;
                return tmp;
            }

       WRAPPER(__ifloordiv__, ifloordiv)

        template <class A, class B>
            A ilshift(A a, B const& b) {
                return a <<= b;
            }
        
        WRAPPER(__ilshift__, ilshift)


        template <class A, class B>
            A imod(A a, B const& b) {
    	        return a%=b;
            }

        WRAPPER(__imod__, imod)

        template <class A, class B>
            A imul(A a, B const& b) {
            	return a*=b;
            }

        WRAPPER(__imul__, imul)

        template <class A, class B>
            A ior(A a, B const& b) {
    	        return a|=b;
            }

        WRAPPER(__ior__, ior)

        template <class A, class B>
            A ipow(A a, B const& b) {
            	return a = pow(a,b);
            }

        WRAPPER(__ipow__, ipow)

        template <class A, class B>
            A irshift(A a, B const& b) {
    	        return a>>=b;
            }

        WRAPPER(__irshift__, irshift)

        template <class A, class B>
            A isub(A a, B const& b) {
            	return a-=b;
            }

        WRAPPER(__isub__, isub)

        template <class A, class B>
            auto itruediv(A  a, B const& b) ->decltype(truediv(a,b)) {
                auto tmp = a;
                a = truediv(a,b);
    	        return truediv(tmp,b);
            }

        WRAPPER(__itruediv__, itruediv)

        template <class A, class B>
            A ixor(A a, B const& b) {
            	return a^=b;
            }

        WRAPPER(__ixor__, ixor)


        template <class A, class B>
            bool contains(A const& a, B const& b) {
    	        return in(a, b);
            }

        WRAPPER(__contains__, contains)

        template <class A, class B>
            long countOf(A const& a, B const& b) {
            	return std::count(a.begin(), a.end(), b);
            }

        template <class A, class B>
            none_type delitem(A&& a, B const& b) {
                a.remove(b);
                return None;
            }

        WRAPPER(__delitem__, delitem)

        template <class A, class B>
            auto getitem(A const& a, B const& b) -> decltype(a[b]) {
        	    return a[b];
            }

        WRAPPER(__getitem__, getitem)

        template <class A, class B>
            long indexOf(A const& a, B const& b) {
        	    return a.index(b);
            }

        struct itemgetter_return {
            long i;
            itemgetter_return(long const& item=-1) : i(item){}
            template<class A>
                auto operator()(A const& a) const -> decltype(a[i]) {
                    return a[i];
                }
        };


        itemgetter_return itemgetter(long item)
        {
            return itemgetter_return(item);
        }

        template<typename... Types>
        struct itemgetter_tuple_return {
         
            std::tuple<Types...> items;
         
            itemgetter_tuple_return(Types... items) : items(items...) {
            }
            
            itemgetter_tuple_return(){
            }
         
            template<class T, class A, int I>
                void helper(T & t, A const& a, int_<I>) const {
                    std::get<I>(t) = a[std::get<I>(items)];
                    helper(t,a, int_<I-1>());
                }
            template<class T, class A>
                void helper(T& t, A const& a, int_<0>) const {
                    std::get<0>(t) = a[std::get<0>(items)];
                }
         
            template<class A>
                auto operator()(A const& a) const -> std::tuple< typename std::remove_cv<typename std::remove_reference<decltype(a[std::declval<Types>()])>::type>::type ... > {
                    std::tuple< typename std::remove_cv<typename std::remove_reference<decltype(a[std::declval<Types>()])>::type>::type ... > t;
                    helper(t, a, int_<sizeof...(Types)-1>());
                    return t;
                }
        };
         
        template<class... L>
        auto itemgetter(long const& item1, long const& item2, L ... items) -> itemgetter_tuple_return<long,long, L...>
        {
            return itemgetter_tuple_return<long,long , L...>(item1, item2, items...);
        }


        PROXY(pythonic::operator_, truth);
        PROXY(pythonic::operator_, __abs__);
        PROXY(pythonic::operator_, __xor__);
        PROXY(pythonic::operator_, is_);
        PROXY(pythonic::operator_, is_not);
        PROXY(pythonic::operator_, countOf);
        PROXY(pythonic::operator_, indexOf);
        PROXY(pythonic::operator_, itemgetter);
    }

}

#endif

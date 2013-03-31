#ifndef PYTHONIC_MODULE_OPERATOR_H
#define PYTHONIC_MODULE_OPERATOR_H

#define WRAPPER2ARGS(fname, lname) \
        template <class A, class B> auto fname(A const& a, B const& b) -> decltype(lname(a, b)) { return lname(a, b); } \
        PROXY(pythonic::operator_, fname);\
        PROXY(pythonic::operator_, lname);

#define IWRAPPER2ARGS(fname, lname) \
        template <class A, class B> auto fname(A  a, B const& b) -> decltype(lname(a, b)) { return lname(a, b); }\
    PROXY(pythonic::operator_, fname);\
        PROXY(pythonic::operator_, lname);
 

#define WRAPPER1ARG(fname, lname) \
        template <class A> auto fname(A const& a) -> decltype(lname(a)) { return lname(a); } \
        PROXY(pythonic::operator_, fname);\
        PROXY(pythonic::operator_, lname);

namespace pythonic {
    namespace operator_ {
        template <class A, class B>
            bool lt(A const& a, B const& b) {
                return a<b;
            }

          WRAPPER2ARGS(__lt__, lt)

        template <class A, class B>
            bool le(A const& a, B const& b) {
                return a<=b;
            }

          WRAPPER2ARGS(__le__, le)

        template <class A, class B>
            bool eq(A const& a, B const& b) {
                return a==b;
            }

          WRAPPER2ARGS(__eq__, eq)

        template <class A, class B>
            bool ne(A const& a, B const& b) {
                return         a!=b;
            }

          WRAPPER2ARGS(__ne__, ne)

        template <class A, class B>
            bool ge(A const& a, B const& b) {
                return a>=b;
            }

          WRAPPER2ARGS(__ge__, ge)

        template <class A, class B>
            bool gt(A const& a, B const& b) {
                return a>b;
            }

          WRAPPER2ARGS(__gt__, gt)

        bool not_(bool const& a) {
            return !a;
        }

          WRAPPER1ARG(__not__, not_)

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

          WRAPPER2ARGS(__add__, add)

        template <class A, class B>
            auto and_(A const& a, B const& b) -> decltype(a&b){
                return a&b;
            }

          WRAPPER2ARGS(__and__, and_)

        template <class A, class B>
            auto div(A const& a, B const& b) -> decltype(a/b){
                if (b==0)
                {
                    throw __builtin__::ZeroDivisionError("Division by zero !");
                }
                return a/b;
            }

          WRAPPER2ARGS(__div__, div)

        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(a/b){
                if (b==0)
                {
                    throw __builtin__::ZeroDivisionError("Division by zero !");
                }
                return (a-(a % b))/b;
            }

          WRAPPER2ARGS(__floordiv__, floordiv)

        template <class A>
            A inv(A const& a) {
                return ~a;
            }

          WRAPPER1ARG(__inv__, inv)

        template <class A>
            A invert(A const& a) {
                return ~a;
            }

          WRAPPER1ARG(__invert__, invert)

        template <class A>
            A lshift(A const& a, int const& b) {
                return a<<b;
            }

          WRAPPER2ARGS(__lshift__, lshift)

         int mod(int const& a, int const& b) {
                return a%b;
            }

          WRAPPER2ARGS(__mod__, mod)

        template <class A, class B>
            auto mul(A const& a, B const& b) -> decltype(a*b) {
                return a*b;
            }

          WRAPPER2ARGS(__mul__, mul)

        template <class A>
            A neg(A const& a) {
                return -a;
            }

          WRAPPER1ARG(__neg__, neg)

        template <class A, class B>
            auto or_(A const& a, B const& b) -> decltype(a|b) {
                return a|b;
            }

          WRAPPER2ARGS(__or__, or_)

        template <class A>
            A pos(A const& a) {
                return +a;
            }

          WRAPPER1ARG(__pos__, pos)

        template <class A, class B>
            auto rshift(A const& a, B const& b) -> decltype(a>>b) {
                return a>>b;
            }

          WRAPPER2ARGS(__rshift__, rshift)

        template <class A, class B>
            auto sub(A const& a, B const& b) -> decltype(a-b) {
                return a-b;
            }

        WRAPPER2ARGS(__sub__, sub)

        template <class A, class B>
            auto truediv(A const& a, B const& b) -> decltype(a/(double)b) {
                return a/((double)b);
            }

        WRAPPER2ARGS(__truediv__, truediv)

        template <class A, class B>
            auto __xor__(A const& a, B const& b) -> decltype(a^b) {
                return a^b;
            }

        template <class A, class B>
            auto concat(A const& a, B const& b) -> decltype(a+b) {
                return a+b;
            }

        WRAPPER2ARGS(__concat__, concat)

        template <class A, class B>
            A iadd(A a, B const& b) {
                return a+=b;
            }

        IWRAPPER2ARGS(__iadd__, iadd)

        template <class A, class B>
            A iand(A  a, B const& b) {
                return a&=b;
            }

        IWRAPPER2ARGS(__iand__, iand)

        template <class A, class B>
            A iconcat(A  a, B const& b) {
                return a+=b;
            }

        IWRAPPER2ARGS(__iconcat__, iconcat)

        template <class A, class B>
            A idiv(A a, B const& b) {
                return a /= b;
            }

        IWRAPPER2ARGS(__idiv__, idiv)

        template <class A, class B>
            A ifloordiv(A a, B const& b) {
                A tmp = (a-(a % b))/b;
                a = tmp;
                return tmp;
            }

       IWRAPPER2ARGS(__ifloordiv__, ifloordiv)

        template <class A, class B>
            A ilshift(A a, B const& b) {
                return a <<= b;
            }
        
        IWRAPPER2ARGS(__ilshift__, ilshift)


        template <class A, class B>
            A imod(A a, B const& b) {
    	        return a%=b;
            }

        IWRAPPER2ARGS(__imod__, imod)

        template <class A, class B>
            A imul(A a, B const& b) {
            	return a*=b;
            }

        IWRAPPER2ARGS(__imul__, imul)

        template <class A, class B>
            A ior(A a, B const& b) {
    	        return a|=b;
            }

        IWRAPPER2ARGS(__ior__, ior)

        template <class A, class B>
            A ipow(A a, B const& b) {
            	return a = pow(a,b);
            }

        IWRAPPER2ARGS(__ipow__, ipow)

        template <class A, class B>
            A irshift(A a, B const& b) {
    	        return a>>=b;
            }

        IWRAPPER2ARGS(__irshift__, irshift)

        template <class A, class B>
            A isub(A a, B const& b) {
            	return a-=b;
            }

        IWRAPPER2ARGS(__isub__, isub)

        template <class A, class B>
            A itruediv(A  a, B const& b) {
    	        return a/=b;
            }

        IWRAPPER2ARGS(__itruediv__, itruediv)

        template <class A, class B>
            A ixor(A a, B const& b) {
            	return a^=b;
            }

        IWRAPPER2ARGS(__ixor__, ixor)


        template <class A, class B>
            bool contains(A const& a, B const& b) {
    	        return 0 <= a.index(b) && a.index(b) < a.size();
            }

        WRAPPER2ARGS(__contains__, contains)

        template <class A, class B>
            long countOf(A const& a, B const& b) {
            	return std::count(a.begin(), a.end(), b);
            }

        template <class A, class B>
            void delitem(A const& a, B const& b) {
            	try {
                    	a.remove(b);
    	        }
            	catch (std::exception& e)
            	{
    	        	std::cout << "Can't remove intem :" << e.what() << std::endl;
        	    }
            }

        WRAPPER2ARGS(__delitem__, delitem)

        template <class A, class B>
            auto getitem(A const& a, B const& b) -> decltype(a[b]) {
        	    return a[b];
            }

        WRAPPER2ARGS(__getitem__, getitem)

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

        struct itemgetter_tuple_return {
            pythonic::core::list<long> items_list;
            template<typename... L>
            itemgetter_tuple_return(long const& item, L ...  items)
            {
                items_list.push_back(item);
                itemgetter_tuple_return(items...);
            }

            itemgetter_tuple_return(){ }

            template<class A>
                int operator()(A const& a) const {//-> decltype(std::make_tuple(a[items_list[0]])) {
                    //auto result = std::make_tuple(a[items_list[0]]);
                        int result = 1;
//                    for (auto i = items_list.begin()+1; i!= items_list.end(); i++)
//                        result = std::tuple_cat(result, std::make_tuple(a[*i]);
                    return result;
                }
            int operator()() const { return -1;}
        };

        itemgetter_return itemgetter(long item)
        {
            return itemgetter_return(item);
        }

        template<class... L>
        itemgetter_tuple_return itemgetter(long const& item1, long const& item2, L ... items)
        {
            return itemgetter_tuple_return(item1, item2, items...);
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

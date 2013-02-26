#ifndef PYTHONIC_MODULE_OPERATOR_H
#define PYTHONIC_MODULE_OPERATOR_H

namespace pythonic {
    namespace operator_ {
	template <class A, class B>
            bool lt(A const& a, B const& b) {
                return a<b;
            }

	template <class A, class B>
            bool le(A const& a, B const& b) {
                return a<=b;
            }

	template <class A, class B>
            bool eq(A const& a, B const& b) {
                return a==b;
            }

        template <class A, class B>
            bool ne(A const& a, B const& b) {
		return 	a!=b;
            }

        template <class A, class B>
            bool ge(A const& a, B const& b) {
		return a>=b;
            }

        template <class A, class B>
            bool gt(A const& a, B const& b) {
		return a>b;
            }

        template <class A, class B>
            bool __lt__(A const& a, B const& b) {
		return a<b;
            }

        template <class A, class B>
            bool __le__(A const& a, B const& b) {
		return a<=b;
            }

        template <class A, class B>
            bool __eq__(A const& a, B const& b) {
		return a==b;
            }

        template <class A, class B>
            bool __ne__(A const& a, B const& b) {
		return a!=b;
            }

        template <class A, class B>
            bool __ge__(A const& a, B const& b) {
		return a>=b;
            }

        template <class A, class B>
            bool __gt__(A const& a, B const& b) {
		return a>b;
            }

        bool not_(bool const& a) {
	    return !a;
        }

        bool __not__(bool const& a) {
	    return !a;
        }

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

	using std::abs;

        template <class A>
            A __abs__(A const& a) {
		return abs(a);
            }

        template <class A, class B>
            auto __add__(A const& a, B const& b) -> decltype(a+b) {
		return a+b;
            }

        template <class A, class B>
            auto add(A const& a, B const& b) -> decltype(a+b) {
		return __add__(a+b);
            }


        template <class A, class B>
            auto and_(A const& a, B const& b) -> decltype(a&b){
		return a&b;
            }

        template <class A, class B>
            auto __and__(A const& a, B const& b) -> decltype(a&b){
		return a&b;
            }

        template <class A, class B>
            auto div(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return a/b;
            }

        template <class A, class B>
            auto __div__(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return a/b;
            }

        template <class A, class B>
            auto floordiv(A const& a, B const& b) -> decltype(a/b){
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return (a-(a % b))/b;
            }

        template <class A, class B>
            auto __floordiv__(A const& a, B const& b) -> decltype(a/b) { 
		if (b==0)
		{
                    throw ZeroDivisionError("Division by zero impossible !");
		}
		return (a-(a % b))/b;
            }

        PROXY(pythonic::operator_, lt);
        PROXY(pythonic::operator_, le);
        PROXY(pythonic::operator_, eq);
	PROXY(pythonic::operator_, ne);
        PROXY(pythonic::operator_, ge);
        PROXY(pythonic::operator_, gt);
        PROXY(pythonic::operator_, __lt__);
        PROXY(pythonic::operator_, __le__);
        PROXY(pythonic::operator_, __eq__);
        PROXY(pythonic::operator_, __ne__);
        PROXY(pythonic::operator_, __ge__);
        PROXY(pythonic::operator_, __gt__);
        PROXY(pythonic::operator_, not_);
        PROXY(pythonic::operator_, __not__);
        PROXY(pythonic::operator_, truth);
        PROXY(pythonic::operator_, is_);
        PROXY(pythonic::operator_, is_not);
        PROXY(pythonic::operator_, abs);
        PROXY(pythonic::operator_, __abs__);
        PROXY(pythonic::operator_, add);
        PROXY(pythonic::operator_, __add__);
        PROXY(pythonic::operator_, and_);
        PROXY(pythonic::operator_, __and__);
        PROXY(pythonic::operator_, div);
        PROXY(pythonic::operator_, __div__);
        PROXY(pythonic::operator_, floordiv);
        PROXY(pythonic::operator_, __floordiv__);
    }

}

#endif

#include <pythonic++.h>
using namespace pythonic;

int main() {
    long r = 0;
    for(auto i : range(5)) r+=i;
    return !( r == 10 );
}

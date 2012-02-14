#include <pythonic++.h>
using namespace pythonic;

int main() {
    auto n= None;
    int i=3;
    none<int> j = 5;
    j = j + i;
    j = None;
    return j == None;
}


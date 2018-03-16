run_tests() {
    if [ -n "$PEP8" ]
    then
        PYTHONPATH=$PWD:$PYTHONPATH py.test pythran --pep8 -m pep8
    fi
    if [ "$PYTHON_VERSION" = 2 -a "$TRAVIS_PYTHON_VERSION" = 3.5 ]
    then
        exit
    fi
    if [ -n "$NOTEBOOK" ]
    then
        PYTHONPATH=$PWD:$PYTHONPATH py.test pythran/tests/notebooks --nbval
        exit
    fi
    printf "[compiler]\nCXX=$CXX\nCC=$CC\ncflags=-std=c++11 $CXXFLAGS -w\nldflags=$CXXFLAGS\n" > ~/.pythranrc
    OMP_NUM_THREADS=4 PYTHONPATH=$PWD:$PYTHONPATH py.test -v $TESTCASE
}

# Test with both clang and gcc
# Only gcc can test openMP, and travis does not support gcc when gcc uses too much memory
# So some tests have been commented out, as it is useless to compile them with clang
if [ -z "$MODE"]
then
    CC=clang-3.5 CXX=clang++-3.5 CXXFLAGS="-g" run_tests
    CC=clang-3.5 CXX=clang++-3.5 CXXFLAGS="-DUSE_BOOST_SIMD -march=native" run_tests
    CC=gcc-5 CXX=g++-5 CXXFLAGS="-fopenmp" run_tests
    CC=gcc-5 CXX=g++-5 CXXFLAGS="-DUSE_BOOST_SIMD -march=native -fopenmp" run_tests
else
    case $MODE in
        seq)
            CC=clang-3.5 CXX=clang++-3.5 CXXFLAGS="-g" run_tests
            ;;
        vec)
            CC=clang-3.5 CXX=clang++-3.5 CXXFLAGS="-DUSE_BOOST_SIMD -march=native" run_tests
            ;;
        omp)
            CC=gcc-5 CXX=g++-5 CXXFLAGS="-fopenmp" run_tests
            ;;
        all)
            CC=gcc-5 CXX=g++-5 CXXFLAGS="-DUSE_BOOST_SIMD -march=native -fopenmp" run_tests
            ;;
    esac
fi

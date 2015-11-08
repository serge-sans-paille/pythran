#!/bin/sh
. ./config.dat
LAB=.lab
rm -rf ${LAB}
mkdir ${LAB}
cd ${LAB}

wget ${BOOST_URL} -O boost.tar.bz2
tar xjf boost.tar.bz2
cd boost_*
export BOOST_ROOT=$PWD
sh bootstrap.sh
./bjam tools/bcp
cd ..


wget ${NT2_URL} -O nt2.zip
unzip nt2.zip
cd nt2-*
cmake -DCMAKE_INSTALL_PREFIX=install
make
make install
cp -r install/include/* ../..

cd $BOOST_ROOT

$BOOST_ROOT/dist/bin/bcp ${BOOSTDEPS} ../..

cd ../..
rm -rf ${LAB}
rm -rf libs boost.css boost.png doc Jamroot  rst.css  usr/

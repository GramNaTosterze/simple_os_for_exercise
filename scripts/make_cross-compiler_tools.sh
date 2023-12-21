#!/bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

mkdir $HOME/src
# clone tool src
git clone git://sourceware.org/git/binutils-gdb.git src/binutils-gdb
git clone git://gcc.gnu.org/git/gcc.git src/gcc


# make binutils
cd $HOME/src
mkdir build-binutils
cd build-binutils
pwd
../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
#make distclean
make
make install

# make gcc
cd $HOME/src
which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
#make clean
#make distclean
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

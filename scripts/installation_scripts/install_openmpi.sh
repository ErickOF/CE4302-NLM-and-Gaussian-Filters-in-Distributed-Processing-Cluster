#!/bin/sh

OPENMPI_DIR=openmpi

# Install curl to download open-mpi
sudo apt-get install curl

# Creating build directory
if [ ! -d $HOME/$OPENMPI_DIR ]; then
	mkdir $HOME/$OPENMPI_DIR;
fi

# Download OpenMPI
curl https://download.open-mpi.org/release/open-mpi/v4.0/openmpi-4.0.4.tar.gz --output openmpi-4.0.4.tar.gz
mv ./openmpi-4.0.4.tar.gz $HOME/$OPENMPI_DIR/openmpi-4.0.4.tar.gz
cd $HOME/$OPENMPI_DIR/
tar -xzvf openmpi-4.0.4.tar.gz
cd openmpi-4.0.4

# Installing tools
sudo apt-get install build-essential

# Configure OpenMPI installation
./configure --prefix=$HOME/openmpi

# Compile OpenMPI
make all

# Install OpenMPI
make install

# Complementaries packages for OpenMPI
sudo apt-get install openmpi-bin
sudo apt-get install libopenmpi-dev

# Add OpenMPI to PATH and LD_LIBRARY PATH system vars
export PATH=$PATH:$HOME/$OPENMPI_DIR/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/$OPENMPI_DIR/lib

# Test
mpicc -v

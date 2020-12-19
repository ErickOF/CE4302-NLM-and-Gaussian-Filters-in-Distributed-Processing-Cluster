#!/bin/sh

MPI_HOSTFILE=mpi_hostfile

echo "# Master " > $HOME/.$MPI_HOSTFILE
echo "localhost slots=1" >> $HOME/$MPI_HOSTFILE
echo "# Slave1" >> $HOME/$MPI_HOSTFILE
echo "slave1 slots=1" >> $HOME/$MPI_HOSTFILE

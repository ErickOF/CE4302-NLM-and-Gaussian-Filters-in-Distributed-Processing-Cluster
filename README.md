# **CE4302-NLM-and-Gaussian-Filters-in-Distributed-Processing-Cluster**

## **Overview**
Implementation of the Non-Local Means (NLM) and the Gaussian filter with OpenMPI in a distributed processing cluster with one master and two slave nodes

## **Dependencies**
* [GNU Make 4.1](https://www.gnu.org/software/make/)
* [stb](https://github.com/nothings/stb) - for image manipulation


## **How to use**
### **Non-Local Means Filter**
* *nlm images="path/to/image1 path/to/image2...":* build, run and clean in the master node.
* *nlm-mpi images="path/to/image1 path/to/image2...":* build, run and clean in the cluster.

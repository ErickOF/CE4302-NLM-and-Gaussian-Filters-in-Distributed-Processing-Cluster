# **CE4302-NLM-and-Gaussian-Filters-in-Distributed-Processing-Cluster**

## **Overview**
Implementation of the Non-Local Means (NLM) and the Gaussian filter with OpenMPI in a distributed processing cluster with one master and two slave nodes

## **Dependencies**
* [GNU Make 4.1](https://www.gnu.org/software/make/)
* [stb](https://github.com/nothings/stb) - for image manipulation


## **How to use**
### **Non-Local Means Filter**

```shell
make nlm w=3 sw=5 sigma=2.5 imgs="img1 img2 img3 etc"
```

```shell
make nlm-mpi w=3 sm=5 sigma=2.5 imgs="img1 img2 img3 etc"
```


### **Gaussian Filter**

```shell
make gaussian w=5 sigma=1.5 imgs="img1 img2 img3 etc"
```

```shell
make gaussian-mpi w=5 sigma=1.5 imgs="img1 img2 img3 etc"
```


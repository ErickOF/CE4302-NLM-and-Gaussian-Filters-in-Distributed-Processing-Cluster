# **CE4302-NLM-and-LoG-in-Distributed-Processing-Cluster**

## **Overview**
Implementation of the Non-Local Means (NLM) and the Laplacian of Gaussian (LoG) filter with OpenMPI in a distributed processing cluster with one master and two slave nodes

## **Dependencies**
* [GNU Make 4.1](https://www.gnu.org/software/make/)
* [stb](https://github.com/nothings/stb) - for image manipulation


## **How to use**
### **Non-Local Means Filter**
* *build-nlm:* build the filter.
* *run-nlm:* run the filter. Error if the file wasn't built.
* *clean-nlm:* clean the output file.
* *all-nlm:* build, run and clean.

### **Laplacian of Gaussian Filter**
* *build-log:* build the filter.
* *run-log:* run the filter. Error if the file wasn't built.
* *clean-log:* clean the output file.
* *all-log:* build, run and clean.

### **All**
* *build-all:* build the NLM and LoG filters.
* *clean-all:* clean the output files of the NLM and the LoG filters.
* *run-all:* run the NLM and the LoG filters. Error if the files weren't built.
* *all:* do all above.

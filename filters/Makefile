# Compiler for normal C files
CC=gcc
# Compiler for C files that use OpenMPI
CC_MPI=mpicc
# Execute the OpenMPI code with three nodes
MPIEXEC=mpiexec -np 3


# Output folder
OUTPUT_DIR=outputs/

# Files
NLM_FILE=nlm
NLM_C=$(NLM_FILE).c

NLM_MPI_FILE=nlm-mpi
NLM_MPI_C=$(NLM_MPI_FILE).c

GAUSSIAN_FILE=gaussian
GAUSSIAN_C=$(GAUSSIAN_FILE).c

GAUSSIAN_MPI_FILE=gaussian-mpi
GAUSSIAN_MPI_C=$(GAUSSIAN_MPI_FILE).c

# Use math library
FLAGS=-lm

# Test
# Test1 - 5 images
TEST_IMGS1=src/01.png src/02.png src/03.png src/04.png src/05.png
# Test2 - 10 images
TEST_IMGS2=$(TEST_IMGS1) src/06.png src/07.png src/08.png src/09.png src/10.png
# Test3 - 20 images
TEST_IMGS3=$(TEST_IMGS2) src/11.png src/12.png src/12.png src/13.png src/14.png src/15.png src/16.png src/17.png src/18.png src/19.png src/20.png
# Standard Deviation
STDDEV_GAUSSIAN=2.0
STDDEV_NLM=3.5
# Window Size
WIN_SIZE_GAUSSIAN=9
WIN_SIZE_NLM=5
# Similarity Window Size (NLM)
SIM_WIN_SIZE=7



# Non-Local Means Filter
nlm:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(NLM_FILE) $(w) $(sw) $(sigma) $(imgs)
		rm -f $(NLM_FILE)

# Non-Local Means Filter with OpenMPI
nlm-mpi:
		$(CC_MPI) -o $(NLM_MPI_FILE) $(NLM_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(NLM_MPI_FILE) $(w) $(sw) $(sigma) $(imgs)
		rm -f $(NLM_MPI_FILE)


# Test: Non-Local Means Filter
test-nlm1:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(NLM_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS1)
		rm -f $(NLM_FILE)

test-nlm2:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(NLM_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS2)
		rm -f $(NLM_FILE)

test-nlm3:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(NLM_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS3)
		rm -f $(NLM_FILE)


# Test: Non-Local Means Filter with OpenMPI
test-nlm-mpi1:
		$(CC_MPI) -o $(NLM_MPI_FILE) $(NLM_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(NLM_MPI_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS1)
		rm -f $(NLM_MPI_FILE)

test-nlm-mpi2:
		$(CC_MPI) -o $(NLM_MPI_FILE) $(NLM_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(NLM_MPI_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS2)
		rm -f $(NLM_MPI_FILE)

test-nlm-mpi3:
		$(CC_MPI) -o $(NLM_MPI_FILE) $(NLM_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(NLM_MPI_FILE) $(WIN_SIZE_NLM) $(SIM_WIN_SIZE) $(STDDEV_NLM) $(TEST_IMGS3)
		rm -f $(NLM_MPI_FILE)



# Gaussian Filter
gaussian:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(GAUSSIAN_FILE) $(w) $(sigma) $(imgs)
		rm -f $(GAUSSIAN_FILE)

# Gaussian Filter with OpenMPI
gaussian-mpi:
		$(CC_MPI) -o $(GAUSSIAN_MPI_FILE) $(GAUSSIAN_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(GAUSSIAN_MPI_FILE) $(w) $(sigma) $(imgs)
		rm -f $(GAUSSIAN_MPI_FILE)


# Test: Gaussian Filter
test-gaussian1:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(GAUSSIAN_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS1)
		rm -f $(GAUSSIAN_FILE)

test-gaussian2:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(GAUSSIAN_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS2)
		rm -f $(GAUSSIAN_FILE)

test-gaussian3:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(GAUSSIAN_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS3)
		rm -f $(GAUSSIAN_FILE)


# Test: Gaussian Filter with OpenMPI
test-gaussian-mpi1:
		$(CC_MPI) -o $(GAUSSIAN_MPI_FILE) $(GAUSSIAN_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(GAUSSIAN_MPI_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS1)
		rm -f $(GAUSSIAN_MPI_FILE)

test-gaussian-mpi2:
		$(CC_MPI) -o $(GAUSSIAN_MPI_FILE) $(GAUSSIAN_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(GAUSSIAN_MPI_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS2)
		rm -f $(GAUSSIAN_MPI_FILE)

test-gaussian-mpi3:
		$(CC_MPI) -o $(GAUSSIAN_MPI_FILE) $(GAUSSIAN_MPI_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time $(MPIEXEC) ./$(GAUSSIAN_MPI_FILE) $(WIN_SIZE_GAUSSIAN) $(STDDEV_GAUSSIAN) $(TEST_IMGS3)
		rm -f $(GAUSSIAN_MPI_FILE)


# Clean the output folder and residual files
clean:
		rm -rf $(OUTPUT_DIR)
		rm -f $(GAUSSIAN_FILE) $(GAUSSIAN_MPI_FILE) $(NLM_FILE) $(NLM_MPI_FILE)


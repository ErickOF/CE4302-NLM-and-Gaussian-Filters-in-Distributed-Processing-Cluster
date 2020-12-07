CC=gcc

# Non-Local Means code
NLM_FILTER=nlm
NLM_FILTER_C=$(NLM_FILTER).c

# Laplacian of Gaussian code
LOG_FILTER=log
LOG_FILTER_C=$(LOG_FILTER).c

# Use math library
FLAGS=-lm


# Non-Local Means Filter
all-nlm: | build-nlm run-nlm clean-nlm

build-nlm:
		$(CC) -o $(NLM_FILTER) $(NLM_FILTER_C) $(FLAGS)

run-nlm:
		./$(NLM_FILTER)

clean-nlm:
		rm -f $(NLM_FILTER)


# Laplacian of Gaussian Filter
all-log: | build-log run-log clean-log

build-log:
		$(CC) -o $(LOG_FILTER) $(LOG_FILTER_C) $(FLAGS)

run-log:
		./$(LOG_FILTER)

clean-log:
		rm -f $(LOG_FILTER)


# Clean all
clean-all: | clean-log clean-log

# Do all
all: | all-nlm all-log

# Build all
build-all: | build-nlm build-log

# Run all
run-all: |run-nlm run-log


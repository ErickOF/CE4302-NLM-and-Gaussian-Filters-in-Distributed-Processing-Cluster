CC=gcc

NLM_FILE=nlm
NLM_C=$(NLM_FILE).c

GAUSSIAN_FILE=gaussian
GAUSSIAN_C=$(GAUSSIAN_FILE).c

# Use math library
FLAGS=-lm


# Non-Local Means Filter
nlm:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p outputs/
		time ./$(NLM_FILE) $(images)
		rm -f $(NLM_FILE)

# Gaussian Filter
gaussian:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p outputs/
		time ./$(GAUSSIAN_FILE) $(images)
		rm -f $(GAUSSIAN_FILE)

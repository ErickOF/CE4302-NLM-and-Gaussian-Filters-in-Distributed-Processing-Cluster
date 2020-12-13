CC=gcc

# Output folder
OUTPUT_DIR=outputs/

# Files
NLM_FILE=nlm
NLM_C=$(NLM_FILE).c

GAUSSIAN_FILE=gaussian
GAUSSIAN_C=$(GAUSSIAN_FILE).c

# Use math library
FLAGS=-lm


# Non-Local Means Filter
nlm:
		$(CC) -o $(NLM_FILE) $(NLM_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(NLM_FILE) $(w) $(sw) $(sigma) $(imgs)
		rm -f $(NLM_FILE)

# Gaussian Filter
gaussian:
		$(CC) -o $(GAUSSIAN_FILE) $(GAUSSIAN_C) $(FLAGS)
		@mkdir -p $(OUTPUT_DIR)
		time ./$(GAUSSIAN_FILE) $(w) $(sigma) $(imgs)
		rm -f $(GAUSSIAN_FILE)

clean:
		rm -rf $(OUTPUT_DIR)
		rm -f $(GAUSSIAN_FILE) $(NLM_FILE)

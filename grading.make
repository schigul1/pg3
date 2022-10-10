SUBMIT_FILES=functions.c functions.h grading.make Makefile \
				solutions.a test.c
SUBMIT_DIR=$(USER)

# Create a directory for submission files
$(SUBMIT_DIR):
	mkdir -p $(USER) 

# Copy submission files, then archive them
$(USER).tar: $(SUBMIT_DIR) $(SUBMIT_FILES)
	cp -v $(SUBMIT_FILES) $<
	tar -cv -f $@ $<

# Create the test run's log file
feedback.log: test
	(date && whoami) | tee -a feedback.log
	$(PWD)/test 2>&1 | tee -a feedback.log

# This is a target for student use.
# It prepares an archive for submitting the assignment
.PHONY: submit
submit: $(USER).tar

# This is a target for grader use to initiate a test run.
# The grader should execute `make -k check` 
# in order to continue past test errors.
.PHONY: check
check: feedback.log

# WARNING: DO NOT CALL THIS UNLESS YOU HAVE ACCESS TO solutions.c
# (i.e. instructors and graders only)
.PHONY:really-clean
really-clean: clean
	rm -fv solutions.a feedback.log

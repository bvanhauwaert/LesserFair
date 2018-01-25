## Begin configurable section
# Application name
APP_NAME := LesserApplication
# Build directory
BUILD_DIR := build
# Compile flags
#  -g add debug information
FLAGS = -g 
# Wt include and lib directory.
WT_INCLUDE_DIR=../../../opt/usr/include
WT_LIB_DIR=../../../opt/usr/lib

## List of C++ source modules
CC_MODULES := \
	LesserApplication \
	Main \
	Player \
	UserInterface

## Make logic
# Executabel name and list of source, object and dependency files. These are
# derived from the list of C++ modules.
EXECUTABLE := $(BUILD_DIR)/$(APP_NAME)
CC_FILES += $(foreach file, $(CC_MODULES), $(file).cc)
CC_OBJECTS += $(foreach ccfile, $(CC_FILES), $(BUILD_DIR)/objects/$(ccfile).o)
CC_DEPS += $(foreach ccfile, $(CC_FILES), $(BUILD_DIR)/deps/$(ccfile).d)
# Set up extra include and link directorys
EXTRA_INCLUDE_DIR=$(foreach inc, ${WT_INCLUDE_DIR}, -I$(inc))
EXTRA_LIB_DIR=$(foreach lib, ${WT_LIB_DIR}, -L$(lib))

## Link rule to build executable from all objects
$(EXECUTABLE): $(CC_OBJECTS) Makefile
		g++ $(FLAGS) $(EXTRA_LIB_DIR) -o $(EXECUTABLE) $(CC_OBJECTS) \
			-lwt -lwthttp -lboost_filesystem -lboost_system -lgmp -lgmpxx -lpthread
		@echo

# Simple rule to run the application
run: $(EXECUTABLE)
		export LD_LIBRARY_PATH=$(foreach lib,${WT_LIB_DIR},$(lib):)$$LD_LIBRARYPATH && \
		 $(EXECUTABLE) --http-address=0.0.0.0 --http-port=8090 --docroot=.

# Clean the executable and all object and dependency files
clean:
	rm $(CC_OBJECTS) $(CC_DEPS) $(EXECUTABLE)

# How to generate an object file from a source file. As a side effect also generate
# a corresponding dependency file
$(BUILD_DIR)/objects/%.cc.o : %.cc Makefile
	@mkdir -p $(@D) $(patsubst $(BUILD_DIR)/objects%,$(BUILD_DIR)/deps%,$(@D))
	g++ $(FLAGS) $(EXTRA_INCLUDE_DIR) -Wall -std=c++14 \
	  	-c $< -o $@ \
	  	-MMD -MF $(patsubst $(BUILD_DIR)/objects/%.o,$(BUILD_DIR)/deps/%.d,$@)
	@echo

# Include all dependency files
-include $(CC_DEPS)

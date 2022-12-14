TARGET 		= cuda 

CC 		= g++
NVCC		= nvcc
LINKER 		= g++ -o 

CUDA_INSTALL_PATH ?= /usr/local/cuda

INCD 		= -I$(CUDA_INSTALL_PATH)/include
LIBS 		= -L$(CUDA_INSTALL_PATH)/lib -lcudart

CFLAGS 		= -W -Wall -Ofast
NFLAGS 		= -O3 --use_fast_math -arch=compute_32
LFLAGS 		=  -Wall -I. -lm -lGL -lGLEW -lSDL2 -lGLU -O3

SRCDIR 		= src
OBJDIR 		= obj
BINDIR 		= bin

SOURCES 	:= $(wildcard $(SRCDIR)/*.cpp) 
SOURCES_CU 	:= $(wildcard $(SRCDIR)/*.cu)
INCLUDES 	:= $(wildcard $(SRCDIR)/*.h)  
INCLUDES_CU := $(wildcard $(SRCDIR)/*.cuh)
OBJECTS 	:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o) 
OBJECTS_CU 	:= $(SOURCES_CU:$(SRCDIR)/%.cu=$(OBJDIR)/%.cuo)
rm 			= rm -f

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS_CU) $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS_CU) $(OBJECTS) $(INCD) $(LIBS) $(LFLAGS) 

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) $(INCD) -c $< -o $@

$(OBJECTS_CU): $(OBJDIR)/%.cuo : $(SRCDIR)/%.cu
	@$(NVCC) $(NFLAGS) $(INCD) -c $< -o $@

.PHONY: clean
clean:
	@$(rm) $(OBJECTS_CU) $(OBJECTS)

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)


# project name (generate executable with this name)
TARGET   = gurux.dlms.server.bin

CC       = g++

# compiling flags here
<<<<<<< HEAD
CFLAGS   = -c -std=c++11
=======
CFLAGS   = -c
>>>>>>> 8a81167e51af2be8751bad437bb068262d8ed2cf

LINKER   = g++ -o

# linking flags here
LFLAGS   = -L../development/lib

# change these to set the proper directories where each files should be

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)

OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS) -lgurux_dlms_cpp -lpthread
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!" 
	@echo $(OBJECTS)

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
<<<<<<< HEAD
	@echo "Executable removed!"
=======
	@echo "Executable removed!"
>>>>>>> 8a81167e51af2be8751bad437bb068262d8ed2cf

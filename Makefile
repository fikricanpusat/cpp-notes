# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17

# Target executable
TARGET := cpp-notes.bin

# Directories
SRCDIR := src
INCDIR := include
BUILDDIR := build

SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
INCS := -I$(INCDIR)

# Build rule
all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCS) -o $@ $^

# Object file compilation
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCS) -c -o $@ $<

# Create build directory if not exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean rule
clean:
	rm -f $(TARGET) $(BUILDDIR)/*.o

.PHONY: all clean

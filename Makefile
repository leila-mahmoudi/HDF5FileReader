# Compiler and flags
CXX := g++
CXXFLAGS := -I/usr/include/hdf5/serial/
LDFLAGS := -L/usr/lib/x86_64-linux-gnu/hdf5/serial -lhdf5_cpp -lhdf5

# Target and source files
TARGET := myprogram
SRCS := main.cpp

# Build rules
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
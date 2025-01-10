CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -Wpedantic	 # The C++ compiler options

TARGET = docserver # Ejecutable

SRCS = docserver.cc # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
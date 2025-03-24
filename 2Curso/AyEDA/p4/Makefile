CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++17	 # The C++ compiler options (C++14)

TARGET = busqueda # Ejecutable

SRCS = main.cc # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
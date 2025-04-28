CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++17	 # The C++ compiler options (C++14)

TARGET = arbol # Ejecutable

SRCS = main.cpp # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)
	$(CXX) $(CXXFLAGS) -o arbolTRAZA $(SRCS) -DTRAZA

clean:
	rm -f $(TARGET)
	rm -f arbolTRAZA
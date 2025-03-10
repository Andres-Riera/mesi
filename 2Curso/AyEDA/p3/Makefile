CXX = g++						         # The C++ compiler command
CXXFLAGS = -std=c++14 -w -frtti	 # The C++ compiler options (C++14)

TARGET = calculadora # Ejecutable

SRCS = main.cpp # Archivos fuente

all: clean $(TARGET) # Regla por defecto

$(TARGET): $(SRCS) # Regla para compilar el ejecutable
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
CXX ?= g++ 
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS ?= -Iinclude
DOMAIN := src/Item.cpp src/Personagem.cpp src/Pocao.cpp src/Equipamento.cpp src/ResumoItem.cpp src/Inventario.cpp
SOURCES := $(DOMAIN) src/Interface.cpp
HEADERS := $(wildcard include/*.hpp)

.PHONY: all test sanitize clean
all: sistema
sistema: $(SOURCES) src/main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SOURCES) src/main.cpp -o $@
build:
	mkdir -p build
build/teste-%: tests/%.cpp $(SOURCES) $(HEADERS) | build
	$(CXX) $(CXXFLAGS) -UNDEBUG $(CPPFLAGS) $(SOURCES) $< -o $@
test: sistema build/teste-dominio build/teste-inventario build/teste-interface
	./build/teste-dominio
	./build/teste-inventario
	./build/teste-interface
	sh tests/cenarios.sh
sanitize:
	$(MAKE) clean
	$(MAKE) test CXXFLAGS='-std=c++11 -Wall -Wextra -pedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer -fno-pie -no-pie'
clean:
	rm -f sistema sistema.exe
	rm -rf build

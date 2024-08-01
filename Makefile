# Nome do executável
TARGET = mo-wind-farm-layout

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++11

# Diretórios
SRC_DIR = modules
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = modules/headers

# Arquivos fonte e objetos
SOURCES = $(wildcard $(SRC_DIR)/*/*.cpp) $(wildcard $(SRC_DIR)/*/*/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Regras
all: create_dirs $(BIN_DIR)/$(TARGET)

# Regra para criar diretórios
create_dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Regra para compilar o executável
$(BIN_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ $^

# Regra para compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $@ -c $<

# Regra para limpar os arquivos compilados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

# Nome do compilador
CXX = g++

# Flags de compilação (adicionar flags de otimização, warnings, etc., se necessário)
CXXFLAGS = -std=c++11

# Nome do executável
TARGET = moead

# Diretórios com os arquivos fonte
MOEAD_DIR = metaheuristics/moead
POPULATION_DIR = modules/generate_initial_population/generate_population
RANDOM_SOLUTION_DIR = modules/generate_initial_population/generate_random_solution
GENETIC_OPERATORS_DIR = modules/genetic_operators
MODULES_DIR = modules/moead

# Arquivos fonte
SRCS = $(MOEAD_DIR)/moead.cpp \
       $(POPULATION_DIR)/population.cpp \
       $(RANDOM_SOLUTION_DIR)/generate_rSolution.cpp \
       $(MODULES_DIR)/generate_weight_vectors.cpp \
       $(MODULES_DIR)/generate_neighborhood.cpp \
       $(MODULES_DIR)/get_best_z_point.cpp \
       $(MODULES_DIR)/tchebycheff.cpp \
       $(GENETIC_OPERATORS_DIR)/mutation/mutation.cpp \
       $(GENETIC_OPERATORS_DIR)/crossover/crossover.cpp

# Regra para criar o executável
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Regra de limpeza (para remover arquivos gerados, como o executável)
clean:
	rm -f $(TARGET)

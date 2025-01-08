# Variáveis de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Werror -I./headers -I./headers/utils -I./headers/metaheuristics -I./headers/metaheuristics/moead -I./headers/metaheuristics/moead/modules -I./headers/global_modules -I./headers/global_modules/genetic_operators -I./headers/global_modules/generate_initial_population -I./headers/adaptative_grid  -I./headers/metaheuristics/pareto_based -I./headers/metaheuristics/walks

# Diretórios
SRC_DIR = src
HEADER_DIR = headers
META_DIR = src/global_modules/genetic_operators/mutation
CROSS_DIR = src/global_modules/genetic_operators/crossover
RSOLUTION_DIR = src/global_modules/generate_initial_population/generate_random_solution/
POPULATION_DIR = src/global_modules/generate_initial_population/generate_population/

# Arquivos de origem
SRC_FILES = \
    $(SRC_DIR)/adaptive_grid/ParetoSet.cpp \
    $(SRC_DIR)/adaptive_grid/BoundedParetoSet.cpp \
    $(SRC_DIR)/adaptive_grid/Grid.cpp \
    $(SRC_DIR)/global_modules/dominates.cpp \
    $(SRC_DIR)/global_modules/isEqual.cpp \
    $(POPULATION_DIR)/population.cpp \
    $(RSOLUTION_DIR)/generate_rSolution.cpp \
    $(META_DIR)/mutation.cpp \
    $(CROSS_DIR)/crossover.cpp \
    $(SRC_DIR)/metaheuristics/moead/modules/generate_neighborhood.cpp \
    $(SRC_DIR)/metaheuristics/moead/modules/generate_weight_vectors.cpp \
    $(SRC_DIR)/metaheuristics/moead/modules/get_best_z_point.cpp \
    $(SRC_DIR)/metaheuristics/moead/modules/tchebycheff.cpp \
    $(SRC_DIR)/metaheuristics/moead/modules/updateEP.cpp \
    $(SRC_DIR)/metaheuristics/moead/moead.cpp \
    instance_info.cpp

# Arquivo principal
MAIN_FILE = main.cpp

# Arquivo de saída
OUTPUT = moead

# Regra para compilar
$(OUTPUT): $(SRC_FILES) $(MAIN_FILE)
	@echo Starting compilation of adaptative_walk_decomposition...
	@$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(MAIN_FILE) $(SRC_FILES)
	@echo Compilation completed.

# Limpeza dos arquivos gerados
clean:
	@echo "Cleaning generated files..."
	@rm -f $(OUTPUT)
	@echo "Clean completed."

# Recompilar tudo
rebuild: clean $(OUTPUT)
	@echo "Rebuild completed."

@echo off

mkdir dataset
mkdir dataset\decomposition_based
mkdir dataset\decomposition_based\random_walk
mkdir dataset\decomposition_based\adaptative_walk
mkdir dataset\pareto_based
mkdir dataset\pareto_based\random_walk
mkdir dataset\pareto_based\adaptative_walk

set r=0.05 0.1 0.25 0.5 1.0
set l=5 10 25 50 100

for %%L in (%l%) do (
    mkdir dataset\decomposition_based\adaptative_walk\l%%L
)

for %%L in (%l%) do (
    for %%R in (%r%) do (
        mkdir dataset\decomposition_based\random_walk\l%%L_r%%R
    )
)

for %%L in (%l%) do (
    mkdir dataset\pareto_based\adaptative_walk\l%%L
)

for %%L in (%l%) do (
    for %%R in (%r%) do (
        mkdir dataset\pareto_based\random_walk\l%%L_r%%R
    )
)

echo Estrutura de diretórios criada com sucesso!

for %%L in (%l%) do (
    for %%R in (%r%) do (
        echo Run a.exe with: A %%L %%R
        a.exe A %%L %%R
    )
)

pause

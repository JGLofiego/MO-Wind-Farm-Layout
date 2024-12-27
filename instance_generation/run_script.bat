@echo off
:: Verifica se foi passado o número de vezes como argumento
if "%1"=="" (
    echo Por favor, forneça o número de vezes como argumento.
    exit /b 1
)

:: Captura o número de vezes do argumento
set num_vezes=%1

:: Loop para rodar o script Python
for /l %%i in (11,1,%num_vezes%) do (
    echo Rodando o script Python pela vez %%i...
    python script.py %%i
)

echo Finalizado!

# CMakeList.txt: проект CMake для lab4_sem3(graphs_algos); включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("lab4_sem3(graphs_algos)")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeTarget 
"src/lab4_sem3(graphs_algos).cpp"
"src/lab4_sem3(graphs_algos).h"
"src/Graph.h" 
"src/PairHash.h"
"src/DictionaryStructs/Dictionary"
"src/DictionaryStructs/IDictionary"
"src/DictionaryStructs/HashTable"

)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

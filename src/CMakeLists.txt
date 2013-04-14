#############################################################################
# PokePets Source
#############################################################################
project(PokePets_src)
cmake_minimum_required(VERSION 2.8)

# list of source that makes up PokePets!
set(PP_OBJECTS
    CSVReader
    DBParser
    Move
    Nature
    Pokemon
    PokemonSpecies
    Type)

# make each PP_OBJECTS an object library and clone the list as target objects
foreach(obj ${PP_OBJECTS})
    add_library(${obj} OBJECT ${obj}.cpp)
    set(PP_TARGET_OBJ ${PP_TARGET_OBJ} $<TARGET_OBJECTS:${obj}>)
endforeach(obj)

set(PP_SOURCES PokePets)

# Main Project Executable
add_executable(PokePets ${PP_SOURCES} ${PP_TARGET_OBJ})
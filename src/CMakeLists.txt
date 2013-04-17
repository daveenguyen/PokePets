#############################################################################
# PokePets Source
#############################################################################
project(PokePets_src)

# list of source that makes up PokePets!
set(PP_OBJECTS
    CSVReader
    DBParser
    Move
    Nature
    Pokemon
    PokemonSpecies
    PokemonBuilder
    Type)

# make each PP_OBJECTS a library
foreach(obj ${PP_OBJECTS})
    add_library(${obj} ${obj}.cpp)
endforeach(obj)

# Create the main executable and link all the objects
set(PP_SOURCES PokePets)
add_executable(PokePets ${PP_SOURCES})
target_link_libraries(PokePets ${PP_OBJECTS})
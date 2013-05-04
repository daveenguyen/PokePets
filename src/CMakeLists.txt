#############################################################################
# PokePets Source
#############################################################################
project(PokePets_src)

# list of source that makes up PokePets!
set(PP_OBJECTS
    Bulbasaur
    Charmander
    CSVReader
    Move
    Nature
    Pokemon
    PokemonSpecies
    PokemonBattle
    PokemonBuilder
    Squirtle
    Type)

# make each PP_OBJECTS a library
##foreach(obj ${PP_OBJECTS})
##    add_library(${obj} ${obj}.cpp)
##endforeach(obj)

# Create the main executable and link all the objects
set(PP_SOURCES PokePets)
add_executable(PokePets ${PP_SOURCES} ${PP_OBJECTS})
#target_link_libraries(PokePets ${PP_OBJECTS})
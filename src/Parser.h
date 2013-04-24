#ifndef PARSER_H
#define PARSER_H

    // Language of Names
    //  1: Japanese
    //  2: Official Roomaji
    //  3: Korean
    //  4: Chinese
    //  5: French
    //  6: German
    //  7: Spanish
    //  8: Italian
    //  9: English
    // 10: Czech
    #define LANGUAGE_ID 9

    // Pokemon Version Group
    //  1: Red, Blue
    //  2: Yellow
    //  3: Gold, Silver
    //  4: Crystal
    //  5: Ruby, Sapphire
    //  6: Emerald
    //  7: Fire Red, Leaf Green
    //  8: Diamond, Pearl
    //  9: Platinum
    // 10: Heart Gold, Soul Silver
    // 11: Black, White
    // 12: Colosseum
    // 13: XD
    // 14: Black 2, White 2
    #define VERSION_GROUP_ID 14

    // PokemonSpecies class
    #define POKEMON_CSV                 "../data/csv/pokemon.csv"
    #define EXPERIENCE_CSV              "../data/csv/experience.csv"
    #define POKEMON_MOVES_CSV           "../data/csv/pokemon_moves.csv"
    #define POKEMON_STATS_CSV           "../data/csv/pokemon_stats.csv"
    #define POKEMON_TYPES_CSV           "../data/csv/pokemon_types.csv"
    #define POKEMON_SPECIES_CSV         "../data/csv/pokemon_species.csv"
    #define POKEMON_ABILITIES_CSV       "../data/csv/pokemon_abilities.csv"
    #define POKEMON_SPECIES_NAMES_CSV   "../data/csv/pokemon_species_names.csv"

    // Type class
    #define TYPE_NAMES_CSV              "../data/csv/type_names.csv"
    #define TYPE_EFFICACY_CSV           "../data/csv/type_efficacy.csv"

    // Nature class
    #define NATURES_CSV                 "../data/csv/natures.csv"
    #define NATURE_NAMES_CSV            "../data/csv/nature_names.csv"

    // Move class
    #define MOVES_CSV                   "../data/csv/moves.csv"
    #define MOVE_META_CSV               "../data/csv/move_meta.csv"
    #define MOVE_NAMES_CSV              "../data/csv/move_names.csv"
    #define MOVE_META_STAT_CHANGES_CSV  "../data/csv/move_meta_stat_changes.csv"

#endif // PARSER_H
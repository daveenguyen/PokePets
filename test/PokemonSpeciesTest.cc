#include <gtest/gtest.h>
#include <cstdlib>

#include "../src/PokemonSpecies.h"
#include "../src/PokemonBuilder.h"
#include "../src/CSVReader.h"
#include "../src/Type.h"

namespace {

     TEST(PokeSpeciesConstructor, Default)
    {
        CSVReader reader;
        PokemonSpecies species(0);

        EXPECT_EQ(0, species.getDexNum() );
        EXPECT_TRUE( species.getName().empty() );
        EXPECT_EQ(0, species.getType(0).getTypeNum() );
        EXPECT_EQ(0, species.getType(1).getTypeNum() );

        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(0, species.getSpeciesAbility(i) );

        EXPECT_EQ(0, species.getGenderRate() );

        for (int i = 0; i < 6; ++i)
            EXPECT_EQ(0, species.getBaseStats(i) );

        EXPECT_EQ(0, species.getBaseExp() );

        for (int i = 0; i < 6; ++i)
            EXPECT_EQ(0, species.getEffortYield(i) );

        EXPECT_EQ(0, species.getCapRate() );
        EXPECT_EQ(0, species.getBaseHappiness() );
        EXPECT_EQ(0, species.getGrowthRate() );

        for (int i = 0; i < 100; ++i)
            EXPECT_EQ(0, species.getExpToLvl(i) );

        // tutor moves
        EXPECT_EQ(0, species.getLevelUpMoves().size() );
        EXPECT_EQ(0, species.getEggMoves().size() );
        EXPECT_EQ(0, species.getTutorMoves().size() );
        EXPECT_EQ(0, species.getMachineMoves().size() );
    }

     TEST(PokeSpeciesConstructor, UserDefined)
    {
        CSVReader reader;
        PokemonSpecies species(6);
        PokemonBuilder builder;
        // builder.setReader(&reader);
        // builder.setPokemon((Pokemon*)(&species));
        // builder.initSpecies();

        // get
        // EXPECT_EQ(6,  species.getDexNum() );
        // EXPECT_STREQ("Charizard", species.getName().c_str() );
        // EXPECT_EQ(10, species.getType(0).getTypeNum() );
        // EXPECT_EQ(3,  species.getType(1).getTypeNum() );

        // EXPECT_EQ(66, species.getSpeciesAbility(0) );
        // EXPECT_EQ(0, species.getSpeciesAbility(1) );
        // EXPECT_EQ(94, species.getSpeciesAbility(2) );

        // EXPECT_EQ(1, species.getGenderRate() );

        // EXPECT_EQ(78, species.getBaseStats(0) );
        // EXPECT_EQ(84, species.getBaseStats(1) );
        // EXPECT_EQ(78, species.getBaseStats(2) );
        // EXPECT_EQ(109, species.getBaseStats(3) );
        // EXPECT_EQ(85, species.getBaseStats(4) );
        // EXPECT_EQ(100, species.getBaseStats(5) );

        // EXPECT_EQ(240, species.getBaseExp() );

        // EXPECT_EQ(0, species.getEffortYield(0) );
        // EXPECT_EQ(0, species.getEffortYield(1) );
        // EXPECT_EQ(0, species.getEffortYield(2) );
        // EXPECT_EQ(3, species.getEffortYield(3) );
        // EXPECT_EQ(0, species.getEffortYield(4) );
        // EXPECT_EQ(0, species.getEffortYield(5) );

        // EXPECT_EQ(45, species.getCapRate() );
        // EXPECT_EQ(70, species.getBaseHappiness() );
        // EXPECT_EQ(4, species.getGrowthRate() );

        // for (int i = 0; i < 100; ++i)
            // EXPECT_EQ(0, species.getExpToLvl(i) );

        // // set

        species.setDexNum(6);
        // species.setName("test name");
        // species.setTypes(9, 0);
        // species.setTypes(9, 1);

        // for (int i = 0; i < 3; ++i)
        //     species.setAbilities(9, i);

        // species.setGenderRate(9);

        // for (int i = 0; i < 6; ++i)
        //     species.setBaseStats(9, i);

        // species.setBaseExp(9);

        // for (int i = 0; i < 6; ++i)
        //     species.setEffortYield(9, i);

        // species.setCapRate(9);
        // species.setBaseHappiness(9);
        // species.setGrowthRate(9);

        // for (int i = 0; i < 100; ++i)
        //     species.setExpToLvl(9, i);


        // // get
        EXPECT_EQ(6, species.getDexNum() );
        // EXPECT_FALSE( species.getName().empty() );
        // EXPECT_STREQ("test name", species.getName().c_str());
        // EXPECT_EQ(9, species.getType(0).getTypeNum() );
        // EXPECT_EQ(9, species.getType(1).getTypeNum() );

        // for (int i = 0; i < 3; ++i)
        //     EXPECT_EQ(9, species.getSpeciesAbility(i) );

        // EXPECT_EQ(9, species.getGenderRate() );

        // for (int i = 0; i < 6; ++i)
        //     EXPECT_EQ(9, species.getBaseStats(i) );

        // EXPECT_EQ(9, species.getBaseExp() );

        // for (int i = 0; i < 6; ++i)
        //     EXPECT_EQ(9, species.getEffortYield(i) );

        // EXPECT_EQ(9, species.getCapRate() );
        // EXPECT_EQ(9, species.getBaseHappiness() );
        // EXPECT_EQ(9, species.getGrowthRate() );

        // for (int i = 0; i < 100; ++i)
        //     EXPECT_EQ(9, species.getExpToLvl(i) );

    }


     TEST(PokeSpeciesConstructor, SettersGetters)
    {
        CSVReader reader;
        PokemonSpecies species(0);

        EXPECT_EQ(0, species.getDexNum() );
        EXPECT_TRUE( species.getName().empty() );
        EXPECT_EQ(0, species.getType(0).getTypeNum() );
        EXPECT_EQ(0, species.getType(1).getTypeNum() );

        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(0, species.getSpeciesAbility(i) );

        EXPECT_EQ(0, species.getGenderRate() );

        for (int i = 0; i < 6; ++i)
            EXPECT_EQ(0, species.getBaseStats(i) );

        EXPECT_EQ(0, species.getBaseExp() );

        for (int i = 0; i < 6; ++i)
            EXPECT_EQ(0, species.getEffortYield(i) );

        EXPECT_EQ(0, species.getCapRate() );
        EXPECT_EQ(0, species.getBaseHappiness() );
        EXPECT_EQ(0, species.getGrowthRate() );

        for (int i = 0; i < 100; ++i)
            EXPECT_EQ(0, species.getExpToLvl(i) );

        // tutor moves
        EXPECT_EQ(0, species.getLevelUpMoves().size() );
        EXPECT_EQ(0, species.getEggMoves().size() );
        EXPECT_EQ(0, species.getTutorMoves().size() );
        EXPECT_EQ(0, species.getMachineMoves().size() );

        species.setDexNum(6);

        // PokemonBuilder builder;
        // builder.setReader(&reader);
        // builder.setPokemon((Pokemon*)(&species));
        // builder.initSpecies();

        species.setDexNum(6);
        species.setName("Charizard");
        species.setType(0,10);
        species.setType(1,3);

        species.setSpeciesAbility(0,66);
        species.setSpeciesAbility(1,0);
        species.setSpeciesAbility(2,94);

        species.setGenderRate(1);

        species.setBaseStat(0,78);
        species.setBaseStat(1,84);
        species.setBaseStat(2,78);
        species.setBaseStat(3,109);
        species.setBaseStat(4,85);
        species.setBaseStat(5,100);

        species.setBaseExp(240);

        species.setEffortYield(0,0);
        species.setEffortYield(1,0);
        species.setEffortYield(2,0);
        species.setEffortYield(3,3);
        species.setEffortYield(4,0);
        species.setEffortYield(5,0);

        species.setCapRate(45);
        species.setBaseHappiness(70);
        species.setGrowthRate(4);


        EXPECT_EQ(6,  species.getDexNum() );
        EXPECT_STREQ("Charizard", species.getName().c_str() );
        EXPECT_EQ(10, species.getType(0).getTypeNum() );
        EXPECT_EQ(3,  species.getType(1).getTypeNum() );

        EXPECT_EQ(66, species.getSpeciesAbility(0) );
        EXPECT_EQ(0, species.getSpeciesAbility(1) );
        EXPECT_EQ(94, species.getSpeciesAbility(2) );

        EXPECT_EQ(1, species.getGenderRate() );

        EXPECT_EQ(78, species.getBaseStats(0) );
        EXPECT_EQ(84, species.getBaseStats(1) );
        EXPECT_EQ(78, species.getBaseStats(2) );
        EXPECT_EQ(109, species.getBaseStats(3) );
        EXPECT_EQ(85, species.getBaseStats(4) );
        EXPECT_EQ(100, species.getBaseStats(5) );

        EXPECT_EQ(240, species.getBaseExp() );

        EXPECT_EQ(0, species.getEffortYield(0) );
        EXPECT_EQ(0, species.getEffortYield(1) );
        EXPECT_EQ(0, species.getEffortYield(2) );
        EXPECT_EQ(3, species.getEffortYield(3) );
        EXPECT_EQ(0, species.getEffortYield(4) );
        EXPECT_EQ(0, species.getEffortYield(5) );

        EXPECT_EQ(45, species.getCapRate() );
        EXPECT_EQ(70, species.getBaseHappiness() );
        EXPECT_EQ(4, species.getGrowthRate() );
    }

     TEST(PokeSpeciesConstructor, Vectors)
    {
        CSVReader reader;
        PokemonSpecies species(0);

        // tutor moves
        EXPECT_EQ(0, species.getLevelUpMoves().size() );
        EXPECT_EQ(0, species.getEggMoves().size() );
        EXPECT_EQ(0, species.getTutorMoves().size() );
        EXPECT_EQ(0, species.getMachineMoves().size() );

        // species.addLevelUpMoves(2, 3, 4);
        // species.addEggMoves(5);
        // species.addTutorMoves(6);
        // species.addMachineMoves(7);

        // EXPECT_EQ(1, species.getLevelUpMoves().size() );
        // EXPECT_EQ(1, species.getEggMoves().size() );
        // EXPECT_EQ(1, species.getTutorMoves().size() );
        // EXPECT_EQ(1, species.getMachineMoves().size() );
    }

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
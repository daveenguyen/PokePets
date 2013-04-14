#include <gtest/gtest.h>
#include <cstdlib>

#include "../src/PokemonSpecies.h"
#include "../src/CSVReader.h"

namespace {

     TEST(PokeSpeciesConstructor, Default)
    {
        CSVReader reader;
        PokemonSpecies species(&reader);

        EXPECT_EQ(0, species.getDexNum() );
        EXPECT_TRUE( species.getName().empty() );
        EXPECT_EQ(0, species.getTypes(0) );
        EXPECT_EQ(0, species.getTypes(1) );

        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(0, species.getAbilities(i) );

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
        PokemonSpecies species(&reader,6);

        // get
        EXPECT_EQ(6,  species.getDexNum() );
        EXPECT_STREQ("Charizard", species.getName().c_str() );
        EXPECT_EQ(10, species.getTypes(0) );
        EXPECT_EQ(3,  species.getTypes(1) );

        EXPECT_EQ(66, species.getAbilities(0) );
        EXPECT_EQ(0, species.getAbilities(1) );
        EXPECT_EQ(94, species.getAbilities(2) );

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
        // EXPECT_EQ(9, species.getTypes(0) );
        // EXPECT_EQ(9, species.getTypes(1) );

        // for (int i = 0; i < 3; ++i)
        //     EXPECT_EQ(9, species.getAbilities(i) );

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
        PokemonSpecies species(&reader);

        EXPECT_EQ(0, species.getDexNum() );
        EXPECT_TRUE( species.getName().empty() );
        EXPECT_EQ(0, species.getTypes(0) );
        EXPECT_EQ(0, species.getTypes(1) );

        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(0, species.getAbilities(i) );

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
        species.initFromParser();

        EXPECT_EQ(6,  species.getDexNum() );
        EXPECT_STREQ("Charizard", species.getName().c_str() );
        EXPECT_EQ(10, species.getTypes(0) );
        EXPECT_EQ(3,  species.getTypes(1) );

        EXPECT_EQ(66, species.getAbilities(0) );
        EXPECT_EQ(0, species.getAbilities(1) );
        EXPECT_EQ(94, species.getAbilities(2) );

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
        PokemonSpecies species(&reader);

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
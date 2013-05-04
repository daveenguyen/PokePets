#include <gtest/gtest.h>
#include <cstdlib>
#include "../src/CSVReader.h"

#define IDEAL_CSV   "../test/csv/ideal.csv"
#define SKIP_CSV    "../test/csv/skip.csv"
#define BAD_CSV     "../test/csv/bad.csv"

namespace {

     TEST(CSVReaderConstructorTests, DefaultConstructor)
    {
        CSVReader reader;

        EXPECT_EQ(0, reader.getFieldSize());
        EXPECT_EQ(-1, reader.getFieldIndex());
        EXPECT_TRUE(reader.getLine().empty());
        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_FALSE(reader.isOpen());
    }

     TEST(CSVReaderConstructorTests, UserDefConstructor)
    {
        CSVReader reader(IDEAL_CSV);

        EXPECT_NE(0, reader.getFieldSize());
        EXPECT_EQ(-1, reader.getFieldIndex());
        EXPECT_FALSE(reader.getLine().empty());
        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_TRUE(reader.isOpen());
    }

    TEST(CSVReaderFunctionTests, openFile)
    {
        CSVReader reader;
        EXPECT_FALSE(reader.isOpen());
        EXPECT_FALSE(reader.isOpen());

        reader.openFile(IDEAL_CSV);
        EXPECT_TRUE(reader.isOpen());
        reader.openFile(SKIP_CSV);
        EXPECT_TRUE(reader.isOpen());

        EXPECT_EXIT(reader.openFile(BAD_CSV), ::testing::ExitedWithCode(1), "Could not open ");
    }

     TEST(CSVReaderFunctionTests, reset)
    {
        CSVReader reader;

        EXPECT_EQ(0, reader.getFieldSize());
        EXPECT_EQ(-1, reader.getFieldIndex());
        EXPECT_TRUE(reader.getLine().empty());
        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_FALSE(reader.isOpen());

        reader.openFile(IDEAL_CSV);

        EXPECT_NE(0, reader.getFieldSize());
        EXPECT_EQ(-1, reader.getFieldIndex());
        EXPECT_FALSE(reader.getLine().empty());
        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_TRUE(reader.isOpen());
        reader.readField();
        EXPECT_NE(-1, reader.getFieldIndex());
        EXPECT_FALSE(reader.getCurField().empty());

        reader.reset();
        EXPECT_EQ(0, reader.getFieldSize());
        EXPECT_EQ(-1, reader.getFieldIndex());
        EXPECT_TRUE(reader.getLine().empty());
        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_FALSE(reader.isOpen());
    }

     TEST(CSVReaderTests, readLine)
    {
        CSVReader reader;

        EXPECT_TRUE(reader.getCurField().empty());
        reader.openFile(IDEAL_CSV);

        reader.readLine();
        EXPECT_STREQ("28,7,-1,ing",reader.getLine().c_str());

        reader.readLine();
        EXPECT_STREQ("14,2,2,str",reader.getLine().c_str());
    }

     TEST(CSVReaderTests, readField)
    {
        CSVReader reader;

        EXPECT_TRUE(reader.getCurField().empty());
        EXPECT_EQ(0,reader.getField<int>());
        reader.openFile(IDEAL_CSV);
        EXPECT_TRUE(reader.getCurField().empty());

        reader.readField();
        EXPECT_STREQ("move_id",reader.getCurField().c_str());

        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        reader.readField();
        reader.readField();
        EXPECT_STREQ("-1",reader.getCurField().c_str());
        EXPECT_EQ(2,reader.getFieldIndex());
    }

     TEST(CSVReaderGetterTests, getLine)
    {
        CSVReader reader;

        EXPECT_TRUE(reader.getLine().empty());
        reader.openFile(IDEAL_CSV);
        EXPECT_STREQ("move_id,stat_id,change,string",reader.getLine().c_str());

        reader.readLine();
        EXPECT_STREQ("28,7,-1,ing",reader.getLine().c_str());

        reader.readLine();
        EXPECT_STREQ("14,2,2,str",reader.getLine().c_str());
    }

     TEST(CSVReaderGetterTests, getFieldIdeal)
    {
        CSVReader reader;

        EXPECT_TRUE(reader.getCurField().empty());
        reader.openFile(IDEAL_CSV);
        EXPECT_TRUE(reader.getCurField().empty());

        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());

        reader.readField();
        EXPECT_STREQ("28",reader.getCurField().c_str());

        reader.readField();
        EXPECT_STREQ("7",reader.getCurField().c_str());

        reader.readField();
        EXPECT_STREQ("-1",reader.getCurField().c_str());

        reader.readField();
        EXPECT_STREQ("ing",reader.getCurField().c_str());
    }

     TEST(CSVReaderGetterTests, getFieldSkip)
    {
        CSVReader reader;

        EXPECT_TRUE(reader.getCurField().empty());
        reader.openFile(SKIP_CSV);
        EXPECT_TRUE(reader.getCurField().empty());

        // line 2
        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_STREQ("1",reader.getCurField().c_str());
        reader.readField();
        EXPECT_STREQ("9.0",reader.getCurField().c_str());
        reader.readField();
        EXPECT_STREQ("Pound it",reader.getCurField().c_str());

        // line 3
        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_STREQ("3.5",reader.getCurField().c_str());
        reader.readField();
        EXPECT_STREQ("6",reader.getCurField().c_str());
        reader.readField();
        EXPECT_TRUE(reader.getCurField().empty());

        // line 4
        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_STREQ("4",reader.getCurField().c_str());
        reader.readField();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_STREQ("Yes",reader.getCurField().c_str());

        // line 5
        reader.readLine();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_TRUE(reader.getCurField().empty());
        reader.readField();
        EXPECT_STREQ("5",reader.getCurField().c_str());
        reader.readField();
        EXPECT_STREQ("No",reader.getCurField().c_str());
    }

     TEST(CSVReaderGetterTests, getFieldSize)
    {
        CSVReader reader;

        EXPECT_EQ(0,reader.getFieldSize());
        reader.openFile(IDEAL_CSV);
        EXPECT_EQ(4,reader.getFieldSize());

        reader.reset();
        EXPECT_EQ(0,reader.getFieldSize());

        reader.openFile(SKIP_CSV);
        EXPECT_EQ(3,reader.getFieldSize());
    }

     TEST(CSVReaderGetterTests, getFieldIndex)
    {
        CSVReader reader;

        EXPECT_EQ(-1,reader.getFieldIndex());
        reader.openFile(IDEAL_CSV);
        EXPECT_EQ(-1,reader.getFieldIndex());

        reader.readLine();
        EXPECT_EQ(-1,reader.getFieldIndex());

        reader.readField();
        EXPECT_EQ(0,reader.getFieldIndex());

        reader.readField();
        EXPECT_EQ(1,reader.getFieldIndex());

        reader.reset();
        EXPECT_EQ(-1,reader.getFieldIndex());
    }

     TEST(CSVReaderBoolTests, isEof)
    {
        CSVReader reader;

        EXPECT_FALSE(reader.isEof());
        reader.openFile(IDEAL_CSV);
        EXPECT_FALSE(reader.isEof());

        // line 2
        reader.readLine();
        EXPECT_FALSE(reader.isEof());

        // line 3
        reader.readLine();
        EXPECT_TRUE(reader.isEof());
    }

     TEST(CSVReaderBoolTests, isEolIdeal)
    {
        CSVReader reader;

        EXPECT_FALSE(reader.isEol());
        reader.openFile(IDEAL_CSV);
        EXPECT_FALSE(reader.isEol());

        reader.readLine();
        EXPECT_FALSE(reader.isEol());

        reader.readField();
        EXPECT_FALSE(reader.isEol());

        reader.readField();
        EXPECT_FALSE(reader.isEol());

        reader.readField();
        EXPECT_FALSE(reader.isEol());

        reader.readField();
        EXPECT_TRUE(reader.isEol());
    }

     TEST(CSVReaderBoolTests, isEolSkip)
    {
        CSVReader reader;

        // default
        EXPECT_FALSE(reader.isEol());
        // open file
        reader.openFile(SKIP_CSV);
        EXPECT_FALSE(reader.isEol());

        // line 1 fields
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_TRUE(reader.isEol());

        // line 2 fields
        reader.readLine();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_TRUE(reader.isEol());

        // line 3 fields
        reader.readLine();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_TRUE(reader.isEol());

        // line 4 fields
        reader.readLine();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_TRUE(reader.isEol());

        // line 5 fields
        reader.readLine();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_FALSE(reader.isEol());
        reader.readField();
        EXPECT_TRUE(reader.isEol());
    }

     TEST(CSVReaderBoolTests, isOpen)
    {
        CSVReader reader;

        EXPECT_FALSE(reader.isOpen());

        reader.openFile(IDEAL_CSV);
        EXPECT_TRUE(reader.isOpen());

        reader.openFile(SKIP_CSV);
        EXPECT_TRUE(reader.isOpen());

        reader.reset();
        EXPECT_FALSE(reader.isOpen());
    }

    TEST(CSVReaderFunctionTests, countFields)
    {
        CSVReader reader;
        EXPECT_EQ(0, reader.getFieldSize());
        reader.openFile(IDEAL_CSV);
        EXPECT_EQ(4, reader.getFieldSize());
        reader.openFile(SKIP_CSV);
        EXPECT_EQ(3, reader.getFieldSize());
    }

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
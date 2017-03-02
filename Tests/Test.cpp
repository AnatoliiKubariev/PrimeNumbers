#include "gtest/gtest.h"

#include "XMLHanler.h"
#include "PrimeNumbersCalculator.h"

#include <fstream>

::testing::AssertionResult VECTOR_EQ(const std::vector<int>& lhs,
                                     const std::vector<int>& rhs)
{
    if(lhs.size() != rhs.size())
    {
        return ::testing::AssertionFailure();
    }

    for(auto i = 0; i < lhs.size(); ++i)
    {
        if(lhs[0] != rhs[0])
        {
            return ::testing::AssertionFailure();
        }
    }
    return ::testing::AssertionSuccess();
}

::testing::AssertionResult INTERVAL_EQ(const Interval& lhs,
                                       const Interval& rhs)
{
    if(lhs.high != rhs.high || lhs.high != rhs.high)
    {
        return ::testing::AssertionFailure();
    }
    return ::testing::AssertionSuccess();
}

TEST(PrimeNumbersCalculatorTest, CanCalculate)
{
    std::ifstream stream("test.txt");
    PrimeNumbersCalculator calc;
    const Interval interval = GetItervals(stream)[0];
    EXPECT_TRUE(VECTOR_EQ({{2, 3, 5, 7}}, calc.GetPrimals(interval)));
}

TEST(ParserTest, CanParse)
{
    std::ifstream stream("test.txt");

    EXPECT_TRUE(INTERVAL_EQ(GetItervals(stream)[0], {1, 10}));
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
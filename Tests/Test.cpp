#include "gtest/gtest.h"

#include "XMLHandler.h"
#include "PrimeNumbersCalculator.h"

#include <fstream>
#include <filesystem> 

class PrimeNumbersCalculatorTest: public ::testing::Test
{
public:
    PrimeNumbersCalculatorTest()
    {
        test_primes = {2, 3, 5, 7,
            101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
            157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

        result_test = "<root>\n"
            "<intervals>\n"
            "<interval>\n"
            "<low> 1</low>\n"
            "<high> 10 </high>\n"
            "</interval>\n"
            "<interval>\n"
            "<low> 100 </low>\n"
            "<high> 200 </high>\n"
            "</interval>\n"
            "</intervals>\n"
            "<primes> "
            "2 3 5 7 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 "
            "</primes>\n"
            "</root>";
    }

    void SetUp() override
    {
        std::string test = "<root>\n"
            "<intervals>\n"
            "<interval>\n"
            "<low> 1</low>\n"
            "<high> 10 </high>\n"
            "</interval>\n"
            "<interval>\n"
            "<low> 100 </low>\n"
            "<high> 200 </high>\n"
            "</interval>\n"
            "</intervals>\n"
            "</root>";
        std::ofstream test_file(test_file_name);
        test_file << test;
    }

    void TearDown() override
    {
        std::experimental::filesystem::v1::remove(test_file_name);
    }

    ~PrimeNumbersCalculatorTest()
    {
    }

    std::vector<int> test_primes;
    std::string result_test;
    std::string test_file_name = "test.txt";
};

::testing::AssertionResult INTERVAL_EQ(const Interval& lhs,
                                       const Interval& rhs)
{
    if(lhs.high != rhs.high || lhs.high != rhs.high)
    {
        return ::testing::AssertionFailure();
    }
    return ::testing::AssertionSuccess();
}

TEST_F(PrimeNumbersCalculatorTest, CanCalculate)
{
    std::ifstream stream(test_file_name);
    PrimeNumbersCalculator calc;
    std::vector<int> primes;
    for(auto& interval : GetIntervals(stream))
    {
        for(auto prime : calc.GetPrimes(interval))
        {
            primes.push_back(prime);
        }
    }
    EXPECT_EQ(test_primes, primes);
}

TEST_F(PrimeNumbersCalculatorTest, CanParse)
{
    std::ifstream stream(test_file_name);
    EXPECT_TRUE(INTERVAL_EQ(GetIntervals(stream)[0], {1, 10}));
    EXPECT_TRUE(INTERVAL_EQ(GetIntervals(stream)[1], {100, 200}));
}

TEST_F(PrimeNumbersCalculatorTest, ResultTest)
{
    std::ifstream stream(test_file_name);
    PrimeNumbersCalculator calc;
    std::vector<int> primes;
    for(auto& interval : GetIntervals(stream))
    {
        for(auto prime : calc.GetPrimes(interval))
        {
            primes.push_back(prime);
        }
    }
    std::fstream result_test_file(test_file_name);
    WritePrimes(result_test_file, primes);
    std::string str((std::istreambuf_iterator<char>(result_test_file)),
                    std::istreambuf_iterator<char>());
    EXPECT_EQ(str, result_test);
}

TEST(NotValidXML, ThrowExeption)
{
    std::string not_valid = "<root>\n"
        "<intervals>\n"
        "<interval>\n"
        "<low> 1</low>\n"
        "<high> 10\n"
        "</interval>\n"
        "<interval>\n"
        "</interval>\n"
        "</intervals>\n"
        "</root>";
    {
        std::ofstream ofs("not_valid.txt");
        ofs << not_valid;
    }
    std::ifstream stream("not_valid.txt");
    EXPECT_THROW(GetIntervals(stream), std::exception);
    stream.close();
    std::experimental::filesystem::v1::remove("not_valid.txt");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include "XMLHandler.h"

#include <exception>
#include <stack>
#include <string>

namespace
{
std::string GetTag(std::istream& stream);
int GetData(std::istream& stream);
}

std::vector<Interval> GetIntervals(const std::string& file_name)
{
    std::ifstream ifs(file_name);
    return GetIntervals(ifs);
}

std::vector<Interval> GetIntervals(std::istream& stream)
{
    stream.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    std::vector<Interval> intervals;
    std::stack<std::string> tags;
    while(stream)
    {
        std::string tag = GetTag(stream);

        if(tag == "root" ||
           tag == "intervals")
        {
            tags.push(tag);
        }
        else if(tag == "interval")
        {
            tags.push(tag);
            intervals.push_back({-1, -1});
        }
        else if(tag == "low")
        {
            tags.push(tag);
            intervals.back().low = GetData(stream);
        }
        else if(tag == "high")
        {
            tags.push(tag);
            intervals.back().high = GetData(stream);
        }
        else if(tag == "/interval" ||
                tag == "/low" ||
                tag == "/high" ||
                tag == "/intervals")
        {
            tag.erase(0, 1);
            if(tag != tags.top())
            {
                throw std::logic_error("not valid xml");
            }
            tags.pop();
        }
        else if(tag == "/root")
        {
            tag.erase(0, 1);
            if(tag != tags.top())
            {
                throw std::logic_error("not valid xml");
            }
            break;
        }
    }
    stream.seekg(0);
    return intervals;
}

void WritePrimes(const std::string& file_name, const std::vector<int>& primes)
{
    std::fstream fs(file_name);
    WritePrimes(fs, primes);
}

void WritePrimes(std::fstream& stream, const std::vector<int>& primes)
{
    stream.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    std::string tag;
    while(stream)
    {
        tag = GetTag(stream);
        if(tag == "/intervals")
        {
            stream.seekp(stream.tellg());
            stream << std::endl << "<primes> ";

            for(auto prime : primes)
            {
                stream << prime;
                stream << " ";
            }

            stream << "</primes>" << std::endl << "</root>";
            break;
        }
    }
    stream.seekp(0);
}

namespace
{
std::string GetTag(std::istream& stream)
{
    char ch;
    stream >> ch;
    while(ch != '<')
    {
        stream >> ch;
    }

    stream >> ch;
    std::string res;
    while(ch != '>')
    {
        res += ch;
        stream >> ch;
    }

    return res;
}

int GetData(std::istream& stream)
{
    char curr;
    stream >> curr;
    std::string res;
    while(curr != '<')
    {
        res += curr;
        stream >> curr;
    }
    int pos = stream.tellg();
    --pos;
    stream.seekg(pos);

    return std::stoi(res);
}
}
#include "XMLHanler.h"

#include <string>

std::string GetTag(std::istream& stream);
int GetData(std::istream& stream);

std::vector<Interval> GetItervals(std::istream& stream)
{
    std::vector<Interval> intervals;
    std::string tag;
    while(stream)
    {
        tag = GetTag(stream);
        if(tag == "interval")
        {
            intervals.push_back({-1, -1});
        }
        else if(tag == "low")
        {
            intervals.back().low = GetData(stream);
        }
        else if(tag == "high")
        {
            intervals.back().high = GetData(stream);
        }
        else if(tag == "/intervals")
        {
            break;
        }
    }
    stream.seekg(std::ios::beg);
    return intervals;
}

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
    return "";
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
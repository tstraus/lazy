#include "lazy.h"
#include "lest.hpp"

#include <iostream>
#include <chrono>

using namespace std;
using namespace tstraus;

const lest::test t[] =
{
    CASE("String" "[tstraus::Lazy]")
    {
        Lazy<string> s([]() {
            //cout << "evaluating" << endl;

            return "I'm Lazy";
        });

        EXPECT(s.evaluated() == false);

        const auto first = s.get();
        const auto second = s.get();

        EXPECT(s.evaluated() == true);
        EXPECT(first == second);
    },
    CASE("StringCaptured" "[tstraus::Lazy]")
    {
        const string c = "I'm Lazy and Capturing";
        Lazy<string> s([c]() {
            //cout << "evaluating" << endl;

            return c;
        });

        EXPECT(s.evaluated() == false);

        const auto first = s.get();
        EXPECT(s.evaluated()  == true);
        const auto second = s.get();

        EXPECT(first == second);
    },
    CASE("CopyAfter" "[tstraus::Lazy]")
    {
        Lazy<string> s1([]() {
            //cout << "evaluating" << endl;

            return "I'm a Lazy Copy After Evaluation";
        });


        EXPECT(s1.evaluated() == false);

        const auto first = s1.get();
        EXPECT(s1.evaluated() == true);

        auto s2 = s1;
        EXPECT(s2.evaluated() == true);

        const auto second = s2.get();
        EXPECT(s1.evaluated() == true);
        EXPECT(s2.evaluated() == true);

        EXPECT(first == second);

    },
    CASE("CopyBefore" "[tstraus::Lazy]")
    {
        Lazy<string> s1([]() {
            //cout << "evaluating" << endl;

            return "I'm a Lazy Copy Before Evaluation";
        });

        auto s2 = s1;

        EXPECT(s1.evaluated() == false);
        EXPECT(s2.evaluated() == false);

        const auto first = s2.get();
        EXPECT(s2.evaluated() == true);

        const auto second = s1.get();
        EXPECT(s1.evaluated() == true);
        EXPECT(s2.evaluated() == true);

        EXPECT(first == second);
    }
};

// run with '-p' to see each test
int main(int argc, char** argv)
{
    return lest::run(t, argc, argv);
}

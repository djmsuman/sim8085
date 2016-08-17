#include <fstream>
#include <iterator>
#include "./libs/engine.h"

bool strequal(const char *src, const char *dst)
{
    while (*src)
    {
        if (*src != *dst)
            return false;
        ++src;
        ++dst;
    }
    return true;
}

const char **gotoSwitch(const char **begin, const char **end, const char *val)
{
    for (; begin != end; ++begin)
        if (strequal(*begin, val))
            break;
    return begin;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    CPU cpu;
    ifstream inFile;
    ios_base::sync_with_stdio(false);
    cout << "Intel(R) 8085 Simulator\n";
    if (argc > 1)
    {
        const char **param_end = argv + argc;
        const char **parm = gotoSwitch(argv, param_end, "-f");
        if (parm != param_end) //i.e parameter found
        {
            if (++parm != param_end) // next paremeter is not end of the array also increment the paremeter at the same time
            {
                cout << "Opening file\"" << *parm << "\"" << endl;
                inFile.open(*parm);
                if (!inFile.is_open() || !inFile.good())
                {
                    cerr << "Error opening file." << endl;
                    return 4;
                }
                hexcode_parse(cpu, inFile);
                cout << "loading complete.\n"
                     << endl;
                inFile.close();
            }
        }
    }
    if (!inFile.is_open())
        cout << "Going into Trainer kit mode" << endl;
    reploop(cpu);
    return 0;
}

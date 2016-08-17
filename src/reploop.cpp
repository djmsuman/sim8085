#include "./libs/engine.h"
#include <string>  // for stl string class
#include <sstream> // for stringstream. used for extracting formated inputs from a string. e.g. extracting aboth string & hex from another given string
#include <bitset>  // for bitset. used for converting numbers to binary
#include <cstdlib> // for exit(int);

//handy String manupulation function(maybe called utilitiy functions)
// changes a range of any string to lowercase
// this function takes range of string using iterators
void string_tolower(std::string::iterator begin, std::string::iterator end)
{
    for (; begin != end; ++begin)
    {
        if (*begin >= 'A' && *begin <= 'Z')
            *begin += ('a' - 'A'); // iterators class overloads operator *, to give actual content pointed by current iterators
    }
}

//Function's for pretty printing
//Prints CPU flags with proper spacing in oneline.
void printFlags(const CPU &cpu)
{
    using namespace std;
    cout << "(Flags) "
         << "S: " << cpu.S
         << " Z: " << cpu.Z
         << " AC: " << cpu.AC
         << " P: " << cpu.P
         << " CY: " << cpu.CY << endl;
}
//Prints CPU registors with proper spacing
void printRegister(CPU &cpu)
{
    using namespace std;
    cout << "(Register)           Value  Binary\n"
         << "Accumulator A        "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.A) << "     "
         << bitset<8>(cpu.A) << "\n"
         << "Register B           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.B) << "     "
         << bitset<8>(cpu.B) << "\n"
         << "Register C           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.C) << "     "
         << bitset<8>(cpu.C) << "\n"
         << "Register D           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.D) << "     "
         << bitset<8>(cpu.D) << "\n"
         << "Register E           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.E) << "     "
         << bitset<8>(cpu.E) << "\n"
         << "Register H           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.H) << "     "
         << bitset<8>(cpu.H) << "\n"
         << "Register L           "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.L) << "     "
         << bitset<8>(cpu.L) << "\n"
         << "MemoryPointer(M)     "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.memory[cpu.putHL()]) << "     "
         << bitset<8>(cpu.memory[cpu.putHL()]) << "\n"
         << "StackPointer         "
         << setfill('0') << setw(2) << hex << static_cast<uint>(cpu.SP) << "     "
         << bitset<16>(cpu.SP)
         << endl;
}
// Takes 2 Vector iterator, begin ,end
// Which is a vector contaning some memory(ram) address
// Ram::AddrIter is typedef for std::vector<Byte2>::iterator
// The prints the address & content of whole address stored in vector range specified by iterator
void printMemoryRange(Ram::AddrIter begin, Ram::AddrIter end, CPU &cpu)
{
    using namespace std;
    do
    {
        cout << setfill('0') << setw(4) << hex << static_cast<uint>(*begin) << ": "
             << static_cast<uint>(cpu.memory[*begin])
             << endl;
    } while (begin++ != end);
}
// Prints the address & content of memory address stored in usedAddress vector
// Ram::uaBegin() & Ram::uaEnd() gives the iterator of usedAddress
// This function sorts the address in the vector and use printMemoryRange() func
void printUsedMemory(CPU &cpu)
{
    Ram::AddrIter i = cpu.memory.uaBegin();
    Ram::AddrIter end = cpu.memory.uaEnd();
    std::sort(cpu.memory.uaBegin(), cpu.memory.uaEnd());
    printMemoryRange(i, end, cpu);
} // Prints the address & content of memory address stored in loadedAddress vector
// Ram::laBegin() & Ram::laEnd() gives the iterator of Ram::loadedAddress vector
// This function sorts the address in the vector and use printMemoryRange() func
void printLoadedMemory(CPU &cpu)
{
    using namespace std;
    Ram::AddrIter i = cpu.memory.laBegin();
    Ram::AddrIter end = cpu.memory.laEnd();
    sort(cpu.memory.laBegin(), cpu.memory.laEnd());
    printMemoryRange(i, end, cpu);
}
// Shortcut function for printing Flags, Registor and usedMemory
// This function call other printing function to do pretty printing
void printFRUm(CPU &cpu)
{
    printFlags(cpu);
    printRegister(cpu);
    printUsedMemory(cpu);
}
// Checks if atmost only last 8 bits are sets in num variable
bool expect_byte(uint num)
{
    return num == (num & 0xFF);
}
// Checks if atmost only last 16 bits are sets in num variable
bool expect_byte2(uint num)
{
    return num == (num & 0xFFFF);
}
// help message about the interactive mode
void help()
{
    using namespace std;
    cout << "h|help          Print this message\n\n"
         << "s|step [n]      Step n instructions. If n is not given it defaults to 1\n\n"
         << "r|run           Execute all loaded instructions from the current position\n\n"
         << "H|halt|stop     Stop execution and print the current flags & registors & used memory\n\n"
         << "p|print rf or [a|b|c|d|e|h|l|bc|de|hl|pc|sp] or [f|flags] or r or m <memory address>\n"
         << "                Prints the corosponding thing. rf = registors & flags\n"
         << "                in p m <addr> if memory address <addr> is missing then it prints memory pointed by HL registers\n"
         << "                e.g. 'p m c050' prints the memory c050.\n\n"
         << "p|print lmem    Print memory where instruction's were loaded from file\n"
         << "p|print umem    Print memory which were accessed by user\n\n"
         << "S|set [a|b|c|d|e|h|l|bc|de|hl|pc|sp] or [s|z|ac|p|cy] or m <memory address> <value>\n"
         << "                The last argument value is reqired as valid HEX number.\n\n"
         << "mem|m <start-address> <end-address>\n"
         << "                Prints the memory range. Address in hexadecimals\n\n"
         << "memclear        Clears the memory.\n"
         << "memset <start-address> <end-address>\n"
         << "                Insert value in the specified memory range.\n"
         << "                This options are available in this mode:\n"
         << "                <hexcode> => sets the value at current memory position.\n"
         << "                ok => write the memory and go into previous mode.\n"
         << "                + => increment current memory value by 1\n"
         << "                p => steps a memory cell back\n"
         << "exit            Immediately exits the simulator."
         << endl;
}

void reploop(CPU &cpu)
{
    using namespace std;
    cout << "Interactive mode.\nEnter h or help for help" << endl;
    string cmd;
    uint arg;
    while (true)
    {
        cout << setfill('0') << setw(4) << hex << (uint)cpu.putPC() << "> ";
        getline(cin, cmd);
        stringstream ss(cmd);
        ss >> cmd;
        if (cmd == "help" || cmd == "h")
            help();
        else if (cmd == "step" || cmd == "s")
        {
            uint count;
            if (ss >> count)
            {
                while (count-- > 0)
                    if (cpu.step() == false)
                    {
                        printFRUm(cpu);
                        break;
                    }
            }
            else if (cpu.step() == false)
            {
                printFRUm(cpu);
                break;
            }
        }
        else if (cmd == "run" || cmd == "r")
        {
            while (cpu.step())
                ;
            printFRUm(cpu);
        }
        else if (cmd == "halt" || cmd == "stop" || cmd == "H")
        {
            printFlags(cpu);
            printRegister(cpu);
            break;
        }
        else if (cmd == "print" || cmd == "p")
        {
            if (!(ss >> cmd))
            {
                printFRUm(cpu); // no more augument
                continue;
            }
            string_tolower(cmd.begin(), cmd.end());
            if (cmd == "m" || cmd == "mem")
            {
                if (!(ss >> hex >> arg)) // if no address given... then show memory pointed by hl
                    cout << setfill('0') << setw(2) << hex << (uint)cpu.memory[cpu.putHL()] << " Binary:" << bitset<8>(cpu.memory[cpu.putHL()]) << endl;
                else
                    cout << setfill('0') << setw(2) << hex << (uint)cpu.memory[static_cast<Byte2>(arg & 0xFFFF)] << " Binary:" << bitset<8>(cpu.memory[static_cast<Byte2>(arg & 0xFFFF)]) << endl;
            }
            else if (cmd == "lmem")
                printLoadedMemory(cpu);
            else if (cmd == "umem")
                printUsedMemory(cpu);
            else if (cmd == "r")
                printRegister(cpu);
            else if (cmd == "rf" || cmd == "fr")
            {
                printFlags(cpu);
                printRegister(cpu);
            }
            else if (cmd == "f" || cmd == "flags")
                printFlags(cpu);
            else if (cmd == "a")
                cout << hex << (uint)cpu.A << " binary: " << bitset<8>(cpu.A) << endl;
            else if (cmd == "b")
                cout << hex << (uint)cpu.B << " binary: " << bitset<8>(cpu.B) << endl;
            else if (cmd == "c")
                cout << hex << (uint)cpu.C << " binary: " << bitset<8>(cpu.C) << endl;
            else if (cmd == "d")
                cout << hex << (uint)cpu.D << " binary: " << bitset<8>(cpu.D) << endl;
            else if (cmd == "e")
                cout << hex << (uint)cpu.E << " binary: " << bitset<8>(cpu.E) << endl;
            else if (cmd == "h")
                cout << hex << (uint)cpu.H << " binary: " << bitset<8>(cpu.H) << endl;
            else if (cmd == "l")
                cout << hex << (uint)cpu.L << " binary: " << bitset<8>(cpu.L) << endl;
            else if (cmd == "bc")
                cout << hex << (uint)cpu.putBC() << " binary: " << bitset<16>((uint)cpu.putBC()) << endl;
            else if (cmd == "de")
                cout << hex << (uint)cpu.putDE() << " binary: " << bitset<16>((uint)cpu.putDE()) << endl;
            else if (cmd == "hl")
                cout << hex << (uint)cpu.putHL() << " binary: " << bitset<16>((uint)cpu.putHL()) << endl;
            else if (cmd == "pc")
                cout << hex << (uint)cpu.putPC() << " binary: " << bitset<16>((uint)cpu.putPC()) << endl;
            else if (cmd == "sp")
                cout << hex << (uint)cpu.putSP() << " binary: " << bitset<16>((uint)cpu.putSP()) << endl;
        }
        else if (cmd == "mem" || cmd == "m")
        {
            uint start, end;
            if (ss >> hex >> start && ss >> hex >> end)
            {
                if (!expect_byte2(start) && !expect_byte2(end))
                    cout << "Address out of range(>= 0xFFFF)" << endl;
                else
                    for (; start <= end; ++start)
                        cout << setfill('0') << setw(4) << hex << start
                             << ": " << setfill('0') << setw(2) << hex << (uint)cpu.memory[start & 0xFFFF]
                             << endl;
            }
            else
                cout << "Wrong address range" << endl;
        }
        else if (cmd == "memclear")
        {
            cpu.memory.clear();
        }
        else if (cmd == "memset")
        {
            uint addrStart, addrEnd;
            if (ss >> hex >> addrStart >> hex >> addrEnd)
            {
                if (expect_byte2(addrStart) && expect_byte2(addrEnd))
                {
                    cpu.memory.jump(addrStart);
                    while (cpu.memory.currentInsPos() <= addrEnd)
                    {
                        // Prompt, address(16bit): data(8bit)
                        cout << setfill('0') << setw(4) << (uint)cpu.memory.currentInsPos() << ": " << setw(2) << hex << (uint)cpu.memory.currentIns() << "> ";
                        cin >> cmd;
                        if (cmd == "ok")
                            break;
                        else if (cmd == "+")
                        {
                            arg = cpu.memory.currentIns();
                            cpu.memory.jump(cpu.memory.currentInsPos() - 1);
                            cpu.memory.append_inst(arg++);
                        }
                        else if (cmd == "p")
                            cpu.memory.jump(cpu.memory.currentInsPos() - 1);
                        else
                        {
                            stringstream hxss(cmd);
                            if (hxss >> hex >> arg)
                            {
                                if (expect_byte(arg))
                                    cpu.memory.append_inst(arg);
                            }
                            else
                                cout << "Value(8bit) as hex code expected." << endl;
                        }
                    } //while under memset
                }
                else
                    cout << "range address is not under 0xFFFF" << endl;
            }
            else
                cout << "address range must be suppied with memset" << endl;
            continue;
        }
        else if (cmd == "set" || cmd == "S")
        {
            ss >> cmd;
            string_tolower(cmd.begin(), cmd.end());
            ss >> hex >> arg;
            //cout << "cmd: " << cmd << endl;
            //cout << "argument: " << hex << arg << endl;
            if (cmd == "a" && expect_byte(arg))
                cpu.A = static_cast<Byte>(arg);
            else if (cmd == "b" && expect_byte(arg))
                cpu.B = static_cast<Byte>(arg);
            else if (cmd == "c" && expect_byte(arg))
                cpu.C = static_cast<Byte>(arg);
            else if (cmd == "d" && expect_byte(arg))
                cpu.D = static_cast<Byte>(arg);
            else if (cmd == "e" && expect_byte(arg))
                cpu.E = static_cast<Byte>(arg);
            else if (cmd == "h" && expect_byte(arg))
                cpu.H = static_cast<Byte>(arg);
            else if (cmd == "l" && expect_byte(arg))
                cpu.L = static_cast<Byte>(arg);

            else if (cmd == "bc" && expect_byte2(arg))
                cpu.BC = static_cast<Byte2>(arg);
            else if (cmd == "de" && expect_byte2(arg))
                cpu.DE = static_cast<Byte2>(arg);
            else if (cmd == "hl" && expect_byte2(arg))
                cpu.HL = static_cast<Byte2>(arg);
            else if (cmd == "pc" && expect_byte2(arg))
                cpu.PC = static_cast<Byte2>(arg);
            else if (cmd == "sp" && expect_byte2(arg))
                cpu.SP = static_cast<Byte2>(arg);

            else if (cmd == "s")
                cpu.S = arg & 0x1;
            else if (cmd == "z")
                cpu.Z = arg & 0x1;
            else if (cmd == "ac")
                cpu.AC = arg & 0x1;
            else if (cmd == "p")
                cpu.P = arg & 0x1;
            else if (cmd == "cy")
                cpu.CY = arg & 0x1;

            else if (cmd == "mem" && expect_byte2(arg))
            {
                uint val;
                if (!(ss >> hex >> val))
                {
                    cout << "No value given." << endl;
                    continue;
                }
                else
                    //cout << hex << val  << endl;
                    if (!expect_byte(val))
                    cout << "value too big. Expected a byte(max FF)" << endl;
                else
                    cpu.memory[arg] = val;
            }
            else
                cout << "Wrong arguments" << endl;
        }
        else if (cmd == "exit")
        {
            exit(109);
        }
        else
        {
            cout << "Unknown command, " << cmd << endl;
        }
    } // while
    cout << "========== Exiting ==========" << endl;
}

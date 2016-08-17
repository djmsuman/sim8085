#include "./libs/engine.h"

/*
* @return total nibble
*/
int hexcode_parse(CPU &cpu, std::istream &hexcode_stream)
{
    using namespace std;
    int nibble_count = 0;
    unsigned int byte1, byte2;
    unsigned int opcode;
    Byte2 b2;
    char ch;
    while (hexcode_stream >> ch)
    {
        if (ch == '@')
        {
            hexcode_stream >> hex >> byte1;
            hexcode_stream >> hex >> byte2;
            RegPair addr;
            addr.reg_right = byte1;
            addr.reg_left = byte2;
            //byte2 = (byte2 << 8) | (byte1);
            b2 = addr.regPair;
            cpu.memory.jump(b2);
            cout << "Jumping to: " << setfill('0') << setw(4) << hex << (uint)cpu.memory.currentInsPos() << endl;
        }
        else
        {
            hexcode_stream.unget();
        }
        hexcode_stream >> hex >> opcode;
        cpu.memory.append_inst(opcode);
        //cout << "opcode: " << hex << opcode << endl;
        nibble_count++;
    }
    cpu.gotoFirstInst();
    cout << "Total bytes: " << dec << nibble_count << endl;
    return nibble_count;
}

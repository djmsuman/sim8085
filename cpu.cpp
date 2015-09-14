#include "core.h"
#include <iostream>
#include "opcodes.h"
#include <iomanip>
#include <bitset>

#define set 1
#define reset 0

CPU::CPU()
    : BC(0), DE(0), HL(0),
      A(0), B(BC.reg_left), C(BC.reg_right), D(DE.reg_left), E(DE.reg_right), H(HL.reg_left), L(HL.reg_right),
      SP(0), PC(0),
      S(0), Z(0), AC(0), P(0), CY(0)
{

}

CPU::~CPU()
{
}

void CPU::gotoFirstInst()
{
    PC = memory.loadedAddress.front();
}

void CPU::manip_sign(Byte& reg)
{
    if (reg & 0x80)
        S = set;
    else
        S = reset;
}

void CPU::manip_zero(Byte& reg)
{
    if (reg == 0x00)
        Z = set;
    else
        Z = reset;
}

void CPU::manip_parity(Byte& reg)
{
    using namespace std;
    bitset<8> abits(reg);
    if (abits.count() % 2 == 0x00)
        P = set;
    else
        P = reset;
}

bool CPU::step()
{
    using namespace std;
    Byte ob1, ob2;
    Byte2 obd1, obd2, obd3;
    uint operand1, operand2;

    switch (memory.memory[PC])
    {
    case ACI:
        obd1 = A;
        obd2 = memory.memory[++PC];
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_A:
        obd1 = A;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_B:
        obd1 = A;
        obd2 = B;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_C:
        obd1 = A;
        obd2 = C;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_D:
        obd1 = A;
        obd2 = D;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_E:
        obd1 = A;
        obd2 = E;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_H:
        obd1 = A;
        obd2 = H;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_L:
        obd1 = A;
        obd2 = L;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADC_M:
        obd1 = A;
        obd2 = memory.memory[HL.regPair];
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += CY;
        obd2 += obd1;
        A = obd2 & 0xFF;
        /* All Flags are modified to reflect the result. */
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_A:
        obd1 = A;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_B:
        obd1 = A;
        obd2 = B;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_C:
        obd1 = A;
        obd2 = C;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_D:
        obd1 = A;
        obd2 = D;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_E:
        obd1 = A;
        obd2 = E;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_H:
        obd1 = A;
        obd2 = H;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_L:
        obd1 = A;
        obd2 = L;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADD_M:
        obd1 = A;
        obd2 = memory.memory[HL.regPair];
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 = obd1 + obd2;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ADI:
        obd1 = A;
        obd2 = memory.memory[++PC];
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case ANA_A:
        A = A & A;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_B:
        A = A & B;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_C:
        A = A & C;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_D:
        A = A & D;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_E:
        A = A & E;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_H:
        A = A & H;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_L:
        A = A & L;
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANA_M:
        A = A & memory.memory[HL.regPair];
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case ANI:
        A = A & memory.memory[++PC];
        /* Only S, Z, P are modified to reflect the result. CY is reset and AC is set. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case CALL:
        ob1 = memory.memory[++PC]; //lsb
        obd1 = memory.memory[++PC] ; //msb
        obd1 = (obd1 << 8) | ob1;
        if (SP == 0x0)
            SP = 0XFFFF;
        else
            SP = SP - 1;
        ob1 = (PC + 1) & 0xFF; //lsb
        ob2 = (PC + 1) >> 8; //msb
        memory.memory[SP--] = ob2; //msb
        memory.memory[SP] = ob1; //lsb
        PC = obd1;
        cout << "CALL " << hex << (uint)PC << endl;
        return true;
        break;
    case CMA:
        A = ~A;
        /* No flags are modified. */
        break;
    case CMC:
        CY = !CY;
        /* No flags are modified except Carry, which is complemented. */
        break;
    case CMP_A:
        if ( A < A)
        {
            CY = set;
            Z = reset;
        }
        else if (A == A)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_B:
        if ( A < B)
        {
            CY = set;
            Z = reset;
        }
        else if (A == B)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_C:
        if ( A < C)
        {
            CY = set;
            Z = reset;
        }
        else if (A == C)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_D:
        if ( A < D)
        {
            CY = set;
            Z = reset;
        }
        else if (A == D)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_E:
        if ( A < E)
        {
            CY = set;
            Z = reset;
        }
        else if (A == E)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_H:
        if ( A < H)
        {
            CY = set;
            Z = reset;
        }
        else if (A == H)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_L:
        if ( A < L)
        {
            CY = set;
            Z = reset;
        }
        else if (A == L)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CMP_M:
        if ( A < memory.memory[HL.regPair])
        {
            CY = set;
            Z = reset;
        }
        else if (A == memory.memory[HL.regPair])
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case CC:
        if (CY == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        ++PC;
        ++PC;
        break;
    case CM:
        if (S == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CNC:
        if (CY == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CNZ:
        if (Z == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CP:
        if (S == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CPE:
        if (P == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CPO:
        if (P == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CZ:
        if (Z == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            obd1 = memory.memory[++PC] ; //msb
            obd1 = (obd1 << 8) | ob1;
            if (SP == 0x0)
                SP = 0XFFFF;
            else
                SP = SP - 1;
            ob1 = (PC + 1) & 0xFF; //lsb
            ob2 = (PC + 1) >> 8; //msb
            memory.memory[SP--] = ob2; //msb
            memory.memory[SP] = ob1; //lsb
            PC = obd1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        /* No flags are modified. */
        break;
    case CPI:
        ob1 = memory.memory[++PC];
        if ( A < ob1)
        {
            CY = set;
            Z = reset;
        }
        else if (A == ob1)
        {
            CY = reset;
            Z = set;
        }
        else
            CY = Z = reset;
        break;
    case DAA:
        obd1 = A;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        /* All Flags are modified to reflect the result. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case DAD_B:
        operand1 = HL.regPair;
        operand2 = BC.regPair;
        operand2 += operand1;
        HL = (Byte2)(operand2 & 0XFFFF);
        /* Only Carry flag is modified to reflect the result. */
        CY = operand2 >> 16;
        break;
    case DAD_D:
        operand1 = HL.regPair;
        operand2 = DE.regPair;
        operand2 += operand1;
        HL = (Byte2)(operand2 & 0XFFFF);
        /* Only Carry flag is modified to reflect the result. */
        CY = operand2 >> 16;
        break;
    case DAD_H:
        operand1 = HL.regPair;
        operand2 = HL.regPair;
        operand2 += operand1;
        HL = (Byte2)(operand2 & 0XFFFF);
        /* Only Carry flag is modified to reflect the result. */
        CY = operand2 >> 16;
        break;
    case DAD_SP:
        operand1 = HL.regPair;
        operand2 = BC.regPair;
        operand2 += operand1;
        HL = (Byte2)(operand2 & 0XFFFF);
        /* Only Carry flag is modified to reflect the result. */
        CY = operand2 >> 16;
        break;
    case DCR_A:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (A & 0x0F)) >> 4;
        A = ob1 + A;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case DCR_B:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (B & 0x0F)) >> 4;
        B = ob1 + B;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(B);
        manip_zero(B);
        manip_parity(B);
        break;
    case DCR_C:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (C & 0x0F)) >> 4;
        C = ob1 + C;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(C);
        manip_zero(C);
        manip_parity(C);
        break;
    case DCR_D:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (D & 0x0F)) >> 4;
        D = ob1 + D;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(D);
        manip_zero(D);
        manip_parity(D);
        break;
    case DCR_E:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (E & 0x0F)) >> 4;
        E = ob1 + E;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(E);
        manip_zero(E);
        manip_parity(E);
        break;
    case DCR_H:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (H & 0x0F)) >> 4;
        H = ob1 + H;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(H);
        manip_zero(H);
        manip_parity(H);
        break;
    case DCR_L:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        AC = ((ob1 & 0x0F) + (L & 0x0F)) >> 4;
        L = ob1 + L;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(L);
        manip_zero(L);
        manip_parity(L);
        break;
    case DCR_M:
        ob1 = 0x01;
        ob1 = ~ob1 + 1;
        ob2 = memory.memory[HL.regPair];
        AC = ((ob1 & 0x0F) + (ob2 & 0x0F)) >> 4;
        memory.memory[HL.regPair] = ob1 + ob2;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(memory.memory[HL.regPair]);
        manip_zero(memory.memory[HL.regPair]);
        manip_parity(memory.memory[HL.regPair]);
        break;
    case DCX_B:
        BC = BC.regPair - 1;
        /* No flags are modified. */
        break;
    case DCX_D:
        DE = DE.regPair - 1;
        /* No flags are modified. */
        break;
    case DCX_H:
        HL = HL.regPair - 1;
        /* No flags are modified. */
        break;
    case DCX_SP:
        SP = SP - 1;
        /* No flags are modified. */
        break;
    case HLT:
        cout << setfill('0') << setw(4) << hex << PC << " -> HLT" << endl;
        return false;
        break;
    case INR_A:
        AC = ((A & 0x0F) + 1) >> 4;
        A = A + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case INR_B:
        AC = ((B & 0x0F) + 1) >> 4;
        B = B + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(B);
        manip_zero(B);
        manip_parity(B);
        break;
    case INR_C:
        AC = ((C & 0x0F) + 1) >> 4;
        C = C + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(C);
        manip_zero(C);
        manip_parity(C);
        break;
    case INR_D:
        AC = ((D & 0x0F) + 1) >> 4;
        D = D + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(D);
        manip_zero(D);
        manip_parity(D);
        break;
    case INR_E:
        AC = ((E & 0x0F) + 1) >> 4;
        E = E + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(E);
        manip_zero(E);
        manip_parity(E);
        break;
    case INR_H:
        AC = ((H & 0x0F) + 1) >> 4;
        H = H + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(H);
        manip_zero(H);
        manip_parity(H);
        break;
    case INR_L:
        AC = ((L & 0x0F) + 1) >> 4;
        L = L + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(L);
        manip_zero(L);
        manip_parity(L);
        break;
    case INR_M:
        AC = ((memory.memory[HL.regPair] & 0x0F) + 1) >> 4;
        memory.memory[HL.regPair] = memory.memory[HL.regPair] + 1;
        /* S, Z, P, AC are modified to reflect the result. CY is not modified.*/
        manip_sign(memory.memory[HL.regPair]);
        manip_zero(memory.memory[HL.regPair]);
        manip_parity(memory.memory[HL.regPair]);
        break;
    case INX_B:
        BC.regPair++;
        break;
    case INX_D:
        DE.regPair++;
        break;
    case INX_H:
        HL.regPair++;
        break;
    case INX_SP:
        SP++;
        break;
    case JMP:
        ob1 = memory.memory[++PC]; //lsb
        ob2 = memory.memory[++PC]; //msb
        PC = ob2;
        PC = (PC << 8) | ob1;
        return true;
        break;
    case JC:
        if (CY == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JNC:
        if (CY == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JP:
        if (S == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JM:
        if (S == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JPE:
        if (P == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JPO:
        if (P == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JZ:
        if (Z == set)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case JNZ:
        if (Z == reset)
        {
            ob1 = memory.memory[++PC]; //lsb
            ob2 = memory.memory[++PC]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
            return true;
        }
        else
        {
            ++PC;
            ++PC;
        }
        break;
    case LDA:
        ob1 = memory.memory[++PC]; //lsb
        obd1 = memory.memory[++PC]; //msb
        obd1 = (obd1 << 8) | ob1;
        A = memory.memory[obd1];
        break;
    case LDAX_B:
        A = memory.memory[BC.regPair];
        /* No flags are modified. */
        break;
    case LDAX_D:
        A = memory.memory[DE.regPair];
        /* No flags are modified. */
        break;
    case LHLD:
        ob1 = memory.memory[++PC]; //lsb
        obd1 = memory.memory[++PC]; //msb
        obd1 = (obd1 << 8) | ob1;
        L = memory.memory[obd1++];
        H = memory.memory[obd1];/* No flags are modified. */
        break;
    case LXI_B:
        this->C = memory.memory[++PC];
        this->B = memory.memory[++PC];
        /* No flags are modified. */
        break;
    case LXI_D:
        this->E = memory.memory[++PC];
        this->D = memory.memory[++PC];
        /* No flags are modified. */
        break;
    case LXI_H:
        this->L = memory.memory[++PC]; //lsb
        this->H = memory.memory[++PC]; //msb
        break;
    case LXI_SP:
        break;
    case MOV_A_A:
        A = A;
        /* No flags are modified. */
        break;
    case MOV_A_B:
        A = B;
        /* No flags are modified. */
        break;
    case MOV_A_C:
        A = C;
        /* No flags are modified. */
        break;
    case MOV_A_D:
        A = D;
        /* No flags are modified. */
        break;
    case MOV_A_E:
        A = E;
        /* No flags are modified. */
        break;
    case MOV_A_H:
        A = H;
        /* No flags are modified. */
        break;
    case MOV_A_L:
        A = L;
        /* No flags are modified. */
        break;
    case MOV_A_M:
        A = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_B_A:
        B = A;
        /* No flags are modified. */
        break;
    case MOV_B_B:
        B = B;
        /* No flags are modified. */
        break;
    case MOV_B_C:
        B = C;
        /* No flags are modified. */
        break;
    case MOV_B_D:
        B = D;
        /* No flags are modified. */
        break;
    case MOV_B_E:
        B = E;
        /* No flags are modified. */
        break;
    case MOV_B_H:
        B = H;
        /* No flags are modified. */
        break;
    case MOV_B_L:
        B = L;
        /* No flags are modified. */
        break;
    case MOV_B_M:
        B = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_C_A:
        C = A;
        /* No flags are modified. */
        break;
    case MOV_C_B:
        C = B;
        /* No flags are modified. */
        break;
    case MOV_C_C:
        C = C;
        /* No flags are modified. */
        break;
    case MOV_C_D:
        C = D;
        /* No flags are modified. */
        break;
    case MOV_C_E:
        C = E;
        /* No flags are modified. */
        break;
    case MOV_C_H:
        C = H;
        /* No flags are modified. */
        break;
    case MOV_C_L:
        C = L;
        /* No flags are modified. */
        break;
    case MOV_C_M:
        C = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_D_A:
        D = A;
        /* No flags are modified. */
        break;
    case MOV_D_B:
        D = B;
        /* No flags are modified. */
        break;
    case MOV_D_C:
        D = C;
        /* No flags are modified. */
        break;
    case MOV_D_D:
        D = D;
        /* No flags are modified. */
        break;
    case MOV_D_E:
        D = E;
        /* No flags are modified. */
        break;
    case MOV_D_H:
        D = H;
        /* No flags are modified. */
        break;
    case MOV_D_L:
        D = L;
        /* No flags are modified. */
        break;
    case MOV_D_M:
        D = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_E_A:
        E = A;
        /* No flags are modified. */
        break;
    case MOV_E_B:
        E = B;
        /* No flags are modified. */
        break;
    case MOV_E_C:
        E = C;
        /* No flags are modified. */
        break;
    case MOV_E_D:
        E = D;
        /* No flags are modified. */
        break;
    case MOV_E_E:
        E = E;
        /* No flags are modified. */
        break;
    case MOV_E_H:
        E = H;
        /* No flags are modified. */
        break;
    case MOV_E_L:
        E = L;
        /* No flags are modified. */
        break;
    case MOV_E_M:
        E = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_H_A:
        H = A;
        /* No flags are modified. */
        break;
    case MOV_H_B:
        H = B;
        /* No flags are modified. */
        break;
    case MOV_H_C:
        H = C;
        /* No flags are modified. */
        break;
    case MOV_H_D:
        H = D;
        /* No flags are modified. */
        break;
    case MOV_H_E:
        H = E;
        /* No flags are modified. */
        break;
    case MOV_H_H:
        H = H;
        /* No flags are modified. */
        break;
    case MOV_H_L:
        H = L;
        /* No flags are modified. */
        break;
    case MOV_H_M:
        H = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_L_A:
        L = A;
        /* No flags are modified. */
        break;
    case MOV_L_B:
        L = B;
        /* No flags are modified. */
        break;
    case MOV_L_C:
        L = C;
        /* No flags are modified. */
        break;
    case MOV_L_D:
        L = D;
        /* No flags are modified. */
        break;
    case MOV_L_E:
        L = E;
        /* No flags are modified. */
        break;
    case MOV_L_H:
        L = H;
        /* No flags are modified. */
        break;
    case MOV_L_L:
        L = L;
        /* No flags are modified. */
        break;
    case MOV_L_M:
        L = memory.memory[HL.regPair];
        /* No flags are modified. */
        break;
    case MOV_M_A:
        memory.memory[HL.regPair] = A;
        /* No flags are modified. */
        break;
    case MOV_M_B:
        memory.memory[HL.regPair] = B;
        /* No flags are modified. */
        break;
    case MOV_M_C:
        memory.memory[HL.regPair] = C;
        /* No flags are modified. */
        break;
    case MOV_M_D:
        memory.memory[HL.regPair] = D;
        /* No flags are modified. */
        break;
    case MOV_M_E:
        memory.memory[HL.regPair] = E;
        /* No flags are modified. */
        break;
    case MOV_M_H:
        memory.memory[HL.regPair] = H;
        /* No flags are modified. */
        break;
    case MOV_M_L:
        memory.memory[HL.regPair] = L;
        /* No flags are modified. */
        break;
    case MVI_A:
        ob2 = memory.memory[++PC];
        A = ob2;
        /* No flags are modified. */
        break;
    case MVI_B:
        ob2 = memory.memory[++PC];
        B = ob2;
        /* No flags are modified. */
        break;
    case MVI_C:
        ob2 = memory.memory[++PC];
        C = ob2;
        /* No flags are modified. */
        break;
    case MVI_D:
        ob2 = memory.memory[++PC];
        D = ob2;
        /* No flags are modified. */
        break;
    case MVI_E:
        ob2 = memory.memory[++PC];
        E = ob2;
        /* No flags are modified. */
        break;
    case MVI_H:
        ob2 = memory.memory[++PC];
        H = ob2;
        /* No flags are modified. */
        break;
    case MVI_L:
        ob2 = memory.memory[++PC];
        L = ob2;
        /* No flags are modified. */
        break;
    case MVI_M:
        ob2 = memory.memory[++PC];
        HL.regPair = ob2;
        /* No flags are modified. */
        break;
    case NOP:
        cout << setfill('0') << setw(4) << hex << PC << " -> NOP" << endl;
        break;
    case ORA_A:
        A = A | A;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_B:
        A = A | B;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_C:
        A = A | C;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_D:
        A = A | D;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_E:
        A = A | E;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_H:
        A = A | H;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_L:
        A = A | L;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORA_M:
        A = A | memory.memory[HL.regPair];
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case ORI:
        A = A | memory.memory[++PC];
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case PCHL:
        PC = HL.regPair;
        break;
    case POP_B:
        C = memory.memory[SP++];
        B = memory.memory[SP++];
        /*No Flags are affected*/
        break;
    case POP_D:
        E = memory.memory[SP++];
        D = memory.memory[SP++];
        /*No Flags are affected*/
        break;
    case POP_H:
        L = memory.memory[SP++];
        H = memory.memory[SP++];
        /*No Flags are affected*/
        break;
    case POP_PSW:
        A = memory.memory[SP++];
        ob1 = memory.memory[SP++];
        break;
    case PUSH_B:
        memory.memory[--SP] = B;
        memory.memory[--SP] = C;
        /*No Flags are affected*/
        break;
    case PUSH_D:
        memory.memory[--SP] = D;
        memory.memory[--SP] = E;
        /*No Flags are affected*/
        break;
    case PUSH_H:
        memory.memory[--SP] = H;
        memory.memory[--SP] = L;
        /*No Flags are affected*/
        break;
    case PUSH_PSW:
        A = memory.memory[--SP];
        ob1 = memory.memory[--SP];
        /*No Flags are affected*/
        break;
    case RAL:
        ob1 = CY;
        CY = (A >> 7);
        A = (A << 1) | ob1;
        break;
    case RAR:
        ob1 = CY;
        CY = A & 0x01;
        A = (A >> 1) | (ob1 << 7);
        break;
    case RLC:
        CY = (A >> 7);
        A = (A << 1) | (A >> 7);
        break;
    case RRC:
        CY = A & 0x1;
        A = (A >> 1) | (A << 7);
        break;
    case RET:
        if (SP == 0)
            SP = 0xFFFF;
        ob1 = memory.memory[SP--]; //lsb
        if (SP == 0)
            SP = 0xFFFF;
        ob2 = memory.memory[SP--]; //msb
        PC = ob2;
        PC = (PC << 8) | ob1;
        break;
    case RC:
        if (CY == set)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RNC:
        if (CY == reset)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RP:
        if (S == reset)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RM:
        if (S == set)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RPE:
        if (P == set)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RPO:
        if (P == reset)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RZ:
        if (Z == set)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case RNZ:
        if (Z == reset)
        {
            if (SP == 0)
                SP = 0xFFFF;
            ob1 = memory.memory[SP--]; //lsb
            if (SP == 0)
                SP = 0xFFFF;
            ob2 = memory.memory[SP--]; //msb
            PC = ob2;
            PC = (PC << 8) | ob1;
        }
        /* No flags are modified. */
        break;
    case SBB_A:
        obd3 = A + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_B:
        obd3 = B + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_C:
        obd3 = C + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_D:
        obd3 = D + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_E:
        obd3 = E + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_H:
        obd3 = H + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_L:
        obd3 = L + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBB_M:
        obd3 = memory.memory[HL.regPair] + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SBI:
        obd3 = memory.memory[++PC] + 1;
        obd1 = ~obd3 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SHLD:
        ob1 = memory.memory[++PC]; //lsb
        obd1 = memory.memory[++PC]; //msb
        obd1 = (obd1 << 8) | ob1;
        memory.memory[obd1++] = L;
        memory.memory[obd1] = H;
        break;
    case SPHL:
        SP = HL.regPair;
        /* No flags are modified. */
        break;
    case STA:
        ob1 = memory.memory[++PC]; //lsb
        obd1 = memory.memory[++PC]; //msb
        obd1 = (obd1 << 8) | ob1;
        memory.memory[obd1] = A;
        /* No flags are modified. */
        break;
    case STAX_B:
        memory.memory[BC.regPair] = A;
        /* No flags are modified. */
        break;
    case STAX_D:
        memory.memory[DE.regPair] = A;
        /* No flags are modified. */
        break;
    case STC:
        CY = set;
        /* No other flags are modified. */
        break;
    case SUB_A:
        obd1 = ~A + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_B:
        obd1 = ~B + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_C:
        obd1 = ~C + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_D:
        obd1 = ~D + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_E:
        obd1 = ~E + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_H:
        obd1 = ~H + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_L:
        obd1 = ~L + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUB_M:
        obd1 = memory.memory[HL.regPair];
        obd1 = ~obd1 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case SUI:
        obd1 = memory.memory[++PC];
        obd1 = ~obd1 + 1;
        obd2 = A;
        AC = ((obd1 & 0X0F) + (obd2 & 0x0F)) >> 4;
        obd2 += obd1;
        A = obd2 & 0xFF;
        CY = obd2 >> 8;
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        break;
    case XCHG:
        ob1 = L; //lsb
        ob2 = H; //msb
        L = E;   //lsb
        H = D;   //msb
        E = L;   //lsb
        D = H;   //msb
        /* No flags are modified. */
        break;
    case XRA_A:
        A = A ^ A;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_B:
        A = A ^ B;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_C:
        A = A ^ C;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_D:
        A = A ^ D;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_E:
        A = A ^ E;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_H:
        A = A ^ H;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_L:
        A = A ^ L;
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRA_M:
        A = A ^ memory.memory[HL.regPair];
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = reset;
        break;
    case XRI:
        A = A ^ memory.memory[++PC];
        /* Only S, Z, P are modified to reflect the result. CY and AC both are reset. */
        manip_sign(A);
        manip_zero(A);
        manip_parity(A);
        CY = reset;
        AC = set;
        break;
    case XTHL:
        ob1 = memory.memory[SP--];  //msb
        ob2 = memory.memory[SP];    //lsb
        memory.memory[SP++] = L;    //lsb
        memory.memory[SP] = H;      //msb
        L = ob2; //lsb
        H = ob1; //msb
        /* No flags are modified. */
        break;
    case EI:
        cout <<"EI instruction is not implemented.\n";
        break;
    case DI:
        cout <<"DI instruction is not implemented.\n";
        break;
    case IN:
        cout <<"IN instruction is not implemented.\n";
        break;
    case OUT:
        cout<<"OUT instruction is not implemented.\n";
        break;
    case RIM:
        cout<<"RIM instruction is not implemented.\n";
        break;
    case SIM:
        cout<<"SIM instruction is not implemented.\n";
        break;
    case RST_0:
        cout<<"RST_0 instruction is not implemented.\n";
        break;
    case RST_1:
        cout<<"RST_1 instruction is not implemented.\n";
        break;
    case RST_2:
        cout<<"RST_2 instruction is not implemented.\n";
        break;
    case RST_3:
        cout<<"RST_3 instruction is not implemented.\n";
        break;
    case RST_4:
        cout<<"RST_4 instruction is not implemented.\n";
        break;
    case RST_5:
        cout<<"RST_5 instruction is not implemented.\n";
        break;
    case RST_6:
        cout<<"RST_6 instruction is not implemented.\n";
        break;
    case RST_7:
        cout<<"RST_7 instruction is not implemented.\n";
        break;
    default:
        cout << "INVALID OPCODE : " << hex << (uint)memory.memory[PC]
             << " at: " << setfill('0') << setw(4) << hex
             << static_cast<uint>(PC) << endl;
    }//switch
    if (PC == 0XFFFF)
        return false;
    ++PC;
    return true;
}//step()


//A = (( ((ob1 & 0xF0) >> 4) + ((A & 0xF0) >> 4) + AC) << 4) | ((ob1 & 0x0F) + (A & 0x0F));
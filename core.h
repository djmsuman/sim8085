#ifndef DEBDEEPPRJ_CORE_H
#define DEBDEEPPRJ_CORE_H

#include <iostream>
#include <vector>
#include "datatypes.h"

class CPU;
class Ram {
protected:
	Byte *memory;
	int _refcount;
	Byte2 _currentpos; // next push instruction offset, used by append_inst
	int _SIZE;
	std::vector<Byte2> usedAddress; // list of address accessed by operator[]
	std::vector<Byte2> loadedAddress; // list of address loaded by parser
public:
	friend class CPU;
	typedef std::vector<Byte2>::iterator AddrIter;
	Ram(int SIZE = 64 * 1024); // 2^(6+10) = 2^16
	Ram(Ram& r); //copy constructor
	~Ram();
	void clear();
	//Use this operator for setting & getting memory data
	Byte& operator[] (const Byte2 addr);

	//Next Position where instruction will be loaded by append_inst function
	Byte2 currentInsPos() const { return _currentpos;}
	Byte currentIns() const { return memory[_currentpos];}
	// Use this for inserting instruction
	void append_inst(Byte val);
	//used for explictley setting address for next instruction, used with append_inst() function
	Byte2 jump(Byte2 nextNibleoffset);
	AddrIter uaBegin(); // Used Address Iterator begin
	AddrIter uaEnd(); // Used Address Iterator end
	AddrIter laBegin(); // Loaded Address Iterator begin
	AddrIter laEnd(); // Loaded Address Iterator end
};

/*This union is used for Accessing a 16 bit data as 16bit, and 8 bit pair at the same time
We have used this union and c++ reference to keep only one copy of data in regitor pair
and individual registor.
e.g.
HL registor is a RegPair type union
if we access Hl.regPair or assgin HL to any 16bit or large integer type we get 16 bit data.
H is a reference to type Byte and Initialized by H(HL.reg_left)
simillarly L is also a reference to type Byte and Initialized by H(HL.reg_right)
we get MSB & LSB of HL through H & L variables directly
*/
union RegPair {
	Byte2 regPair;
	struct {
		Byte reg_right;
		Byte reg_left;
	};
	RegPair(Byte2 b = 0): regPair(b) {}
};

class CPU {
public:
	RegPair BC, DE, HL;
	Byte A;
	Byte &B, &C, &D, &E, &H, &L;
	Byte2 SP, PC;
	bool S, Z, AC, P, CY;
	Ram memory;

public:
	CPU();
	~CPU();

	Byte putB() const {return B; }
	Byte putC() const {return C; }
	Byte putD() const {return D; }
	Byte putE() const {return E; }
	Byte putH() const {return H; }
	Byte putL() const {return L; }

	Byte2 putBC() const { return BC.regPair; }
	Byte2 putDE() const { return DE.regPair; }
	Byte2 putHL() const { return HL.regPair; }
	Byte putA() const { return	A; }
	Byte2 putSP() const { return	SP; }
	Byte2 putPC() const { return	PC; }

	bool putS() const { return S; }
	bool putZ()const { return Z; }
	bool putAC()const { return AC; }
	bool putP()const { return P; }
	bool putCY()const { return CY; }
	//Call this after loading instruction to ram from parser to set PC appropiately
	void gotoFirstInst();
	//@return true if current instruction is not HLT
	// if current instruction is HLT it returns false
	bool step();

private:
	void manip_sign(Byte& reg);
	void manip_zero(Byte& reg);
	void manip_parity(Byte& reg);
};

#endif // DEBDEEPPRJ_CORE_H
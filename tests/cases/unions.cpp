#include "../../src/libs/core.h"
#include "../libs/catch.hpp"

TEST_CASE("RegPair union alignment","[unions]"){
	RegPair r;
	REQUIRE(r.regPair == 0);
	REQUIRE(r.reg_left == 0);
	REQUIRE(r.reg_right == 0);
	SECTION("changing most signficant byte reg1 to 0x80"){
		r.reg_left = 0x80;
		REQUIRE(r.regPair == 0x8000);
		REQUIRE(r.reg_left == 0x80);
		REQUIRE(r.reg_right == 0x00);
	}
	SECTION("changing lest signficant byte reg2 to 0x01"){
		r.reg_right = 0x01;
		REQUIRE(r.regPair == 0x0001); //
		REQUIRE(r.reg_left == 0x00);
		REQUIRE(r.reg_right == 0x01);
	}
	SECTION("changing both byte 0x88 0x33"){
		r.reg_left = 0x88; // 1000 1000
		r.reg_right = 0x33; // 0011 0011
		REQUIRE(r.regPair == 0x8833); //
		REQUIRE(r.reg_left == 0x88);
		REQUIRE(r.reg_right == 0x33);
	}
	SECTION("changing regPair"){
		r.regPair = 0x8833;
		REQUIRE(r.regPair == 0x8833);
		REQUIRE(r.reg_left == 0x88);
		REQUIRE(r.reg_right == 0x33);
	}
}

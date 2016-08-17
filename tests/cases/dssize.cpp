#include "../libs/catch.hpp"
#include "../../src/libs/core.h"
#include "../../src/libs/datatypes.h"

TEST_CASE("critical & customs datatypes/typedefs expected size","[expected_size]"){
	REQUIRE(sizeof(Byte) == 1);
	REQUIRE(sizeof(Byte2) == 2);
	REQUIRE(sizeof(RegPair) == 2);
}
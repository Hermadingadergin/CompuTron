#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE

#include "catch2\catch.hpp"
#include "computron.h"

TEST_CASE("Testing valid load_from_file")
{
	std::array<int, memorySize> memory{ 0 };
	CHECK_NOTHROW(load_from_file(memory, "p1.txt")); // should be able to read p1.txt
}

TEST_CASE("Testing invalid load_from_file")
{
	std::array<int, memorySize> memory2{ 0 };
	CHECK_THROWS(load_from_file(memory2, "lmnop.txt")); // should not be able to read p2.txt because it does not exist
}

TEST_CASE("Test validWord")
{
	for (int i = -minWord; i <= maxWord; i++)
	{
		CHECK(validWord(i));
	}
	CHECK_FALSE(validWord(10000)); // invalid, too large
	CHECK_FALSE(validWord(-10000)); // invalid, too small
}


TEST_CASE("Test read, write, add, and halt operation")
{
	std::array<int, memorySize> memory{ 1007, 1008, 2007, 3008, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, add operand B to accumulator,
																					// store output to 09, writes output to 09, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 19, 10 }; // 19 + 10 = 29, normal addition

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 29);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1007, 1008, 2007, 3008, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, add operand B to accumulator,
																					 // store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;
	const std::vector<int> inputs2{ -5, -7 }; // -5 + -7 = -12, adding negative numbers

	execute(memory2, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == -12);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory3{ 1009, 1010, 1011, 2009, 3010, 3011, 2112, 1112, 4300 }; // read operand A to 09, read operand B to 09, read operand C to 10,
																								 // load operand A to accumulator, add operand B to accumulator, add operand C to accumulator, store output to 12, writes output to 12, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs3{ -5, -7, 14 }; // -5 + -7 + 14 = 2, adding 3 numbers

	execute(memory3, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs3);

	CHECK(accumulator == 2);
	CHECK(instructionCounter == 8); // instructions range from 0 to 8
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



}

TEST_CASE("Test read, write, subtract, and halt operation")
{
	std::array<int, memorySize> memory{ 1007, 1008, 2007, 3108, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator,
																					// subtract operand B from accumulator, store output to 09, writes output to 09, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 19, 10 }; // 19 - 10 = 9, normal subtraction

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 9);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1007, 1008, 2007, 3108, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, subtract operand B to accumulator,
																					 // store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs2{ -5, -7 }; // -5 - -7 = 2, subtracting negative numbers

	execute(memory2, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == 2);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory3{ 1009, 1010, 1011, 2009, 3110, 3111, 2112, 1112, 4300 }; // read operand A to 09, read operand B to 09, read operand C to 10, load operand A to accumulator,
																								 // subtract operand B from accumulator, subtract operand C from accumulator, store output to 12, writes output to 12, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs3{ -5, -7, 14 }; // -5 - -7 - 14 = -12, subtracting 3 numbers

	execute(memory3, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs3);

	CHECK(accumulator == -12);
	CHECK(instructionCounter == 8); // instructions range from 0 to 8
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode

}

TEST_CASE("Test read, write, divide, and halt operation")
{
	std::array<int, memorySize> memory{ 1007, 1008, 2007, 3208, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, divide accumulator by operand B,
																					// store output to 09, writes output to 09, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 12, 4 }; // 12 / 4 = 3, normal division

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 3);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1007, 1008, 2007, 3208, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, divide accumulator by operand B,
																					 // store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs2{ -8, -2 }; // -8 / -2 = 4, dividing negative numbers

	execute(memory2, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == 4);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory3{ 1009, 1010, 1011, 2009, 3210, 3211, 2112, 1112, 4300 }; // read operand A to 09, read operand B to 09, read operand C to 10, load operand A to accumulator,
																								 // divide accumulator by operand B, divide accumulator by operand C, store output to 12, writes output to 12, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs3{ 81, -3, 3 }; // 81 / -3 / 3 = -3, dividing 3 numbers

	execute(memory3, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs3);

	CHECK(accumulator == -9);
	CHECK(instructionCounter == 8); // instructions range from 0 to 8
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory4{ 1007, 1008, 2007, 3208, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, divide accumulator by operand B,
																					 // store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs4{ -8, 0 }; // -8 / 0 = undefined, dividing by 0, must throw exception

	CHECK_THROWS(execute(memory4, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs4));
}

TEST_CASE("Test read, write, multiply, and halt operation")
{
	std::array<int, memorySize> memory{ 1007, 1008, 2007, 3308, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, multiply accumulator by operand B, 
																					// store output to 09, writes output to 09, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 12, 4 }; // 12 * 4 = 48, normal multiplication

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 48);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1007, 1008, 2007, 3308, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, multiply accumulator by operand B,
																					 // store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs2{ -8, -2 }; // -8 * -2 = 16, multiply negative numbers

	execute(memory2, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == 16);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory3{ 1009, 1010, 1011, 2009, 3310, 3311, 2112, 1112, 4300 }; // read operand A to 09, read operand B to 09, read operand C to 10, load operand A to accumulator,
																								 // multiply accumulator by operand B, multiply accumulator by operand C, store output to 12, writes output to 12, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs3{ -4, -2, -1 }; // -4 * -2 * -1 = -8, multiplying 3 numbers

	execute(memory3, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs3);

	CHECK(accumulator == -8);
	CHECK(instructionCounter == 8); // instructions range from 0 to 8
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory4{ 1007, 1008, 2007, 3308, 2109, 1109, 4300 }; // read operand A to 07, read operand B to 08, load operand A to accumulator, multiply accumulator by operand B, store output to 09, writes output to 09, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs4{ -8, 0 }; // -8 * 0 = 0, multiplying by 0

	execute(memory4, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs4);

	CHECK(accumulator == 0);
	CHECK(instructionCounter == 6); // instructions range from 0 to 6
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode

}

TEST_CASE("Test read, write, add, branch, and halt operation")
{
	std::array<int, memorySize> memory{ 1008, 1009, 4011, 2008, 3009, 2110, 1110, 4300, 0000, 0000, 0000,
		 1018, 1019, 2018, 3019, 2120, 1119, 4300 }; // read operand A to 08, read operand B to 09, branch to 11 (which skips every operation between 04 and 011),
													 // read operand D to 18, read operand E to 19, load operand D to accumulator, add operand E to accumulator, store operand F at 19, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 19, 10, 4, 5 }; // 4 + 5 = 9, normal addition

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 9);
	CHECK(instructionCounter == 17); // instructions range from 0 to 17
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode

}

TEST_CASE("Test read, write, add, branchNeg, and halt operation")
{
	std::array<int, memorySize> memory{ 1008, 1009, 2008, 3009, 2110, 1110, 4111, 4300, 0000, 0000, 0000, 1018, 1019, 2018, 3019, 2120, 1120, 4300, 
		 1018, 1019, 2018, 3019, 2120, 1119, 4300 }; // read operand A to 08, read operand B to 09, load operand A to accumulator,
													 // add operand B to accumulator, store operand C to 10, write C to 10,
													 // branch to 11 (which skips the first halt), read operand D to 18, read operand E to 19,
													 // load operand D to accumulator, add operand E to accumulator, store operand F at 19, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 4, -10, 4, 5 }; // 4 + -10 = -6, adding a negative number, valid condition for branch negative
												   // 4 + 5 = 9, normal addition

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 9);
	CHECK(instructionCounter == 17); // instructions range from 0 to 17
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1008, 1009, 2008, 3009, 2110, 1110, 4111, 4300, 0000, 0000, 0000, 1018, 1019, 2018, 3019, 2120, 1120, 4300,
		 1018, 1019, 2018, 3019, 2120, 1119, 4300 }; // read operand A to 08, read operand B to 09, load operand A to accumulator,
													 // add operand B to accumulator, store operand C to 10, write C to 10,
													 // branch to 11 (which skips the first halt), read operand D to 18, read operand E to 19,
													 // load operand D to accumulator, add operand E to accumulator, store operand F at 19, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs2{ 4, 10, 4, 5 }; // 4 + 10 = 14, normal addition, invalid condition for branch negative

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == 14);
	CHECK(instructionCounter == 7); // instructions range from 0 to 7
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode


}

TEST_CASE("Test read, write, add, branchZero, and halt operation")
{
	std::array<int, memorySize> memory{ 1008, 1009, 2008, 3009, 2110, 1110, 4211, 4300, 0000, 0000, 0000, 1018, 1019, 2018, 3019, 2120, 1120, 4300,
		 1018, 1019, 2018, 3019, 2120, 1119, 4300 }; // read operand A to 08, read operand B to 09, load operand A to accumulator,
													 // add operand B to accumulator, store operand C to 10, write C to 10,
													 // branch to 11 (which skips the first halt), read operand D to 18, read operand E to 19,
													 // load operand D to accumulator, add operand E to accumulator, store operand F at 19, halt
	int accumulator{ 0 };
	size_t instructionCounter{ 0 };
	int instructionRegister{ 0 };
	size_t operationCode{ 0 };
	size_t operand{ 0 };

	const std::vector<int> inputs{ 4, -4, 4, 5 }; // 4 + -4 = 0, adding a negative number, valid condition for branch zero
												  // 4 + 5 = 9, normal addition

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs);

	CHECK(accumulator == 9);
	CHECK(instructionCounter == 17); // instructions range from 0 to 17
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode



	std::array<int, memorySize> memory2{ 1008, 1009, 2008, 3009, 2110, 1110, 4211, 4300, 0000, 0000, 0000, 1018, 1019, 2018, 3019, 2120, 1120, 4300,
		 1018, 1019, 2018, 3019, 2120, 1119, 4300 }; // read operand A to 08, read operand B to 09, load operand A to accumulator,
													 // add operand B to accumulator, store operand C to 10, write C to 10,
													 // branch to 11 (which skips the first halt), read operand D to 18, read operand E to 19,
													 // load operand D to accumulator, add operand E to accumulator, store operand F at 19, halt
	accumulator = 0, instructionRegister = 0, instructionCounter = 0, operationCode = 0, operand = 0;

	const std::vector<int> inputs2{ 4, 10, 4, 5 }; // 4 + 10 = 14, normal addition, invalid condition for branch zero

	execute(memory, &accumulator,
		&instructionCounter, &instructionRegister,
		&operationCode, &operand, inputs2);

	CHECK(accumulator == 14);
	CHECK(instructionCounter == 7); // instructions range from 0 to 7
	CHECK(instructionRegister == 4300); // last instruction which is halt
	CHECK(operand == 0); // halt operand
	CHECK(operationCode == 43); // halt opcode


}

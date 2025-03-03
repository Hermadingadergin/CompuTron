#include "computron.h"

#include <fstream>
#include <iomanip>

void load_from_file(std::array<int, memorySize>& memory, const std::string& filename)
{
	constexpr int sentinel{ -99999 };// terminates reading after -99999
	size_t i{ 0 };
	std::string line;
	int instruction;

	std::ifstream inputFile(filename);
    if (!inputFile)
        // throw runtime_error exception with string "invalid_input"
        throw std::runtime_error("invalid_input");

		while (std::getline(inputFile, line)) {
			instruction = std::stoi(line);
			if (instruction == sentinel)
				break;

			// Check if the instruction is valid using the validWord function
			// If the instruction is valid, store it in memory at position 'i' and increment 'i'
			// If the instruction is invalid, throw a runtime error with the message "invalid_input"

            if (validWord(instruction)) // if valid
            {
                memory[i] = instruction; // stores in memory at position 'i'
                i++; // increment 'i'
            }
            else // if invalid
            {
                throw std::runtime_error("invalid_input"); // throw a runtime error with the message "invalid_input"
            }

		}
	inputFile.close();
}

Command opCodeToCommand(size_t opCode) {
	switch (opCode) {
    case 10: return Command::read;
    case 11: return Command::write;
    case 20: return Command::load;
    case 21: return Command::store;
    case 30: return Command::add;
    case 31: return Command::subtract;
    case 32: return Command::divide;
    case 33: return Command::multiply;
    case 40: return Command::branch;
    case 41: return Command::branchNeg;
    case 42: return Command::branchZero;
    case 43: return Command::halt;
    default: return Command::halt;
	};
}

void execute(std::array<int, memorySize>& memory,
    int* const acPtr, size_t* const icPtr,
    int* const irPtr, size_t* const opCodePtr,
    size_t* const opPtr,
    const std::vector<int>& inputs) {

    size_t inputIndex{ 0 }; // Tracks input

    do {
        //instruction counter to register
        *irPtr = memory[*icPtr]; //instructionRegister = memory [instructionCounter];
        *opCodePtr = *irPtr / 100; //operationCode = instructionRegister / 100; // divide
        *opPtr = *irPtr % 100; //operand = instructionRegister % 100; // remainder

        switch (int word{}; opCodeToCommand(*opCodePtr)) {

        case Command::read:
            word = inputs[inputIndex];
            // Assign the value of 'word' to the memory location pointed to by 'opPtr'
            memory[*opPtr] = word;
            // Increment the instruction counter (icPtr) to point to the next instruction
            (*icPtr)++;

            inputIndex++;
            break;

        case Command::write:
            (*icPtr)++; //Dereference 'icPtr' to access the instruction counter and increment its value by 1
             // use the below cout if needed but comment before submission
            //std::cout << "Contents of " << std::setfill('0') << std::setw(2) 
            //          << *opPtr << " : " << memory[*opPtr] << "\n";
            
            break;

        case Command::load:
            *acPtr = memory[*opPtr]; //Load the value from the memory location pointed to by 'opPtr' into the accumulator (acPtr)
            (*icPtr)++; //Increment the instruction counter (icPtr) to point to the next instruction
            break;

        case Command::store:
            memory[*opPtr] = *acPtr; // Store the value in the accumulator (acPtr) into the memory location pointed to by 'opPtr'
            (*icPtr)++; // Increment the instruction counter (icPtr) to move to the next instruction
            break;

        case Command::add:
            word = *acPtr + memory[*opPtr]; // Add the value in the accumulator (acPtr) to the value in memory at the location pointed to by 'opPtr' and store the result in 'word'
            if (validWord(word)) // If the result is valid, store it in the accumulator and increment the instruction counter
            {
                *acPtr = word;
                (*icPtr)++;
            }
            else // / If the result is invalid, throw a runtime error 
            {
                throw std::runtime_error("invalid add result");
            }
            
            break;

        case Command::subtract:
            word = *acPtr - memory[*opPtr]; // Subtract the value in memory at the location pointed to by 'opPtr' from the value in the accumulator (acPtr) and store the result in 'word'
            if (validWord(word)) // If the result is valid, store it in the accumulator and increment the instruction counter
            {
                *acPtr = word;
                (*icPtr)++;
            }
            else // / If the result is invalid, throw a runtime error
            {
                throw std::runtime_error("invalid subtract result");
            }
            
            break;

        case Command::multiply:
            // as above do it for multiplication
            word = *acPtr * memory[*opPtr]; // Multiply the value in memory at the location pointed to by 'opPtr' by the value in the accumulator (acPtr) and store the result in 'word'
            if (validWord(word)) // If the result is valid, store it in the accumulator and increment the instruction counter
            {
                *acPtr = word;
                (*icPtr)++;
            }
            else // / If the result is invalid, throw a runtime error
            {
                throw std::runtime_error("invalid multiply result");
            }
            break;

        case Command::divide:
            // as above do it for division
            word = memory[*opPtr] / *acPtr; // Divide the value in memory at the location pointed to by 'opPtr' by the value in the accumulator (acPtr) and store the result in 'word'
            if (validWord(word)) // If the result is valid, store it in the accumulator and increment the instruction counter
            {
                *acPtr = word;
                (*icPtr)++;
            }
            else // / If the result is invalid, throw a runtime error
            {
                throw std::runtime_error("invalid multiply result");
            }
            break;

        case Command::branch:
            *icPtr = *opPtr;
            break;

        case Command::branchNeg:
            *acPtr < 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::branchZero:
            *acPtr == 0 ? *icPtr = *opPtr : ++(*icPtr);
            break;

        case Command::halt:
            break;

        default:
            // any instruction required
            break;
        };
        // You may modify the below while condition if required
    } while (opCodeToCommand(*opCodePtr) != Command::halt);
};

bool validWord(int word) {
    if (word < minWord || word > maxWord) //  checks to see if within the range of [minWord, maxWord]
    {
        return false;
    }
    else
    {
        return true;
    }
};

void dump(std::array<int, memorySize>& memory, int accumulator,
    size_t instructionCounter, size_t instructionRegister,
    size_t operationCode, size_t operand) {
    //Todo



    if (memory[instructionCounter] >= 0) // checking word in memory at instructionCounter
    {
        output(std::to_string((int)instructionRegister), (int)accumulator, (int)instructionCounter, true); // positive sign
    }
    else
    {
        output(std::to_string((int)instructionRegister), (int)accumulator, (int)instructionCounter, false); // negative sign
    }

    std::cout << "Memory:\n     0    1    2    3    4    5    6    7    8    9";

    for (size_t i = 0; i < 100; i++)
    {
        if (i % 10 == 0) // creating a new rows with the appropriate headers
        {
            if (i == 0)
            {
                std::cout << "\n " + std::to_string(i) + " "; // accounting for space before 0
            }
            else
            {
                std::cout << "\n" + std::to_string(i) + " ";
            }
            
        }
        if (memory[i] >= 0) // positive value stored in memory
        {
            std::cout << "+";
            if (std::to_string(memory[i]).size() < 4)
            {
                for (int j = 0; j < 4 - std::to_string(memory[i]).size(); j++) // zero filling if necessary
                {
                    std::cout << std::to_string(0);
                }
            }
            std::cout << std::to_string(memory[i]);
        }
        else // negative value stored in memory
        {
            std::cout << "-";
            if (std::to_string(memory[i]).size() < 5)
            {
                for (int j = 0; j < 5 - std::to_string(memory[i]).size(); j++) // zero filling if necessary
                {
                    std::cout << std::to_string(0);
                }
            }
            std::cout << std::to_string(-memory[i]);
        }



    }
    


};

void output(std::string label, int width, int value, bool sign)
{
    std::string result = "Registers\n";
    if (width >= 0) // positive accumulator
    {
        if (width / 10 == 0) // width of 1-9
        {
            result += ("accumulator          +000" + std::to_string(width) + "\n");
        }
        else
        {
            if (width >= 10 && width <= 99) // width of 10-99)
            {
                result += ("accumulator          +00" + std::to_string(width) + "\n");
            }
            else
            {
                if (width >= 100 && width <= 999) // width of 100-999
                {
                    result += ("accumulator          +0" + std::to_string(width) + "\n");
                }
                else
                {
                    if (width >= 1000 && width <= 9999) // width of 1000-9999
                    {
                        result += ("accumulator          +" + std::to_string(width) + "\n");
                    }
                }
            }
        }
    }
    else
    {
        if (width / 10 == 0) // width of negative 1-9
        {
            result += ("accumulator          -000" + std::to_string(-width) + "\n");
        }
        else
        {
            if (width >= 10 && width <= 99) // width of negative 10-99
            {
                result += ("accumulator          -00" + std::to_string(-width) + "\n");
            }
            else
            {
                if (width >= 100 && width <= 999) // width of negative 100-999
                {
                    result += ("accumulator          -0" + std::to_string(-width) + "\n");
                }
                else
                {
                    if (width >= 1000 && width <= 9999) // width of negative 1000-9999
                    {
                        result += ("accumulator          -" + std::to_string(-width) + "\n");
                    }
                }
            }
        }
    }

    if (value / 10 == 0) // if instructioncounter needs zero filling
    {
        result += "instructionCounter   " + std::to_string(0) + std::to_string(value) + "\n";
    }
    else
    {
        if (value >= 10 && value <= 99) // if instructioncounter does not need zero filling
        {
            result += "instructionCounter   " + std::to_string(value) + "\n";
        }
    }

    std::string plusorminus;
    if (sign)
    {
        plusorminus = "+";
    }
    else
    {
        plusorminus = "-";
    }
    result += "instructionRegister  " + plusorminus + label + "\n";
    result += "operationCode        " + label.substr(0, 2) + "\n";
    result += "operand              " + label.substr(2, 2) + "\n";
    std::cout << result;
};
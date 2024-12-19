

//In header files you need to define the methods, only declarations (prototypes)
#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <vector>

extern std::unordered_map<char, std::unordered_map<char, char> > ruleSet;

//fills the memory with random instructions
void initMemory(std::vector<std::string> &_memoryArr, int _memWidth , int _memHeight);

char applyRules(const char _baseColor, const char _tempColor);

char getNewInstruction(const char _ruleResult, int _sumResult);

char checkSymbolColor(const char _currColSym);

int getInstructionValue(const char _instruction);

char executeInstruction(const char _currColSym, const char _neighborSymbol);

char getNeighborSymbol(std::vector<std::string> &_memoryArr, const std::string _neighborPos, int _row, int _col);

//reads memory on current cell and apply rule to the _neighborPos position
void executeStep(std::vector<std::string> &_memoryArr, char &_currColSym, const std::string _neighborPos, int _currRow, int _currColumn, int &_totalNeighbors);

//starts the other methods to read memory and apply the rules
void getNewFrame(std::vector<std::string> &_memoryArr);

#endif
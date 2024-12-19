

//here we can define the methods that later wil be used in swpRender.cpp
#include <iostream>
#include <random>
#include <unordered_map>
#include "../include/codegenerator.h"


// let instructionSet = {
//   r: ["*", "+"],
//   g: ["#", "@"],
//   b: ["<", ">"],
//   e: [".", "."],
// };
//instructionsPool.length();  = 7
std::string instructionsPool = {"*+#@<>."};
std::string colorList = {"RGBE"};

//set random generator to pick instructions from the list
std::random_device rd;
std::mt19937 mt(rd());

//typecast to int , this is for the instructionsPool
std::uniform_real_distribution<double>randomInstructionIndex(0.0, (double)instructionsPool.length());
//----------------------

//typecast to int , this is for the colorList
std::uniform_real_distribution<double>randomColorIndex(0.0, (double)colorList.length());
//----------------------


std::unordered_map<char, std::unordered_map<char, char> > ruleSet;

char applyRules(const char _baseColor, const char _tempColor){

    char ruleResult;
    //does this rule already exists?
    if (ruleSet.find(_baseColor) != ruleSet.end()){

        if (ruleSet[_baseColor].find(_tempColor) != ruleSet[_baseColor].end()){
            //apply the current rule
            ruleResult = ruleSet[_baseColor][_tempColor];
            return ruleResult;
        }else{
            int newIndex = (int)randomColorIndex(mt);
            ruleResult = colorList[newIndex];
            ruleSet[_baseColor][_tempColor] = ruleResult;
            return ruleResult;
        }
        
    }else{
        //this is a new rule, add it to the list
        int newIndex = (int)randomColorIndex(mt);
        ruleResult = colorList[newIndex];

        std::unordered_map<char, char> temp;
        ruleSet[_baseColor] = temp;
        ruleSet[_baseColor][_tempColor] = ruleResult;

        return ruleResult;
    }
}


char getNewInstruction(const char _ruleResult, int _sumResult){

    char nInst;
    if(_ruleResult == 'R'){
        if(_sumResult == 0){
            nInst = '*';
        }else{
            nInst = '+';
        }
    }else if(_ruleResult == 'G'){
        if(_sumResult == 0){
            nInst = '#';
        }else{
            nInst = '@';
        }
    }else if(_ruleResult == 'B'){
        if(_sumResult == 0){
            nInst = '<';
        }else{
            nInst = '>';
        }
    }else if(_ruleResult == 'E'){
        nInst = '.';
    }

    return nInst;
}



char checkSymbolColor(const char _currColSym){
    
    char currSymColor = 'Q'; //no valid symbol by default

    if(_currColSym == '*' || _currColSym == '+' ){
        currSymColor = 'R';
    }else if(_currColSym == '#' || _currColSym == '@' ){
        currSymColor = 'G';
    }else if(_currColSym == '<' || _currColSym == '>' ){
        currSymColor = 'B';
    }else if(_currColSym == '.'){
        currSymColor = 'E';
    }

    return currSymColor;
}


int getInstructionValue(const char _instruction){
    
    int instValue = 0;

    if(_instruction == '*'){
        instValue = 0;
    }else if(_instruction == '+'){
        instValue = 1;
    }else if(_instruction == '#'){
        instValue = 0;
    }else if(_instruction == '@'){
        instValue = 1;
    }else if(_instruction == '<'){
        instValue = 0;
    }else if(_instruction == '>'){
        instValue = 1;
    }else if(_instruction == '.'){
        instValue = 0;
    }

    return instValue;
}


char executeInstruction(const char _currColSym, const char _neighborSymbol){
    //sum the values first
    int currColNum = getInstructionValue(_currColSym);
    int tempCellNum = getInstructionValue(_neighborSymbol);
    int sumResult = currColNum + tempCellNum;

    //only binary for now, so reset to zero if is equal to 2
    if (sumResult == 2) {
        sumResult = 0;
    }

    //identify the cells values to apply rule
    char currColColor = checkSymbolColor(_currColSym);
    char tempCellColor = checkSymbolColor(_neighborSymbol);
    char ruleResult = applyRules(currColColor, tempCellColor);


    char newInstruct = getNewInstruction(ruleResult,sumResult);
    return newInstruct;
}


char getNeighborSymbol(std::vector<std::string> &_memoryArr, const std::string _neighborPos, int _row, int _col){

    char tempCellSym;

    int tempRow = _row;
    int tempCol = _col;

    if(_neighborPos == "t1"){//top left --- [_row - 1][_col - 1]
        try
        {
            // get temp cell value (instruction symbol)
            if((_row - 1) < 0){
                tempRow = 0;
            }else{
                tempRow = _row -1;
            }

            if((_col - 1) < 0){
                tempCol = 0;
            }else{
                tempCol = _col -1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "t2"){//top middle --- [_row - 1][_col]
        try
        {
            if((_row - 1) < 0){
                tempRow = 0;
            }else{
                tempRow = _row - 1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "t3"){//top right --- [_row - 1][_col + 1]
        try
        {
            if((_row - 1) < 0){
                tempRow = 0;
            }else{
                tempRow = _row -1;
            }

            if((_col + 1) >= _memoryArr[0].length() ){
                tempCol = _col;
            }else{
                tempCol = _col + 1;
            }
            
            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "m1"){//middle left  [_row][_col - 1]
        try
        {
            if((_col - 1) < 0){
                tempCol = 0;
            }else{
                tempCol = _col -1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "m3"){//middle right  [_row][_col + 1]
        try
        {
            if((_col + 1) >= _memoryArr[0].length() ){
                tempCol = _col;
            }else{
                tempCol = _col + 1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "b1"){//bottom left [_row + 1][_col - 1]
        try
        {
            if((_row + 1) >= _memoryArr.size()){
                tempRow = _row;
            }else{
                tempRow = _row + 1;
            }

            if((_col - 1) < 0){
                tempCol = 0;
            }else{
                tempCol = _col -1;
            }
            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "b2"){//bottom middle [_row + 1][_col]
        try
        {
            if((_row + 1) >= _memoryArr.size()){
                tempRow = _row;
            }else{
                tempRow = _row + 1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }else if(_neighborPos == "b3"){//bottom right [_row + 1][_col + 1]
        try
        {
            if((_row + 1) >= _memoryArr.size()){
                tempRow = _row;
            }else{
                tempRow = _row + 1;
            }

            if((_col + 1) >= _memoryArr[0].length() ){
                tempCol = _col;
            }else{
                tempCol = _col + 1;
            }

            tempCellSym = _memoryArr[tempRow][tempCol];
            return tempCellSym;
        }
        catch(const std::exception& e)
        {
            return 'Q';
        }
    }
}


void executeStep(std::vector<std::string> &_memoryArr, char &_currColSym, const std::string _neighborPos, int _currRow, int _currColumn, int &_totalNeighbors){


    char neighborSymbol = getNeighborSymbol(_memoryArr, _neighborPos, _currRow, _currColumn);

    if(neighborSymbol != 'Q'){

        //check curr symbol color
        char currSymColor = checkSymbolColor(_currColSym);

        // std::cout << "QQQ executeStep currSymColor  " << currSymColor << '\n';

        //check neighbor Symbol color
        char neighborSymColor = checkSymbolColor(neighborSymbol);

        /*
            the opposite colors definition will be:

            R and B (or B and R)
            G will be opposite of R or B
            E will always add +1 to the count
        */
        if(currSymColor == 'R'){
            if(neighborSymColor == 'B' || neighborSymColor == 'E'){
                _totalNeighbors+=1;
            }
        }else if(currSymColor == 'G'){
            if(neighborSymColor == 'B' || neighborSymColor == 'R' || neighborSymColor == 'E'){
                _totalNeighbors+=1;
            }
        }else if(currSymColor == 'B'){
            if(neighborSymColor == 'R' || neighborSymColor == 'E'){
                _totalNeighbors+=1;
            }
        }else if(currSymColor == 'E' && neighborSymColor == 'E'){
            _totalNeighbors+=1;
        }

        int rowNum = _currRow;
        int colNum = _currColumn;

        char newInstruction = executeInstruction(_currColSym, neighborSymbol);


        if(_neighborPos == "t1"){

            if((_currRow - 1) < 0){
                rowNum = 0;
            }else{
                rowNum = _currRow -1;
            }

            if((_currColumn - 1) < 0){
                colNum = 0;
            }else{
                colNum = _currColumn -1;
            }
        }else if(_neighborPos == "t2"){
            
            if((_currRow - 1) < 0){
                rowNum = 0;
            }else{
                rowNum = _currRow - 1;
            }

            colNum = _currColumn;
        }else if(_neighborPos == "t3"){
            
            if((_currRow - 1) < 0){
                rowNum = 0;
            }else{
                rowNum = _currRow - 1;
            }

            if((_currColumn + 1) >= _memoryArr[0].length() ){
                colNum = _currColumn;
            }else{
                colNum = _currColumn + 1;
            }

        }else if(_neighborPos == "m1"){
            
            if((_currColumn - 1) < 0){
                colNum = 0;
            }else{
                colNum = _currColumn -1;
            }

            rowNum = _currRow;
        }else if(_neighborPos == "m3"){
            
            if((_currColumn + 1) >= _memoryArr[0].length() ){
                colNum = _currColumn;
            }else{
                colNum = _currColumn + 1;
            }

            rowNum = _currRow;

        }else if(_neighborPos == "b1"){
            
            if((_currRow + 1) >= _memoryArr.size()){
                rowNum = _currRow;
            }else{
                rowNum = _currRow + 1;
            }

            if((_currColumn - 1) < 0){
                colNum = 0;
            }else{
                colNum = _currColumn -1;
            }
            
        }else if(_neighborPos == "b2"){
            
            if((_currRow + 1) >= _memoryArr.size()){
                rowNum = _currRow;
            }else{
                rowNum = _currRow + 1;
            }

            colNum = _currColumn;

        }else if(_neighborPos == "b3"){

            if((_currRow + 1) >= _memoryArr.size()){
                rowNum = _currRow;
            }else{
                rowNum = _currRow + 1;
            }

            if((_currColumn + 1) >= _memoryArr[0].length() ){
                colNum = _currColumn;
            }else{
                colNum = _currColumn + 1;
            }

        }

        //replace neighbor cell symbol
        _memoryArr[rowNum][colNum] = newInstruction;
    }
};
//-----------------------------------------
//-----------------------------------------
void getNewFrame(std::vector<std::string> &_memoryArr){

    // loop the memory and execute the program
    //curr symbol is assumed to be the center of a 3x3 grid
    // * * *
    // * C *
    // * * *
    //for the piece of the center, count how many
    //of the opposite color are around it
    // and use that as index for colorPool
    int totalNeighbors = 0;
    const int memWidth = _memoryArr[0].length();
    const int memHeight = _memoryArr.size();
    int loopStop = memWidth * memHeight;


    for (int i = 0; i < loopStop; i++)
    {   
        int currRow = (int)(i / memWidth); // determines row
        int currColumn = i % memWidth; // determines column

        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "t1", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "t2", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "t3", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "m1", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "m3", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "b1", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "b2", currRow, currColumn, totalNeighbors);
        executeStep(_memoryArr, _memoryArr[currRow][currColumn], "b3", currRow, currColumn, totalNeighbors);

        
        //this is for the center, after counting all neighbors
        if(totalNeighbors >= instructionsPool.length()){
            totalNeighbors = (int)randomInstructionIndex(mt);
            _memoryArr[currRow][currColumn] = instructionsPool[totalNeighbors];
        }else{
            _memoryArr[currRow][currColumn] = instructionsPool[totalNeighbors];
        }
        totalNeighbors = 0;
    }
};

//-----------------------------------------
//-----------------------------------------
//fills the memory with random instructions
void initMemory(std::vector<std::string> &_memoryArr, int _memWidth , int _memHeight){

    for (int i = 0; i < _memHeight; i++)
    {
        for (int j = 0; j < _memWidth; j++)
        {
            int newInstructionPtr = (int)randomInstructionIndex(mt);
            char newInstruction = instructionsPool[newInstructionPtr];
            // std::cout << newInstruction;
            if(j == 0){
                std::string newRow;
                _memoryArr.insert(_memoryArr.end(), newRow);
                _memoryArr[i]+= newInstruction;
            }else{
                _memoryArr[i]+= newInstruction;
            }
        }
    }
};
//-----------------------------------------
//-----------------------------------------
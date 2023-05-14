#include "model.h"

Model::Model(std::string fileName)
{
    setFileName(fileName);
}

int Model::isNum(char c) { return c >= '0' && c <= '9'; }

void Model::parser()
{
    if (errorCode != FILE_HAS_WRONG_EXTENSION)
    {
        std::ifstream file(fileName);
        std::string line;

        if (!file.is_open())
        {
            errorCode = FAILED_TO_OPEN_FILE;
            return;
        }

        while (errorCode == 0 && std::getline(file, line))
        {
            if (!line.compare(0, 2, "v "))
            {
                vertexParser(line);
            }
            else if (!line.compare(0, 2, "f "))
            {
                edgesParser(line);
            }
        }
        file.close();
    }
}

void Model::vertexParser(std::string line)
{
    size_t numPos = 0, dotPos = 0;
    double coord = 0;
    double coord_temp[3]{};
    int coord_num = 0;

    for (size_t i = 2; i < line.size() && coord_num != 3; ++i)
    {
        while (isNum(line[i]) || line[i] == '.')
        {
            if (numPos == 0) numPos = i;
            if (line[i] == '.')
            {
                dotPos = i;
            }
            else
            {
                coord = coord * 10 + (line[i++] - '0');
            }
        }
        if (numPos != 0)
        {
            if (dotPos != 0) dotPos = i - dotPos - 1;
            coord = coord / pow(10, dotPos);
            if (line[numPos - 1] == '-') coord = -coord;
            coord_temp[coord_num++] = coord;
        }
        if (coord_num == 3)
        {
            vertexCoord.insert(vertexCoord.end(), coord_temp, coord_temp + 3);
        }
        coord = 0;
        numPos = 0;
        dotPos = 0;
    }
}

void Model::edgesParser(std::string line)
{
    long countIndex_temp = countIndex;
    long firstIndex = 0, tempIndex = 0;
    int checkOrder = 0, checkSpace;
    bool checkNum = false;

    for (size_t i = 2; i < line.size(); ++i)
    {
        checkSpace = line[i - 1];
        while (isNum(line[i]) && checkSpace == ' ')
        {
            checkNum = true;
            tempIndex = tempIndex * 10 + (line[i++] - '0');
        }
        if (checkNum != false)
        {
            ++checkOrder;
            vertexIndex[++countIndex_temp - 1] = --tempIndex;
            if (checkOrder == 1)
            {
                firstIndex = tempIndex;
            }
            else
            {
                vertexIndex[++countIndex_temp - 1] = tempIndex;
            }
            tempIndex = 0;
            checkNum = false;
        }
    }
    ++countIndex_temp;
    vertexIndex[countIndex_temp - 1] = firstIndex;
    countIndex = countIndex_temp;
}

void Model::setFileName(std::string fileName)
{
    if (fileName.size() <= 3 || fileName.compare(fileName.size() - 4, 4, ".obj")) 
    {
        errorCode = FILE_HAS_WRONG_EXTENSION;
    } 
    else 
    {
        this->fileName = fileName;
    }
}

int Model::getError()
{
    return errorCode;
}

long Model::getCountVertex()
{
    return countVertex;
}

long Model::getCountIndex()
{
    return countIndex;
}

std::vector<int> Model::getVertexIndex()
{
    return vertexIndex;
}

std::vector<double> Model::getVertexCoord()
{
    return vertexCoord;
}

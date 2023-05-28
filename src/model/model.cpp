#include "model.h"

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
                edgesParser(std::string(line.begin() + 2, line.end()));
            }
        }
        file.close();
    }
}

void Model::vertexParser(std::string line)
{
    double d1 = 0, d2 = 0, d3 = 0;
    char j = 0;

    if (sscanf(line.c_str(), "%c %lf %lf %lf %c", &j, &d1, &d2, &d3, &j) == 4)
    {
        vertexCoord.insert(vertexCoord.end(), {d1, d2, d3});
    }
    else
    {
        errorCode = INCORRECT_ENTRY_OF_THE_VERTEX_COORDINATE;
    }
}

void Model::edgesParser(std::string line)
{
    std::istringstream iss(line);
    std::string token;
    int first = 0, firstIndex = 0;
    int index = 0;

    while (std::getline(iss, token, ' '))
    {
        sscanf(token.c_str(), "%d", &index);

        if (index <= 0 || token.find('\r') != std::string::npos) continue;
        --index;

        if (first == 0)
        {
            vertexIndex.push_back(index);
            firstIndex = index;
            first = 1;
        }
        else
        {
            vertexIndex.insert(vertexIndex.end(), {index, index});
        }
    }
    vertexIndex.push_back(firstIndex);
}

void Model::setFileName(std::string fileName)
{
    if (fileName.size() <= 3 || fileName.compare(fileName.size() - 4, 4, ".obj")) 
    {
        errorCode = FILE_HAS_WRONG_EXTENSION;
    } 
    else 
    {
        vertexCoord.clear();
        vertexIndex.clear();
        errorCode = 0;
        this->fileName = fileName;
    }
}

int Model::getError()
{
    return errorCode;
}

std::vector<int>& Model::getVertexIndex()
{
    return vertexIndex;
}

std::vector<double>& Model::getVertexCoord()
{
    return vertexCoord;
}

void Model::transform(int& strategyType, double& value, transformation_t& axis)
{
    if (strategyType == MOVE)
    {
        transformationModel.setStrategy(new MoveStrategy());
    }
    else if (strategyType == ROTATE)
    {
        transformationModel.setStrategy(new RotateStrategy());
    }
    else if (strategyType == SCALE)
    {
        transformationModel.setStrategy(new ScaleStrategy());
    }
    transformationModel.performTransformation(vertexCoord, value, axis);
}

typename Model::Model& Model::getInstance()
{
    static Model instance;
    return instance;
}

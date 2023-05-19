#include <vector>
#include <cmath>

#define X 0
#define Y 1
#define Z 2

#define MOVE 0
#define ROTATE 1
#define SCALE 2

class TransformationStrategy
{
public:
    virtual ~TransformationStrategy() {}
    virtual void transform(std::vector<double>&, double&, int& axis) {}
};

class MoveStrategy : public TransformationStrategy
{
    void transform(std::vector<double>& vertexCoord, double& step, int& axis) override
    {
        for (int i = axis; i < vertexCoord.size(); i += 3)
        {
            vertexCoord[i] += step;
        }
    }
};

class RotateStrategy : public TransformationStrategy 
{
    void transform(std::vector<double>& vertexCoord, double& angle, int& axis) override
    {
        double tempAngle = angle * M_PI / 180;
        double cosValue = cos(tempAngle);
        double sinValue = sin(tempAngle);

        for (int i = (axis == X) ? 1 : 0; i < vertexCoord.size(); i += 3)
        {
            double coord = vertexCoord[i];

            if (axis == X) 
            {
                vertexCoord[i] = cosValue * coord - sinValue * vertexCoord[i + 1];
                vertexCoord[i + 1] = sinValue * coord + cosValue * vertexCoord[i + 1];
            } 
            else if (axis == Y) 
            {
                vertexCoord[i] = cosValue * coord + sinValue * vertexCoord[i + 2];
                vertexCoord[i + 2] = -sinValue * coord + cosValue * vertexCoord[i + 2];
            } 
            else if (axis == Z) 
            {
                // vertexCoord[i] = cosValue * coord - sinValue * vertexCoord[i + 1];
                // vertexCoord[i + 1] = sinValue * coord + cosValue * vertexCoord[i + 1];
                vertexCoord[i] = cosValue * coord + sinValue * vertexCoord[i + 1];
                vertexCoord[i + 1] = -sinValue * coord + cosValue * vertexCoord[i + 1];
            }
        }
    }
};

class ScaleStrategy : public TransformationStrategy
{
    void transform(std::vector<double>& vertexCoord, double& scale, int&) override
    {
        for (int i = 0; i < vertexCoord.size(); ++i)
        {
            vertexCoord[i] += scale / 100 * vertexCoord[i];
        }
    }
};

class Strategy
{
public:
    Strategy() : strategy(nullptr) {}

    void setStrategy(TransformationStrategy* strategy)
    {
        this->strategy = strategy;
    }

    void performTransformation(std::vector<double>& vertexCoord, double& value, int& axis)
    {
        strategy->transform(vertexCoord, value, axis);
        delete strategy;
    }
private:
    TransformationStrategy* strategy;
};

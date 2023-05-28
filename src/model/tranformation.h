#ifndef CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_
#define CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_

#include <vector>
#include <cmath>

typedef enum 
{
    X = 0,
    Y = 1,
    Z = 2,
    MOVE = 0,
    ROTATE = 1,
    SCALE = 2
} transformation_t;

class TransformationStrategy
{
public:
    virtual ~TransformationStrategy() {}
    virtual void transform(std::vector<double>&, double&, transformation_t& axis) {}
};

class MoveStrategy : public TransformationStrategy
{
    void transform(std::vector<double>& vertexCoord, double& step, transformation_t& axis) override
    {
        for (int i = axis; i < vertexCoord.size(); i += 3)
        {
            vertexCoord[i] += step;
        }
    }
};

class RotateStrategy : public TransformationStrategy 
{
    void transform(std::vector<double>& vertexCoord, double& angle, transformation_t& axis) override
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
                vertexCoord[i] = cosValue * coord + sinValue * vertexCoord[i + 1];
                vertexCoord[i + 1] = -sinValue * coord + cosValue * vertexCoord[i + 1];
            }
        }
    }
};

class ScaleStrategy : public TransformationStrategy
{
    void transform(std::vector<double>& vertexCoord, double& scale, transformation_t&) override
    {
        for (int i = 0; i < vertexCoord.size(); ++i)
        {
            // vertexCoord[i] += scale / 100 * vertexCoord[i];
            vertexCoord[i] *= scale;
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

    void performTransformation(std::vector<double>& vertexCoord, double& value, transformation_t& axis)
    {
        strategy->transform(vertexCoord, value, axis);
        delete strategy;
    }
private:
    TransformationStrategy* strategy;
};

#endif  // CPP4_3DVIEWER_V2_0_MODEL_TRANSFORMATION_H_

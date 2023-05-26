#include "test_core.h"

using namespace std;

TEST(MODEL, CORRECT_FILE)
{
    Model model("/home/lunarskii/project/3DViewer_v2.0/src/tests/one_million.obj");
    model.parser();
    
    cout << "countVertex = " << model.getCountVertex() << endl;
    // cout << "vertexCoord = ";
    // std::vector<double> temp1 = model.getVertexCoord();
    // double* vertexCoord = temp1.data();
    // for (int i = 0; i < model.getCountVertex() * 3; ++i)
    // {
    //     cout << vertexCoord[i] << " ";
    // }
    cout << endl;
    cout << "countIndex = " << model.getCountIndex() << endl;
    // cout << "vertexIndex = ";
    // std::vector<int> temp2 = model.getVertexIndex();
    // int* vertexIndex = temp2.data();
    // for (int i = 0; i < model.getCountIndex(); ++i)
    // {
    //     cout << vertexIndex[i] << " ";
    // }
    // cout << endl;

    ASSERT_EQ(model.getError(), 0);
}

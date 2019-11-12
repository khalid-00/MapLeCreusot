#ifndef TESTCLASS_H
#define TESTCLASS_H
#include "model.h"


class testClass
{


    friend class Model;
    Model* m_model;



public:
    testClass(Model* model)
    {
        m_model = model;
    }
};


#endif // TESTCLASS_H

#include "DataBase.h"

class DataBase : public IDataBase
{
public:

    // IDataBase
private:

    void Connect() override
    {

    }
};

std::unique_ptr<IDataBase> MakeDataBase()
{
    return std::make_unique<DataBase>();
}

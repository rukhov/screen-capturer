#ifndef DATABASE_H
#define DATABASE_H

#include <memory>

class IDataBase
{
public:
    virtual ~IDataBase() = default;

    virtual void Connect() = 0;
};

std::unique_ptr<IDataBase> MakeDataBase();

#endif // DATABASE_H

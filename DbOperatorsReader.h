#ifndef DBOPERATORSREADER_H
#define DBOPERATORSREADER_H

#include "IOperatorsReader.h"
#include <QSqlDatabase>

//Класс вычитки данных операторов из БД
class DbOperatorsReader : public IOperatorsReader
{
public:
    ~DbOperatorsReader() override;

    bool init() override;
    OperatorsTreeNode* readOperators() override;

private:
    QSqlDatabase m_db;
};

#endif // DBOPERATORSREADER_H

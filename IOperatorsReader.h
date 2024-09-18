#ifndef IOPERATORSREADER_H
#define IOPERATORSREADER_H

class OperatorsTreeNode;

//Абстрактный класс вычитки данных операторов из хранилища
class IOperatorsReader
{
public:
    virtual ~IOperatorsReader() = default;
    virtual bool init() = 0;
    virtual OperatorsTreeNode* readOperators() = 0;
};

#endif // IOPERATORSREADER_H

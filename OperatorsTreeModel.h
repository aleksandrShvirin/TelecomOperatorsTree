#ifndef OPERATORSTREEMODEL_H
#define OPERATORSTREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>

class OperatorsTreeNode;
class IOperatorsReader;

//Модель данных по операторам
class OperatorsTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    OperatorsTreeModel(IOperatorsReader& operatorsReader, QObject* parent = nullptr);

    ~OperatorsTreeModel();

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;;

private:
    OperatorsTreeNode* m_rootItem;
    IOperatorsReader& m_operatorsReader;
};


#endif // OPERATORSTREEMODEL_H

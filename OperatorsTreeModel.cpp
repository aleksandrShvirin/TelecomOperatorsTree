#include "OperatorsTreeModel.h"
#include "OperatorsTreeNode.h"
#include "IOperatorsReader.h"

OperatorsTreeModel::OperatorsTreeModel(IOperatorsReader& operatorsReader, QObject* parent) : QAbstractItemModel(parent), m_operatorsReader(operatorsReader)
{
    m_rootItem = operatorsReader.readOperators();
}

OperatorsTreeModel::~OperatorsTreeModel()
{
    delete m_rootItem;
}

QModelIndex OperatorsTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    OperatorsTreeNode* parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<OperatorsTreeNode*>(parent.internalPointer());

    OperatorsTreeNode* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex OperatorsTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    OperatorsTreeNode* childItem = static_cast<OperatorsTreeNode*>(index.internalPointer());
    OperatorsTreeNode* parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int OperatorsTreeModel::rowCount(const QModelIndex& parent) const
{
    OperatorsTreeNode* parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<OperatorsTreeNode*>(parent.internalPointer());

    return parentItem->childCount();
}

int OperatorsTreeModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}

QVariant OperatorsTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    OperatorsTreeNode* item = static_cast<OperatorsTreeNode*>(index.internalPointer());

    if (role == Qt::DisplayRole)
    {
        return item->text();
    }
    else if (role == Qt::DecorationRole)
    {
        return item->icon();
    }

    return QVariant();
}

Qt::ItemFlags OperatorsTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

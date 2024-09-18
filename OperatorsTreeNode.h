#ifndef OPERATORSTREENODE_H
#define OPERATORSTREENODE_H

#include <QIcon>

// Класс для представления узла древовидной структуры
class OperatorsTreeNode
{
public:
    OperatorsTreeNode(const QString& text, const QIcon& icon, OperatorsTreeNode* parent = nullptr);
    ~OperatorsTreeNode();

    void appendChild(OperatorsTreeNode* child);
    OperatorsTreeNode* child(int row);
    int childCount() const;
    int row() const;
    OperatorsTreeNode* parent();
    QString text() const;
    QIcon icon() const;

private:
    QString m_text;
    QIcon m_icon;
    OperatorsTreeNode* m_parent;
    QList<OperatorsTreeNode*> m_children;
};

#endif // OPERATORSTREENODE_H

#include "OperatorsTreeNode.h"

OperatorsTreeNode::OperatorsTreeNode(const QString& text, const QIcon& icon, OperatorsTreeNode* parent)
    : m_text(text), m_icon(icon), m_parent(parent) {}

OperatorsTreeNode::~OperatorsTreeNode()
{
    qDeleteAll(m_children);
}

void OperatorsTreeNode::appendChild(OperatorsTreeNode* child)
{
    m_children.append(child);
}

OperatorsTreeNode* OperatorsTreeNode::child(int row)
{
    return m_children.value(row);
}

int OperatorsTreeNode::childCount() const
{
    return m_children.count();
}

int OperatorsTreeNode::row() const
{
    if (m_parent)
        return m_parent->m_children.indexOf(const_cast<OperatorsTreeNode*>(this));
    return 0;
}

OperatorsTreeNode* OperatorsTreeNode::parent()
{
    return m_parent;
}

QString OperatorsTreeNode::text() const
{
    return m_text;
}

QIcon OperatorsTreeNode::icon() const
{
    return m_icon;
}

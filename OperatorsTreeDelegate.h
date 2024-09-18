#ifndef OPERATORSTREEDELEGATE_H
#define OPERATORSTREEDELEGATE_H

#include <QStyledItemDelegate>
#include <QAbstractItemView>
#include <QPainter>
#include <QScreen>

//Делегат отображения элементов текста и иконки
class OperatorsTreeDelegate : public QStyledItemDelegate
{
public:
    OperatorsTreeDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // OPERATORSTREEDELEGATE_H

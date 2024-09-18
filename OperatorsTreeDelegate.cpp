#include "OperatorsTreeDelegate.h"

OperatorsTreeDelegate::OperatorsTreeDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

void OperatorsTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);

    QFont font = opt.font;
    font.setPointSize(14);
    if(index.parent().isValid() == false)
        font.setBold(true);

    opt.font = font;

    QStyledItemDelegate::paint(painter, opt, index);
}

QSize OperatorsTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemView *itemView = qobject_cast<const QAbstractItemView *>(option.widget);

    if (itemView) {
        QSize itemSize = itemView->size();

        int itemHeight = itemSize.height() * 0.05;
        int itemWidth = itemSize.width();

        return QSize(itemWidth, itemHeight);
    }

    return QStyledItemDelegate::sizeHint(option, index);
}

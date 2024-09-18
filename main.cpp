#include "OperatorsTreeModel.h"
#include "DbOperatorsReader.h"
#include "OperatorsTreeDelegate.h"

#include <QApplication>
#include <QTreeView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Инициализация работы с базой данных, заполнение модели
    DbOperatorsReader operatorsReader;
    operatorsReader.init();
    OperatorsTreeModel model(operatorsReader);

    QTreeView treeView;
    treeView.setModel(&model);
    OperatorsTreeDelegate* delegate = new OperatorsTreeDelegate(&treeView);

    //Скромная настройка стиля
    treeView.setStyleSheet(
        "QTreeView::item {"
        "   border-bottom: 1px solid lightgray;"
        "}"
        "QTreeView::item:selected {"
        "   background-color: lightblue;"
        "   color: black;"
        "}"
        "QTreeView::item:!selected {"
        "   background-color: transparent;"
        "}");

    treeView.setItemDelegate(delegate);

    //Размерность виджета
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();

    int treeWidth = screenGeometry.width() * 0.3;
    int treeHeight = screenGeometry.height() * 0.6;
    treeView.resize(treeWidth, treeHeight);

    int columnCount = treeView.model()->columnCount();
    for(int column = 0; column != columnCount; ++column)
        treeView.setColumnWidth(column, treeWidth / columnCount);

    treeView.setHeaderHidden(true);
    treeView.show();

    return a.exec();
}

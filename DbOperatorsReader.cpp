#include "DbOperatorsReader.h"
#include "OperatorsTreeNode.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDir>

DbOperatorsReader::~DbOperatorsReader()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DbOperatorsReader::init()
{
    QString dbPath = QCoreApplication::applicationDirPath() + QDir::separator() + "OM_system.db";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "Failed to open the database:" << m_db.lastError().text();
        return false;
    }
    else
        qDebug() << "The database has been successfully opened";


    return true;
}

OperatorsTreeNode* DbOperatorsReader::readOperators()
{
    OperatorsTreeNode* rootNode = new OperatorsTreeNode("Root", QIcon());

    QSqlQuery readOperatorsQuery(m_db);

    readOperatorsQuery.prepare(" SELECT operators.mcc as mcc"
                               " , operators.mnc as mnc"
                               " , operators.name as operators_name "
                               " , countries.name as countries_name "
                               " , countries.code as code "
                               " FROM [operators] as operators"
                               " INNER JOIN [countries] AS countries ON countries.mcc = operators.mcc "
                               " ORDER BY operators.mcc ");


    if(!readOperatorsQuery.exec())
    {
        qDebug() << "Select operators failed:" << readOperatorsQuery.lastError().text();
        return rootNode;
    }

    //Упрощенное заполнение дерева с сортировкой по mcc
    int lastMcc = -1;
    OperatorsTreeNode* countyNode = nullptr;

    while(readOperatorsQuery.next())
    {
        int mcc = readOperatorsQuery.record().value("mcc").toInt();//хоть и в БД TEXT
        int mnc = readOperatorsQuery.record().value("mnc").toInt();//хоть и в БД TEXT
        QString operatorsName = readOperatorsQuery.record().value("operators_name").toString();
        QString countriesName = readOperatorsQuery.record().value("countries_name").toString();
        QString countriesCode = readOperatorsQuery.record().value("code").toString();

        if(lastMcc != mcc)
        {
            if(countyNode != nullptr)
                rootNode->appendChild(countyNode);

            QString countyIconPath = QString(":countries/Countries/%1.png").arg(countriesCode);
            countriesName = countriesName + QString(" (%1)").arg(countriesCode);

            countyNode = new OperatorsTreeNode(countriesName, QIcon(countyIconPath), rootNode);
            lastMcc = mcc;
        }

        operatorsName = operatorsName + QString(" (%1-%2)").arg(mcc).arg(mnc);
        QString operatorIconPath = QString(":operators/Operators/%1_%2.png").arg(mcc).arg(mnc);
        OperatorsTreeNode* operatorNode = new OperatorsTreeNode(operatorsName, QIcon(operatorIconPath), countyNode);
        countyNode->appendChild(operatorNode);
    }

    return rootNode;
}

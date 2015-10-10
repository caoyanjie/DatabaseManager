#include "widget.h"
#include <QDebug>

#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QSqlQuery>
#include <QScrollArea>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,initSize(980, 670)
{
    this->resize(initSize);

    //标题
    lab_title = new QLabel("数据库管理", this);

    layout_Title = new QHBoxLayout;
    layout_Title->addStretch();
    layout_Title->addWidget(lab_title);
    layout_Title->addStretch();

    //创建数据库
    ln_databaseName = new QLineEdit(this);
    ln_databaseUsername = new QLineEdit(this);
    ln_databasePassword = new QLineEdit(this);
    ln_databasePath = new QLineEdit(this);
    pbn_choosePath = new QPushButton("浏览", this);
    pbn_createDatabase = new QPushButton("创建数据库", this);

    ln_databaseName->setPlaceholderText("数据库名称");
    ln_databaseUsername->setPlaceholderText("访问数据库的用户名");
    ln_databasePassword->setPlaceholderText("访问密码");
    ln_databasePath->setPlaceholderText("创建路径");

    ln_databasePath->setFixedWidth(180);
    pbn_choosePath->setFixedWidth(35);

    layout_form_c = new QHBoxLayout;
    layout_form_c->addWidget(ln_databasePath);
    layout_form_c->addWidget(pbn_choosePath);
    layout_form_c->setSpacing(0);
    layout_form_c->setMargin(0);

    layout_createDatabase = new QHBoxLayout;
    layout_createDatabase->addLayout(layout_form_c);
    layout_createDatabase->addWidget(ln_databaseName);
    layout_createDatabase->addWidget(ln_databaseUsername);
    layout_createDatabase->addWidget(ln_databasePassword);
    layout_createDatabase->addWidget(pbn_createDatabase);

    connect(ln_databasePath, SIGNAL(textChanged(QString)),
            this, SLOT(ln_databasePath_textChanged(QString)));

    //添加表
    ln_chooseDatabase_addTable = new QLineEdit(this);
    pbn_chooseDatabase_addTable = new QPushButton("浏览", this);
    ln_databaseUsername_addTable = new QLineEdit(this);
    ln_databasePassword_addTable = new QLineEdit(this);
    ln_tableName_addTable = new QLineEdit(this);
    ln_ziduan = new QLineEdit(this);
    pbn_addTable = new QPushButton("添加表", this);

    ln_chooseDatabase_addTable->setPlaceholderText("选择数据库...");
    ln_databaseUsername_addTable->setPlaceholderText("访问数据库的用户名");
    ln_databasePassword_addTable->setPlaceholderText("访问密码");
    ln_tableName_addTable->setPlaceholderText("表名");
    ln_ziduan->setPlaceholderText("字段");

    ln_chooseDatabase_addTable->setFixedWidth(180);
    pbn_chooseDatabase_addTable->setFixedWidth(35);

    connect(ln_chooseDatabase_addTable, SIGNAL(textChanged(QString)),
            this, SLOT(ln_chooseDatabase_addTable_textChanged(QString)));

    layout_form_addTable = new QHBoxLayout;
    layout_form_addTable->addWidget(ln_chooseDatabase_addTable);
    layout_form_addTable->addWidget(pbn_chooseDatabase_addTable);
    layout_form_addTable->setSpacing(0);
    layout_form_addTable->setMargin(0);

    layout_addTable = new QHBoxLayout;
    layout_addTable->addLayout(layout_form_addTable);
    layout_addTable->addWidget(ln_databaseUsername_addTable);
    layout_addTable->addWidget(ln_databasePassword_addTable);
    layout_addTable->addWidget(ln_tableName_addTable);
    layout_addTable->addWidget(ln_ziduan);
    layout_addTable->addWidget(pbn_addTable);

    //显示表
    ln_chooseDatabase_showTable = new QLineEdit;
    pbn_chooseDatabase_showTable = new QPushButton("浏览");
    ln_databaseUsername_showTable = new QLineEdit;
    ln_databasePassword_showTable = new QLineEdit;
    pbn_showTables = new QPushButton("显示表");
    ln_chooseDatabase_showTable->setFixedWidth(180);
    pbn_chooseDatabase_showTable->setFixedWidth(35);
    ln_chooseDatabase_showTable->setPlaceholderText("选择数据库");
    ln_databaseUsername_showTable->setPlaceholderText("访问数据库的用户名");
    ln_databasePassword_showTable->setPlaceholderText("访问密码");

    layout_form_showTable = new QHBoxLayout;
    layout_form_showTable->addWidget(ln_chooseDatabase_showTable);
    layout_form_showTable->addWidget(pbn_chooseDatabase_showTable);
    layout_form_showTable->setSpacing(0);
    layout_form_showTable->setMargin(0);
    layout_showTables = new QHBoxLayout;
    layout_showTables->addLayout(layout_form_showTable);
    layout_showTables->addWidget(ln_databaseUsername_showTable);
    layout_showTables->addWidget(ln_databasePassword_showTable);
    layout_showTables->addWidget(pbn_showTables);

    connect(ln_chooseDatabase_showTable, SIGNAL(textChanged(QString)),
            this, SLOT(ln_chooseDatabase_showTable_textChanged(QString)));

    //添加数据
    ln_chooseDatabase_addDate = new QLineEdit(this);
    pbn_chooseDatabase_addDate = new QPushButton("浏览", this);
    ln_chooseTable_addDate = new QLineEdit(this);
    ln_addDate = new QLineEdit(this);
    pbn_addDate = new QPushButton("添加数据", this);
    ln_chooseDatabase_addDate->setPlaceholderText("选择数据库");
    ln_chooseTable_addDate->setPlaceholderText("选择表");
    ln_addDate->setPlaceholderText("添加的数据");
    ln_chooseDatabase_addDate->setFixedWidth(180);
    pbn_chooseDatabase_addDate->setFixedWidth(35);

    layout_form_addDate = new QHBoxLayout;
    layout_form_addDate->addWidget(ln_chooseDatabase_addDate);
    layout_form_addDate->addWidget(pbn_chooseDatabase_addDate);
    layout_form_addDate->setSpacing(0);
    layout_form_addDate->setMargin(0);
    layout_addDate = new QHBoxLayout;
    layout_addDate->addLayout(layout_form_addDate);
    layout_addDate->addWidget(ln_chooseTable_addDate);
    layout_addDate->addWidget(ln_addDate);
    layout_addDate->addWidget(pbn_addDate);

    connect(pbn_chooseDatabase_addDate, SIGNAL(clicked()), this, SLOT(chooseDatabase_addDate()));
    connect(pbn_addDate, SIGNAL(clicked()), this, SLOT(addDate()));
    connect(ln_chooseDatabase_addDate, SIGNAL(textChanged(QString)), this, SLOT(ln_chooseDatabase_addDate_textChange(QString)));

    //更新数据
    ln_chooseDatabase_update = new QLineEdit;
    ln_chooseDatabase_update->setPlaceholderText(tr("选择数据库"));
    pbn_chooseDatabase_update = new QPushButton("浏览");
    ln_chooseTable_update = new QLineEdit;
    ln_chooseTable_update->setPlaceholderText(tr("选择表"));
    ln_chooseColumn_update = new QLineEdit;
    ln_chooseColumn_update->setPlaceholderText(tr("选择字段"));
    ln_update = new QLineEdit;
    ln_update->setPlaceholderText(tr("更新的数据"));
    pbn_update = new QPushButton("更新数据");
    layout_form_update = new QHBoxLayout;
    layout_update = new QHBoxLayout;
    ln_chooseDatabase_update->setFixedWidth(180);
    pbn_chooseDatabase_update->setFixedWidth(35);

    layout_form_update = new QHBoxLayout;
    layout_form_update->addWidget(ln_chooseDatabase_update);
    layout_form_update->addWidget(pbn_chooseDatabase_update);
    layout_form_update->setSpacing(0);
    layout_form_update->setMargin(0);
    layout_update = new QHBoxLayout;
    layout_update->addLayout(layout_form_update);
    layout_update->addWidget(ln_chooseTable_update);
    layout_update->addWidget(ln_chooseColumn_update);
    layout_update->addWidget(ln_update);
    layout_update->addWidget(pbn_update);

    connect(pbn_chooseDatabase_update, SIGNAL(clicked()), this, SLOT(chooseDatabase_update()));
    connect(pbn_update, SIGNAL(clicked()), this, SLOT(update()));
    connect(ln_chooseDatabase_update, SIGNAL(textChanged(QString)), this, SLOT(ln_chooseDatabase_update_textChange(QString)));

    //显示区域
    textBrowser = new QTextBrowser(this);
    scroArea = new QScrollArea(this);
    scroArea->setWidget(textBrowser);
    scroArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGridLayout *layout_scroll = new QGridLayout;
    layout_scroll->addWidget(textBrowser, 0, 0, 1, 1);
    layout_scroll->setMargin(0);
    scroArea->setLayout(layout_scroll);

    //顶级布局
    line1 = new QFrame;
    line2 = new QFrame;
    line3 = new QFrame;
    line4 = new QFrame;
    line5 = new QFrame;
    line6 = new QFrame;
    line1->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line2->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line3->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line4->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line5->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    line6->setFrameStyle(QFrame::HLine | QFrame::Sunken);

    layout_top = new QVBoxLayout;
    layout_top->addLayout(layout_Title);
    layout_top->addWidget(line1);
    layout_top->addSpacing(10);
    layout_top->addLayout(layout_createDatabase);
    layout_top->addWidget(line2);
    layout_top->addSpacing(10);
    layout_top->addLayout(layout_addTable);
    layout_top->addWidget(line3);
    layout_top->addSpacing(10);
    layout_top->addLayout(layout_addDate);
    layout_top->addWidget(line4);
    layout_top->addSpacing(10);
    layout_top->addLayout(layout_update);
    layout_top->addWidget(line6);
    layout_top->addSpacing(10);
    layout_top->addLayout(layout_showTables);
    layout_top->addWidget(line5);
    layout_top->addSpacing(10);
    layout_top->addWidget(scroArea);

    setLayout(layout_top);

    lab_title->setObjectName("lab_title");

    setStyleSheet(
                "#lab_title{"
                    "font-size: 24pt;"
                    ""
                "}"
                );

    connect(pbn_choosePath, SIGNAL(clicked()),
            this, SLOT(fillPath()));
    connect(pbn_createDatabase, SIGNAL(clicked()),
            this, SLOT(createDatabase()));
    connect(pbn_chooseDatabase_addTable, SIGNAL(clicked()),
            this, SLOT(chooseDatabase_addTable()));
    connect(pbn_chooseDatabase_showTable, SIGNAL(clicked()),
            this, SLOT(chooseDatabase_showTable()));
    connect(pbn_addTable, SIGNAL(clicked()),
            this, SLOT(addTable()));
    connect(pbn_showTables, SIGNAL(clicked()),
            this, SLOT(showTables()));

    pbn_showTables->setFocus();
}

Widget::~Widget()
{
}

//创建数据库
void Widget::createDatabase()
{
    if (ln_databaseName->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "数据库名称不能为空", QMessageBox::Ok);
        ln_databaseName->setFocus();
        return;
    }
    else if (ln_databasePassword->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "数据库名称不能为空", QMessageBox::Ok);
        ln_databasePassword->setFocus();
        return;
    }
    else if (ln_databaseUsername->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "访问数据库的用户名不能为空", QMessageBox::Ok);
        ln_databaseUsername->setFocus();
        return;
    }
    else if (ln_databasePath->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "数据库生成的路径不能为空", QMessageBox::Ok);
        ln_databasePath->setFocus();
        return;
    }
    if (QFile::exists(ln_databasePath->text()+"/"+ln_databaseName->text()))
    {
        switch(QMessageBox::warning(0, "警告！", "存在同名数据库，覆盖请按确认键，否则请按取消键", QMessageBox::Ok|QMessageBox::Cancel))
        {
        case QMessageBox::Cancel:
            ln_databaseName->setFocus();
            return;
        }
    }
    if (openDatabase(ln_databasePath->text()+"/"+ln_databaseName->text(), ln_databaseUsername->text(), ln_databasePassword->text()))
    {
        ln_databaseName->clear();
        ln_databasePassword->clear();
        ln_databaseUsername->clear();
        ln_databasePath->clear();
        QMessageBox::warning(0, "提示！", "数据库创建成功！", QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(0, "提示！", "数据库创建失败！", QMessageBox::Ok);
    }
    db.close();
}

//选择数据库
void Widget::chooseDatabase_addTable()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty())
    {
        return;
    }
    ln_chooseDatabase_addTable->setText(fileName);
}

//添加表
void Widget::addTable()
{
    if (ln_chooseDatabase_addTable->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "请选择数据库", QMessageBox::Ok);
        ln_chooseDatabase_addTable->setFocus();
        return;
    }
    if (ln_databaseUsername_addTable->text().isEmpty())
    {
//        QMessageBox::warning(0, "错误！", "访问数据库的用户名不能为空", QMessageBox::Ok);
//        ln_databaseUsername_t->setFocus();
//        return;
    }
    if (ln_databasePassword_addTable->text().isEmpty())
    {
//        QMessageBox::warning(0, "错误！", "访问密码不能为空", QMessageBox::Ok);
//        ln_databasePassword_t->setFocus();
//        return;
    }
    if (ln_tableName_addTable->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "表名不能为空", QMessageBox::Ok);
        ln_tableName_addTable->setFocus();
        return;
    }
    if (ln_ziduan->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "字段不能为空", QMessageBox::Ok);
        ln_ziduan->setFocus();
        return;
    }
    if (!openDatabase(ln_chooseDatabase_addTable->text(), ln_databaseUsername_addTable->text(), ln_databasePassword_addTable->text()))
    {
        QMessageBox::warning(0, "错误！", "数据库打开失败！", QMessageBox::Ok);
        return;
    }
    QSqlQuery query(db);
    if (query.exec(tr("create table %1(%2)").arg(ln_tableName_addTable->text()).arg(ln_ziduan->text())))
    {
        QMessageBox::warning(0, "提示！", tr("%1表添加成功").arg(ln_tableName_addTable->text()), QMessageBox::Ok);
//        ln_chooseDatabase_t->clear();
//        ln_databaseUsername_t->clear();
//        ln_databasePassword_t->clear();
        ln_tableName_addTable->clear();
        ln_ziduan->clear();
    }
    else
    {
        QMessageBox::warning(0, "错误！", tr("%1表添加失败").arg(ln_tableName_addTable->text()), QMessageBox::Ok);
    }
    db.close();
}

void Widget::chooseDatabase_showTable()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty())
    {
        return;
    }
    ln_chooseDatabase_showTable->setText(fileName);
//    ln_chooseDatabase_showTable->setText(fileName.isEmpty() ? ln_chooseDatabase_showTable->text() : fileName);
}

//显示表
void Widget::showTables()
{
    if (ln_chooseDatabase_showTable->text().isEmpty())
    {
        QMessageBox::warning(0, "错误！", "请选择数据库", QMessageBox::Ok);
        ln_chooseDatabase_showTable->setFocus();
        return;
    }
    if (ln_databaseUsername_showTable->text().isEmpty())
    {
        //QMessageBox::warning(0, "错误！", "访问数据库的用户名不能为空", QMessageBox::Ok);//ln_databaseUsername_s->setFocus();//return;
    }
    if (ln_databasePassword_showTable->text().isEmpty())
    {
        //QMessageBox::warning(0, "错误！", "访问密码不能为空", QMessageBox::Ok);//ln_databasePassword_s->setFocus();//return;
    }
    if (openDatabase(ln_chooseDatabase_showTable->text(), ln_databaseUsername_showTable->text(), ln_databasePassword_showTable->text()))
    {
        //清空上次查询结果
        for (int i=0; i<tableWidgetList.length(); i++)
        {
            tableWidgetList.at(i)->deleteLater();
        }
        tableWidgetList.clear();

        //显示本次查询结果
        QSqlQuery query(db);
        QSqlQuery queryEach(db);
        //queryTest.exec("SELECT type, name, tbl_name FROM sqlite_master ORDER BY type");
        query.exec("select name from sqlite_master");   //查询表名
        while(query.next())                             //每个表
        {
            qDebug() << "\ntable_name: " << query.value(0).toString();
            tableWidget = new QTableWidget(textBrowser);
            QSqlQuery queryColumn(db);
            int tableColumnCount = 0;
            queryColumn.exec(tr("PRAGMA table_info([%1])").arg(query.value(0).toString()));
            while(queryColumn.next())               //一个表中的列名
            {
                int columnCount = tableWidget->columnCount();
                tableWidget->insertColumn(columnCount);
                tableWidgetItem = new QTableWidgetItem(queryColumn.value(1).toString());
                tableWidget->setHorizontalHeaderItem(columnCount, tableWidgetItem);
                tableColumnCount ++;
            }
            tableWidget->show();
            tableWidgetList.append(tableWidget);
            //显示数据
            queryEach.exec(tr("select * from %1").arg(query.value(0).toString()));
            {
                while(queryEach.next())
                {
                    tableWidget->insertRow(tableWidget->rowCount());        //插入一行表格
                    for (int i=0; i<tableColumnCount; i++)
                    {
                        tableWidgetItem = new QTableWidgetItem(queryEach.value(i).toString());
                        tableWidget->setItem(tableWidget->rowCount()-1, i, tableWidgetItem);
                        tableWidget->item(tableWidget->rowCount()-1, i)->setToolTip(queryEach.value(i).toString());
                    }
                }
            }
        }

        if (tableWidgetList.length() == 0)
        {
            textBrowser->setText("<html><h1>此数据库没有表</h1></html>");
            return;
        }

        for (int i=0; i<tableWidgetList.length(); ++i)
        {
            if (i == 0)
            {
                continue;
            }
            if (i==3 and this->width()<(tableWidgetList.at(0)->width()+28)*4)
            {
                this->resize((tableWidgetList.at(0)->width()+28)*4, this->height());
            }
            if (i == 4 and this->height()<(tableWidgetList.at(0)->height()+20)*2+300)
            {
                this->resize(this->width(), (tableWidgetList.at(0)->height()+20)*2+300);
            }
            if (i%4 == 0)
            {
                tableWidgetList.at(i)->move(tableWidgetList.at(i-4)->x(), tableWidgetList.at(i-4)->y()+tableWidgetList.at(i-4)->height()+20);
                if (i!=4)
                {
                    textBrowser->setFixedHeight((tableWidgetList.at(0)->height()+20) * (i/4) -18);
                }
            }
            else
            {
                tableWidgetList.at(i)->move(tableWidgetList.at(i-1)->x()+tableWidgetList.at(i-1)->width()+20, tableWidgetList.at(i-1)->y());
            }
        }
    }
    db.close();
}

//
void Widget::chooseDatabase_addDate()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty())
    {
        return;
    }
    ln_chooseDatabase_addDate->setText(fileName);
}

//添加数据
void Widget::addDate()
{
    if (ln_chooseDatabase_addDate->text().isEmpty())
    {
        QMessageBox::warning(0, "警告！", "请选择数据库", QMessageBox::Ok);
        ln_chooseDatabase_addDate->setFocus();
        return;
    }
    if (ln_chooseTable_addDate->text().isEmpty())
    {
        QMessageBox::warning(0, "警告！", "请选择表", QMessageBox::Ok);
        ln_chooseTable_addDate->setFocus();
        return;
    }
    if (!openDatabase(ln_chooseDatabase_addDate->text()))
    {
        QMessageBox::warning(0, "警告！", "数据库打开失败", QMessageBox::Ok);
        ln_chooseDatabase_addDate->setFocus();
        return;
    }
    QSqlQuery query(db);
    if (!query.exec(tr("INSERT INTO %1 VALUES('%2')").arg(ln_chooseTable_addDate->text()).arg(ln_addDate->text())))
    {
        QMessageBox::warning(0, "警告！", "请确认表是否存在！", QMessageBox::Ok);
        ln_chooseTable_addDate->setFocus();
        db.close();
        return;
    }
    switch(QMessageBox::warning(0, "警告！", "添加成功！\n”确认“继续添加，”取消“结束添加", QMessageBox::Ok|QMessageBox::Cancel))
    {
    case QMessageBox::Ok:
        ln_addDate->clear();
        ln_addDate->setFocus();
        break;
    case QMessageBox::Cancel:
        ln_chooseDatabase_addDate->clear();
        ln_chooseTable_addDate->clear();
        ln_addDate->clear();
        break;
    default:
        QMessageBox::warning(0, "严重错误！！", "未知错误！", QMessageBox::Ok);
    }
    db.close();
}

//验证输入是否合法
void Widget::ln_chooseDatabase_update_textChange(QString databaseName)
{
    ln_chooseDatabase_update->setStyleSheet(tr("color: %1").arg(ln_chooseDatabase_update->text().isEmpty()|QFile::exists(databaseName) ? "black" : "red"));
}

//
void Widget::chooseDatabase_update()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty())
    {
        return;
    }
    ln_chooseDatabase_update->setText(fileName);
}

//更新数据
void Widget::update()
{
    if (ln_chooseDatabase_update->text().isEmpty())
    {
        QMessageBox::warning(0, "警告！", "请选择数据库", QMessageBox::Ok);
        ln_chooseDatabase_update->setFocus();
        return;
    }
    if (ln_chooseTable_update->text().isEmpty())
    {
        QMessageBox::warning(0, "警告！", "请选择表", QMessageBox::Ok);
        ln_chooseTable_update->setFocus();
        return;
    }
    if (ln_chooseColumn_update->text().isEmpty())
    {
        QMessageBox::warning(0, "警告！", "请选择字段", QMessageBox::Ok);
        ln_chooseColumn_update->setFocus();
        return;
    }
    if (!openDatabase(ln_chooseDatabase_update->text()))
    {
        QMessageBox::warning(0, "警告！", "数据库打开失败", QMessageBox::Ok);
        ln_chooseDatabase_update->setFocus();
        return;
    }
    QSqlQuery query(db);
    if (!query.exec(tr("update %1 set %2='%3'").arg(ln_chooseTable_update->text(), ln_chooseColumn_update->text(), ln_update->text())))
    {
        QMessageBox::warning(0, "警告！", "数据更新失败！", QMessageBox::Ok);
        ln_chooseTable_update->setFocus();
        db.close();
        return;
    }
    QMessageBox::warning(0, "提示！", "更新成功！", QMessageBox::Ok);
    db.close();
}

void Widget::ln_databasePath_textChanged(QString dirName)
{
    QDir dir(dirName);
    ln_databasePath->setStyleSheet(tr("color: %1").arg(dir.exists() ? "black" : "red"));
}

//
void Widget::ln_chooseDatabase_addTable_textChanged(QString databaseName)
{
    if(!QFile::exists(databaseName))
    {
//        QFont font;
        ln_chooseDatabase_addTable->setStyleSheet("color: red;");
    }
    else
    {
        ln_chooseDatabase_addTable->setStyleSheet("color: black;");
    }
}

//
void Widget::ln_chooseDatabase_showTable_textChanged(QString databaseName)
{
//    if(!QFile::exists(databaseName))
//    {
//        ln_chooseDatabase_showTable->setStyleSheet("color: red;");
//    }
//    else
//    {
//        ln_chooseDatabase_showTable->setStyleSheet("color: black;");
//    }
    ln_chooseDatabase_showTable->setStyleSheet(tr("color: %1").arg(QFile::exists(databaseName) ? "black" : "red"));
}

//
void Widget::ln_chooseDatabase_addDate_textChange(QString databaseName)
{
    ln_chooseDatabase_addDate->setStyleSheet(tr("color: %1").arg(ln_chooseDatabase_addDate->text().isEmpty()|QFile::exists(databaseName) ? "black" : "red"));
}

//打开数据库
bool Widget::openDatabase(QString databaseName, QString hostName, QString userName, QString password)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    if (db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//选择路径
void Widget::fillPath()
{
    QString path = QFileDialog::getExistingDirectory();
    if (path.isEmpty())
    {
        return;
    }
    ln_databasePath->setText(path);
}

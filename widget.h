#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtWidgets>
//#include <QLabel>
//#include <QLineEdit>
//#include <QPushButton>
//#include <QHBoxLayout>
//#include <QVBoxLayout>
#include <QSqlDatabase>
//#include <QTextBrowser>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    bool openDatabase(QString databaseName, QString hostName="localhost", QString userName="", QString password="");    //打开数据库

    QLabel *lab_title;
    //创建数据库
    QLineEdit *ln_databaseName;
    QLineEdit *ln_databaseUsername;
    QLineEdit *ln_databasePassword;
    QLineEdit *ln_databasePath;
    QPushButton *pbn_choosePath;
    QPushButton *pbn_createDatabase;
    QHBoxLayout *layout_form_c;
    QHBoxLayout *layout_createDatabase;

    //添加表
    QLineEdit *ln_chooseDatabase_addTable;
    QPushButton *pbn_chooseDatabase_addTable;
    QLineEdit *ln_databaseUsername_addTable;
    QLineEdit *ln_databasePassword_addTable;
    QLineEdit *ln_tableName_addTable;
    QLineEdit *ln_ziduan;
    QPushButton *pbn_addTable;
    QHBoxLayout *layout_form_addTable;
    QHBoxLayout *layout_addTable;

    //查询表
    QLineEdit *ln_chooseDatabase_showTable;
    QPushButton *pbn_chooseDatabase_showTable;
    QLineEdit *ln_databaseUsername_showTable;
    QLineEdit *ln_databasePassword_showTable;
    QPushButton *pbn_showTables;
    QHBoxLayout *layout_form_showTable;
    QHBoxLayout *layout_showTables;

    //添加数据
    QLineEdit *ln_chooseDatabase_addDate;
    QPushButton *pbn_chooseDatabase_addDate;
    QLineEdit *ln_chooseTable_addDate;
    QLineEdit *ln_addDate;
    QPushButton *pbn_addDate;
    QHBoxLayout *layout_form_addDate;
    QHBoxLayout *layout_addDate;

    //更新数据
    QLineEdit *ln_chooseDatabase_update;
    QPushButton *pbn_chooseDatabase_update;
    QLineEdit *ln_chooseTable_update;
    QLineEdit *ln_chooseColumn_update;
    QLineEdit *ln_update;
    QPushButton *pbn_update;
    QHBoxLayout *layout_form_update;
    QHBoxLayout *layout_update;

    //显示区域
    QTextBrowser *textBrowser;
    QScrollArea *scroArea;

    //顶级布局
    QFrame *line1;
    QFrame *line2;
    QFrame *line3;
    QFrame *line4;
    QFrame *line5;
    QFrame *line6;
    QHBoxLayout *layout_Title;
    QVBoxLayout *layout_top;

    QSqlDatabase db;

    QTableWidget *tableWidget;
    QTableWidgetItem *tableWidgetItem;
    QList<QTableWidget*> tableWidgetList;

    QSize initSize;

private slots:
    //
    void ln_databasePath_textChanged(QString);
    void fillPath();
    void createDatabase();
    //
    void ln_chooseDatabase_addTable_textChanged(QString);
    void chooseDatabase_addTable();
    void addTable();
    //
    void ln_chooseDatabase_showTable_textChanged(QString);
    void chooseDatabase_showTable();
    void showTables();
    //
    void ln_chooseDatabase_addDate_textChange(QString);     //验证输入是否合法
    void chooseDatabase_addDate();
    void addDate();
    //
    void ln_chooseDatabase_update_textChange(QString databaseName);     //验证输入是否合法
    void chooseDatabase_update();
    void update();
};

#endif // WIDGET_H

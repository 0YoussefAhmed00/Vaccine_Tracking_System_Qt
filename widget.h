#ifndef WIDGET_H
#define WIDGET_H
#pragma once
using namespace std;
#include<QDebug>//>
#include <QWidget>
#include "User.h"
#include"MainManager.h"
#include <QTextStream>
#include <QCheckBox>
#include "Admin.h"
#include <QMessageBox>
#include<iostream>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QLabel>
#include <QList>
#include <QStringListModel>
#include <QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();





private slots:
    void on_SaveSu_clicked();



    void on_Malesu_clicked();

    void on_FSu_clicked();


    void on_LoginSubmit_clicked();

    void on_ShowEntryButton_clicked();



    void on_EditEntrySubmit_clicked();

    void on_DeleteEntry_clicked();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H

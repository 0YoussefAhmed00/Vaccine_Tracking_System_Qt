#pragma once
#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

        ui->Signup_page->setVisible(false);
        ui->Login_page->setVisible(false);
        ui->FDoseSu->setVisible(false);
        ui->SDoseSu->setVisible(false);
        ui->UserPage->setVisible(false);


}
//###########
    MainManager mm;
    bool Gender;
    Entry entry;
    bool saveEntry;
    bool SubmitLogin;
    bool AdminL;
Widget::~Widget()
{
    delete ui;
}






void Widget::on_SaveSu_clicked()
{

    string UNameSup = ui->UserNameSup->text().toStdString();
    entry.name =UNameSup;
    qDebug() << entry.name <<"\n";
    int Age = ui->AgeSu->text().toInt();
    entry.age=Age;
    qDebug() << entry.age <<"\n";
    int ID = ui->IDSu->text().toInt();
    entry.id=ID;
    qDebug() << entry.id <<"\n";
    string GOV = ui->GovSu->text().toStdString();
    entry.government =GOV;
    qDebug() << entry.government <<"\n";
    if(Gender==true)
    {
        entry.gender='m';
      qDebug() << entry.gender <<"\n";
    }
    else{
        entry.gender='f';
      qDebug() << entry.gender <<"\n";
    }
    string Password = ui->PasswordSu->text().toStdString();
    entry.password =Password;
    qDebug() << entry.password <<"\n";
    string vaccineTypeValue = ui->VacctypeSu->currentText().toStdString();
    entry.vaccineType=vaccineTypeValue;
      qDebug() << entry.vaccineType <<"\n";
    string FirstDoseV = ui->FDoseSu->text().toStdString();
    entry.firstDoseDate =FirstDoseV;
    qDebug() << entry.firstDoseDate<<"\n";

    Qt :: CheckState state = ui->FirstDose->checkState();
    if(state == Qt::Checked){
      entry.firstDose = true;
    }
    else {
      entry.firstDose = false;
    }
    string SecondDoseV = ui->SDoseSu->text().toStdString();
    entry.secondDoseDate =SecondDoseV;
    qDebug() << entry.secondDoseDate<<"\n";
    Qt :: CheckState state2 = ui->SecondDose->checkState();
    if(state2 == Qt::Checked){
      entry.secondDose = true;
    }
    else {
      entry.secondDose = false;
    }
    mm.LoadEntriesFromFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
    if(entry.name=="NULL"||entry.age==NULL||entry.gender=='NULL'||entry.government=="NULL"||entry.password=="NULL")
    {
      saveEntry=false;
      QMessageBox::information(this, "Alert", "Please Enter your Data.");
    }
    else if(mm.CheckID(entry.id))
    {
      QMessageBox::information(this, "Alert", "This ID is Already Exist Chage it Please.");
      saveEntry=false;
    }
    else{
      saveEntry=true;
    }

    if (saveEntry==true){
    mm.CreateEntry(entry);
    mm.SaveEntriesToFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
    ui->AgeSu->clear();
    ui->UserNameSup->clear();
    ui->IDSu->clear();
    ui->GovSu->clear();
    ui->PasswordSu->clear();
    ui->FDoseSu->clear();
    ui->SDoseSu->clear();
     QMessageBox::information(this, "SignedUp successfully", "Now you can Login.");
    }

    }





void Widget::on_Malesu_clicked()
{
    Gender =true;
}


void Widget::on_FSu_clicked()
{
    Gender =false;
}



void Widget::on_LoginSubmit_clicked()
{
    mm.LoadEntriesFromFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
    if (ui->IDLogin->text()=="Admin" &&ui->PasswordLogin->text()=="Admin_1234"){
     QMessageBox::information(this, "successfully logged in", "Welcome Admin.");
     AdminL = true;
     ui->UserPage->setVisible(true);
     ui->IntialView->setVisible(false);
    }else if (AdminL==false){
    int IDLoginV = ui->IDLogin->text().toInt();
    string PasswordLoginV = ui->PasswordLogin->text().toStdString();
    Entry temp;
    temp = mm.GetEntry(IDLoginV);
    if (  PasswordLoginV != temp.password ) {
     // Entry found and password matches
     SubmitLogin = false;
     QMessageBox::information(this, "Not successfully logged in", "Your Password or Username is incorrect. Please try again.");
    } else {
     // Entry not found or password doesn't match
     SubmitLogin = true;
     ui->UserPage->setVisible(true);
     ui->IntialView->setVisible(false);
    }
    }
}


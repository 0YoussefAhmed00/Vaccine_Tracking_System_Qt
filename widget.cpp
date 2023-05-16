#pragma once
#include "widget.h"
#include "ui_widget.h"

MainManager mm;
Admin admin(mm);
User user(mm);
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mm.LoadEntriesFromFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
        ui->Signup_page->setVisible(false);
        ui->Login_page->setVisible(false);
        ui->FDoseSu->setVisible(false);
        ui->SDoseSu->setVisible(false);
        ui->UserPage->setVisible(false);
        ui->ShowPage->setVisible(false);
        ui->EditEntryPage->setVisible(false);
        ui->AdminPageB->setVisible(false);
}
//###########
int IDTemp;
    bool Gender;
    Entry entry;
    bool saveEntry;
    bool SubmitLogin;
    bool AdminL;
    bool EditEntry;
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


    if (ui->IDLogin->text()=="Admin" && ui->PasswordLogin->text()=="Admin_1234" ){
     QMessageBox::information(this, "successfully logged in", "Welcome Admin.");
     AdminL = true;
     ui->AdminPageB->setVisible(true);
     ui->Login_page->setVisible(false);
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
     ui->Login_page->setVisible(false);
     IDTemp=IDLoginV;
    }
    }
}


void Widget::on_ShowEntryButton_clicked()
{

 string username= mm.GetEntry(IDTemp).name;
  QString Username = QString::fromStdString(username);
    ui->ShowUsername->setText(Username);
    int UserID =mm.GetEntry(IDTemp).id;
    QString UseRID = QString::number(UserID);
     ui->ShowUserID->setText(UseRID);
     int UAge =mm.GetEntry(IDTemp).age;
     QString UserAge = QString::number(UAge);
    ui->ShowUserAge->setText(UserAge);
     string UGov= mm.GetEntry(IDTemp).government;
    QString UserGov = QString::fromStdString(UGov);
    ui->ShowUserGov->setText(UserGov);
    string UPassword= mm.GetEntry(IDTemp).password;
    QString UserPassword = QString::fromStdString(UPassword);
     ui->ShowUserPassword->setText(UserPassword);
     string UserVaccineType= mm.GetEntry(IDTemp).vaccineType;
     QString UserVT = QString::fromStdString(UserVaccineType);
     ui->ShowUserVT->setText(UserVT);
     char UserGender =mm.GetEntry(IDTemp).gender;
     QString UGender = QString::fromLatin1(&UserGender, 1);
     ui->ShowUserGender->setText(UserVT);
     string FirstDose =mm.GetEntry(IDTemp).firstDoseDate;
     QString FDose = QString::fromStdString(FirstDose);
     ui->ShowUserFD->setText(FDose);
     string secondDose =mm.GetEntry(IDTemp).secondDoseDate;
     QString SDose = QString::fromStdString(secondDose);
     ui->ShowUserSD->setText(SDose);
}



void Widget::on_EditEntrySubmit_clicked()
{     Entry Editent;

     string EditUN = ui->Editusername->text().toStdString();
     Editent.name =EditUN;

     int EAge = ui->EditUserAge->text().toInt();
     Editent.age=EAge;

     int EID = ui->EditUserID->text().toInt();
     Editent.id=EID;

     string EGOV = ui->EditUserGov->text().toStdString();
     Editent.government = EGOV;
     qDebug() << Editent.government <<"\n";

     char Egender = '\0';
     string EditGender(1, Egender);
     EditGender=ui->EditUserG->text().toStdString();

     string EPassword = ui->EditUserP->text().toStdString();
     Editent.password =EPassword;

     string EvaccineTypeValue = ui->EditUserVT->text().toStdString();
     Editent.vaccineType=EvaccineTypeValue;

     string EFirstDoseV = ui->EditUserFD->text().toStdString();
     Editent.firstDoseDate =EFirstDoseV;

     string ESecondDoseV = ui->EditUserSD->text().toStdString();
     Editent.secondDoseDate =ESecondDoseV;


     if(Editent.name=="NULL"||Editent.age==NULL||Editent.gender=='NULL'||Editent.government=="NULL"||Editent.password=="NULL")
     {
    EditEntry=false;
    QMessageBox::information(this, "Alert", "Please Enter your Data.");
     }

     else if(mm.CheckID(Editent.id))
     {
    QMessageBox::information(this, "Alert", "This ID is Already Exist Chage it Please.");
    EditEntry=false;
     }
     else{
    EditEntry=true;
     }

     if(EditEntry==true){
    ui->EditEntryPage->hide();
     mm.EditEntry(IDTemp,Editent);
     mm.SaveEntriesToFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
}
}

void Widget::on_DeleteEntry_clicked()
{
     mm.DeleteEntry(IDTemp);
      mm.SaveEntriesToFile("D:/QtPs/Vaccine_Tracking_sys_qt/TestingCases.csv");
}




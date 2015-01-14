/*
    addnewurldislog.cpp
    Jelyazka RSS/RDF reader
    Copyright (C) 2014 Vladimir Stoyanov
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "addnewurldislog.h"
#include "ui_addnewurldislog.h"
#include "net.h"
AddNewURLDislog::AddNewURLDislog(/*Ui::MainWindow2 *test,*/ MainWindow2 *test1, QWidget *parent, SiteStruct *tmp_site_struct) :
    QDialog(parent),
    ui(new Ui::AddNewURLDislog)//,
   // ui2(new Ui::MainWindow2)
{
    ui->setupUi(this);
    //o_mw2 = new MainWindow2();
    o_mw2 = test1;
    site_struct = tmp_site_struct;
    //ui2->setupUi(test1);
    //ui2 = test;

}

AddNewURLDislog::~AddNewURLDislog()
{
    delete ui;
    delete o_mw2;
}

void AddNewURLDislog::on_pushButton_clicked() //ok button clicked
{
    QString site = ui->lineEdit->text();
    if (checkSite(site))
    {
        MessageBox(NULL, L"URL is not correct!",L"Error", MB_ICONEXCLAMATION);
        return;
    }
    o_mw2->AddToCombobox(site);
    this->hide();
}

void AddNewURLDislog::on_pushButton_2_clicked()
{
    this->hide();
}
bool AddNewURLDislog::checkSite(QString site)
{
    return 0;
}

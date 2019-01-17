/*
    about.h
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
#ifndef ABOUT_H
#define ABOUT_H

#include <QCloseEvent>
#include <QShowEvent>
#include <QWidget>

#include "ui_about.h"

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    virtual ~About();

private slots:
    void OKButtonClicked(); //'OK' button

private:
    Ui::About *ui;
private:
    void closeEvent(QCloseEvent *); // Overriding the window's close event
    void showEvent(QShowEvent *);
};

#endif // ABOUT_H

/*
    help.h
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
#ifndef HELP_H
#define HELP_H

#include <memory>

#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtDebug>
#include <QWidget>

#include "ui_help.h"

namespace Ui
{
    class Help;
}

class Help : public QWidget
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    virtual ~Help();

private:
    std::shared_ptr <Ui::Help> ui_;

private:
    void closeEvent (QCloseEvent *);
    void loadHelp();
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *);
    void setupGui ();

signals:
    void stateChanged (const QString &);
};

#endif // HELP_H

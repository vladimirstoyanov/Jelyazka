/*
    logger.cpp
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
#include "logger.h"

Logger::Logger()
{
}

void Logger::write(QString message, QString filename)
{
    QFile file(filename);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << message << '\n';

    file.close();
}

void Logger::writeHTMLSourceToFile(QString file_name,QString html_source)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << html_source << '\n';
    file.close();
}

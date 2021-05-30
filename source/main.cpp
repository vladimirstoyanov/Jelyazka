/*
    main.cpp
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
#ifndef MAIN_CPP
#define MAIN_CPP

#include <memory>
#include <vector>

#include <QApplication>

#include "jelyazka_manager.h"
#include "RSS/rss_data.h"
#include "Network/http_data.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<RSSData>("RSSData"); //RSSData is used as parameter by a SLOT function
    qRegisterMetaType<HttpData>("HttpData"); //HttpData is used as parameter by a SLOT function
    qRegisterMetaType< std::vector<RSSData> >("std::vector<RSSData>");

    std::shared_ptr<JelyazkaManager> jelayzka_manager = std::make_shared <JelyazkaManager> ();

    Jelyazka::Settings::loadSettings();
    jelayzka_manager->makeConnections();

    return a.exec();
}

#endif

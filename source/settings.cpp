#include "settings.h"
#include <QMessageBox>

namespace Jelyazka
{

bool                 Settings::is_filtering_enabled_ = false;
bool                 Settings::is_notifications_enabled_ = false;
bool                 Settings::is_proxy_connection_enabled_ = false;
QString              Settings::proxy_ip_address_ = "";
QString              Settings::proxy_port_ = "";
unsigned int         Settings::refresh_feeds_time_ = 1;

Settings::Settings()
{
    loadSettings();
}

Settings::~Settings ()
{
}

//ToDo: refactor the funtion
void Settings::loadSettings()
{
    QFile file("../resources/Options");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0, "Error!", "Can't read \'Options\' file: " + file.errorString());
        return;
    }

    QTextStream in(&file);

    QString what = "";
    QString line = in.readLine();

    //get refresh time
    if (line.length()<14)
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }
    if (line[13] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read refresh time from \'Options\' file!");
        file.close();
        return;
    }

    int i=14;
    while (line[i] != '\n' && i<line.length())
    {
        what+=line[i];
        i++;
    }
    i = what.toInt();
    refresh_feeds_time_ = i;

    line = in.readLine();

    if (line.length()<21)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[20] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }

    if (line[21]=='0')
    {
        is_notifications_enabled_ = false;
    }
    else if (line[21] == '1')
    {
        is_notifications_enabled_ = true;
    }
    else
    {
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from a \'Options\' file!");
    }


    // enable/disable proxy connection option
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for notification window from \'Options\' file!");
        file.close();
        return;
    }
    if (line[14] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for enable proxy connection from \'Options\' file!");
        file.close();
        return;
    }

    if (line[15]=='0')
    {
        is_proxy_connection_enabled_ = false;
    }
    else if (line[15] == '1')
    {
        is_proxy_connection_enabled_ = true;
    }
    else
    {
        QMessageBox::critical(0, "Error!", "Wrong value about \'Notification window\' from \'Options\' file!");
    }

    //load proxy server address
    line = in.readLine();

    if (line.length()<15)
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        file.close();
        return;
    }

    if (line[14]!=' ')
    {
        QMessageBox::critical(0, "Error!", "Something is wrong with proxy url in \'Options\' file!");
        file.close();
        return;
    }

    i=15;
    QString str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    proxy_ip_address_ = str_tmp;

    //laod proxy port information
    line = in.readLine();
    if (line.length()<12)
    {
        QMessageBox::critical(0, "Error!", "Can't laod proxy port from \'Options\' file!");
        file.close();
        return;
    }
    if (line[11]!=' ')
    {
        QMessageBox::critical(0, "Error!", "Can't load proxy port from \'Options\' file!");
        file.close();
        return;
    }

    i=12;
    str_tmp="";
    while(line[i]!='\n' && i<line.length())
    {
        str_tmp+=line[i];
        i++;
    }

    proxy_port_ = str_tmp;

    // enable/disable proxy connection option
    line = in.readLine();

    if (line.length()<17)
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for filters from \'Options\' file!");
        file.close();
        return;
    }
    if (line[16] != ' ')
    {
        QMessageBox::critical(0, "Error!", "Can't read information about check for filters from \'Options\' file!");
        file.close();
        return;
    }

    if (line[17]=='0')
    {
        is_filtering_enabled_ = false;

    }
    else if (line[17] == '1')
    {
        is_filtering_enabled_ = true;

    }
    else
    {
        QMessageBox::critical(0, "Error!", "Wrong value about \'Filter window\' from \'Options\' file!");
    }

    file.close();
}

//ToDo: refactor the funtion
void Settings::saveSettings ()
{
    QFile file("../resources/Options");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    if(!file.isOpen())
    {
        QMessageBox::critical(0, "Error!", "Couldn't open \'Options\' file: " + file.errorString());
        return;
    }

    //notifications
    out << "Refresh time: " << refresh_feeds_time_ <<'\n';
    if (is_notifications_enabled_)
    {
        out << "Notification window: 1\n";
    }
    else
    {
        out << "Notification window: 0\n";
    }

    //proxy
    if (is_proxy_connection_enabled_)
    {
        out << "Enabled Proxy: 1\n";
    }
    else
    {
        out << "Enabled Proxy: 0\n";
    }

    out<<"Proxy Address: "<< proxy_ip_address_<<"\n";
    out<<"Proxy Port: "<< proxy_port_<<"\n";


    //filters
    if (is_filtering_enabled_)
    {
        out << "Enabled Filters: 1\n";
    }
    else
    {
        out << "Enabled Filters: 0\n";
    }

    file.close();
}

} //namespace Jelyazka

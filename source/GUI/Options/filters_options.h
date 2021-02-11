#ifndef FILTEROPTIONS_H
#define FILTEROPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>

#include "database.h"
#include "options.h"
#include "settings.h"
#include "ui_optionswindow.h"

namespace Ui
{
    class OptionsWindow;
}

class FiltersOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    FiltersOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high);

    virtual ~FiltersOptions();

    virtual void initilize ();
    virtual void resize ();
    virtual void saveSettings ();
    virtual void loadSettings ();
    virtual void setupGui ();
    virtual void show ();
    virtual void hide ();

private:
    std::shared_ptr<QCheckBox>              cb_enable_filtering_;
    std::shared_ptr<QLabel>                 l_filter_list_;
    std::shared_ptr<QListWidget>            lw_filter_list_;
    std::shared_ptr<QPushButton>            pb_add_filter_;
    std::shared_ptr<QPushButton>            pb_remove_filter_;
    std::shared_ptr<QTextEdit>              te_add_filter_;
private:
     DataBase                                data_base_;
     std::vector<QString>                    l_old_filters_;
     int                                     ok_button_high_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
private:
    void fillFilterListView();
    int addStringToFilterList(const QString &current_text);
    void on_pb_remove_filter();
    void on_pb_add_filter_clicked();
    void on_cb_enable_filtering_clicked(bool state);
    void insertRowToFiltersTable(const QString &filter_name);
    void updateFiltersTable();
};
#endif // FILTEROPTIONS_H

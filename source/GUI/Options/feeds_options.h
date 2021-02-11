#ifndef FEEDSOPTIONS_H
#define FEEDSOPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>

#include "database.h"
#include "options.h"
#include "settings.h"

class FeedsOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    FeedsOptions(QWidget *parent, const int tree_widget_width, const int ok_button_high);

    virtual ~FeedsOptions();

    void initilize () override;
    void loadSettings () override;
    void hide () override;
    void resize () override;
    void saveSettings () override;
    void setupGui () override;
    void show () override;

private slots:
    void on_removeButton_clicked();
private:
    int addToFeedList(const QString &feed_name);
    int cf_label_search_width();
    void fillFeedListView();
    void positioningFeedsOptionWidgets();

private:
    std::shared_ptr<QLineEdit>              cf_find_feed_;
    std::shared_ptr<QLabel>                 cf_label_search_;
    std::shared_ptr<QListWidget>            feed_list_;
    std::vector<QString>                    l_old_feed_list_;

private:
     DataBase                                data_base_;
     int                                     ok_button_high_;
     int                                     tree_widget_width_;
     QWidget *                               parent;
};
#endif // FEEDSOPTIONS_H

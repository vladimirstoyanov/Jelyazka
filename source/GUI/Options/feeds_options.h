#ifndef FEEDSOPTIONS_H
#define FEEDSOPTIONS_H

#include <memory>
#include <vector>

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

#include "database.h"
#include "options.h"
#include "settings.h"

class FeedsOptions : public QWidget, public IOptions
{
    Q_OBJECT
public:
    FeedsOptions(QWidget *parent,
                 const int tree_widget_width,
                 const int ok_button_height,
                 const int ok_button_y);

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
    void fillFeedListView();
    void positioningFeedsOptionWidgets();

private:
    std::shared_ptr<QListWidget>            feed_list_;
    std::vector<QString>                    l_old_feed_list_;
    std::shared_ptr<QPushButton>            remove_button_;
    QStringList                             removed_feeds_;

private:
     DataBase                                data_base_;
     int                                     ok_button_height_;
     int                                     ok_button_y_;
     const unsigned int                      offset_between_widgets_;
     int                                     tree_widget_width_;
     QWidget*                                parent_;
};
#endif // FEEDSOPTIONS_H

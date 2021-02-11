#include "GUI/Options/filters_options.h"

FiltersOptions::FiltersOptions(QWidget *parent, const int tree_widget_width, const int ok_button_height):
    cb_enable_filtering_ (std::make_shared<QCheckBox>(parent))
    , l_filter_list_ (std::make_shared<QLabel>(parent))
    , lw_filter_list_ (std::make_shared<QListWidget>(parent))
    , pb_add_filter_ (std::make_shared<QPushButton>(parent))
    , pb_remove_filter_ (std::make_shared<QPushButton>(parent))
    , te_add_filter_ (std::make_shared<QTextEdit>(parent))
    , ok_button_height_ (ok_button_height)
    , tree_widget_width_ (tree_widget_width)
    , parent (parent)
{


}

FiltersOptions::~FiltersOptions()
{
    l_old_filters_.clear();
}

void FiltersOptions::setupGui ()
{
    //filter options widgets
    cb_enable_filtering_->setGeometry(tree_widget_width_ + 5,
                                      5,
                                      cb_enable_filtering_->width()+50,
                                      cb_enable_filtering_->height());
    pb_add_filter_->setGeometry(cb_enable_filtering_->x(),
                                cb_enable_filtering_->y()+cb_enable_filtering_->height() + 5,
                                pb_add_filter_->width(),
                                pb_add_filter_->height());
    te_add_filter_->setGeometry(pb_add_filter_->x() + pb_add_filter_->width() + 5,
                                pb_add_filter_->y(),
                                parent->width() - (pb_add_filter_->x() + pb_add_filter_->width() + 10),
                                te_add_filter_->height());
    l_filter_list_->setGeometry(te_add_filter_->x(),
                                te_add_filter_->y() + te_add_filter_->height() + 5,
                                l_filter_list_->width(),
                                l_filter_list_->height());
    lw_filter_list_->setGeometry(te_add_filter_->x(),
                                 l_filter_list_->y()+l_filter_list_->height()+5,
                                 parent->width() - (l_filter_list_->x()+5),
                                 parent->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ok_button_height_));
    pb_remove_filter_->setGeometry(cb_enable_filtering_->x(),
                                  lw_filter_list_->y(),
                                  pb_remove_filter_->width(),
                                  pb_remove_filter_->height());

    cb_enable_filtering_->setChecked(false);
    cb_enable_filtering_->setText("Enable filtering");
    pb_add_filter_->setText("Add");
    pb_remove_filter_->setText("Remove");
    l_filter_list_->setText("Filter List:");

    connect(cb_enable_filtering_.get(), SIGNAL(clicked(bool)), this, SLOT(on_cb_enable_filtering_clicked(bool)));
    connect(pb_add_filter_.get(), SIGNAL(clicked()), this, SLOT(on_pb_add_filter_clicked()));
    connect(pb_remove_filter_.get(), SIGNAL(clicked()), this, SLOT(on_pb_remove_filter()));

    cb_enable_filtering_->hide();
    pb_add_filter_->hide();
    te_add_filter_->hide();
    lw_filter_list_->hide();
    l_filter_list_->hide();
    pb_remove_filter_->hide();

}
void FiltersOptions::show ()
{
    cb_enable_filtering_->show();
    pb_add_filter_->show();
    te_add_filter_->show();
    lw_filter_list_->show();
    l_filter_list_->show();
    pb_remove_filter_->show();
}
void FiltersOptions::hide ()
{
    cb_enable_filtering_->hide();
    pb_add_filter_->hide();
    te_add_filter_->hide();
    lw_filter_list_->hide();
    l_filter_list_->hide();
    pb_remove_filter_->hide();
}

void FiltersOptions::resize ()
{
    te_add_filter_->setGeometry(pb_add_filter_->x() + pb_add_filter_->width() + 5,
                               5,
                               parent->width() - (pb_add_filter_->x() + pb_add_filter_->width() + 10),
                               te_add_filter_->height());

    lw_filter_list_->setGeometry(te_add_filter_->x(),
                                l_filter_list_->y()+l_filter_list_->height()+5,
                                parent->width() - (l_filter_list_->x()+5),
                                parent->height() - (l_filter_list_->y()+ l_filter_list_->height()+15+ ok_button_height_));

}

void FiltersOptions::saveSettings ()
{
    Jelyazka::Settings::setIsFilteringEnabled(cb_enable_filtering_->isChecked());
}

void FiltersOptions::loadSettings ()
{

}

void FiltersOptions::updateFiltersTable()
{
     //main_window_->filters_qlist.clear();
     data_base_.removeDataFromFilters(); //delete all old filters data

     for (int i=0;  i<lw_filter_list_->count(); i++)
     {
         insertRowToFiltersTable(lw_filter_list_->item(i)->text());
     }
}


void FiltersOptions::insertRowToFiltersTable(const QString &filter_name)
{
    data_base_.insertRowToFiltersTable(filter_name);
}


void FiltersOptions::on_cb_enable_filtering_clicked(bool state)
{
    if (state)
    {
        pb_add_filter_->setEnabled(true);
        te_add_filter_->setEnabled(true);
        lw_filter_list_->setEnabled(true);
        l_filter_list_->setEnabled(true);
        pb_remove_filter_->setEnabled(true);
    }
    else
    {
        pb_add_filter_->setEnabled(false);
        te_add_filter_->setEnabled(false);
        lw_filter_list_->setEnabled(false);
        l_filter_list_->setEnabled(false);
        pb_remove_filter_->setEnabled(false);
    }
}

void FiltersOptions::on_pb_add_filter_clicked()
{
    if (addStringToFilterList(te_add_filter_->toPlainText()))
    {
        te_add_filter_->setText("");
        return;
    }
    te_add_filter_->setText("");
}

//remove selected item in filter option
void FiltersOptions::on_pb_remove_filter()
{
    if (lw_filter_list_->currentItem()==NULL)
    {
        return;
    }

    QList<QListWidgetItem*> l;
    l = lw_filter_list_->selectedItems();
    if (l.size()==0)
    {
        return;
    }

    delete l[0];
}

//Filter option: adding string to filter list
int FiltersOptions::addStringToFilterList(const QString &current_text)
{
    int count = lw_filter_list_->count(); //get count of listWidget
    if (current_text=="")
    {
        return 1;
    }

    //check for identical string
    for(int row = 0; row < lw_filter_list_->count(); row++)
    {
        QListWidgetItem *item = lw_filter_list_->item(row);
        // process item
        if (current_text == item->text())
        {
            return 1;
        }
    }

    lw_filter_list_->insertItem(count, current_text); //insert new element in the end of list widget
    return 0;
}

void FiltersOptions::fillFilterListView()
{
    std::vector <QString> tmp;
    data_base_.getFilterList(&tmp);

    l_old_filters_.clear();

    for (unsigned int i=0; i<tmp.size(); i++)
    {
        addStringToFilterList(tmp[i]);
        l_old_filters_.push_back(tmp[i]);
    }
}

void FiltersOptions::initilize ()
{
    lw_filter_list_->clear();
    fillFilterListView();
}

#include "rss_article.h"

RSSArticle::RSSArticle():
    date_ ("")
    , link_("")
    , text_ ("")
    , title_ ("")
{

}

//get
QString RSSArticle::getTitle() const
{
    return title_;
}

QString RSSArticle::getLink() const
{
    return link_;
}

QString RSSArticle::getText() const
{
    return text_;
}

QString RSSArticle::getDate() const
{
    return date_;
}


//set
void RSSArticle::setTitle(const QString &title)
{
    title_ = title;
}

void RSSArticle::setLink(const QString &link)
{
    link_ = link;
}

void RSSArticle::setText(const QString &text)
{
    text_ = text;
}

void RSSArticle::setDate(const QString &date)
{
    date_ = date;
}

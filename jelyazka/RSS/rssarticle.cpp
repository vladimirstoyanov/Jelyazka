#include "rssarticle.h"

RSSArticle::RSSArticle():
    date_ ("")
    , link_("")
    , text_ ("")
    , title_ ("")
{

}

//get
QString RSSArticle::getTitle()
{
    return title_;
}

QString RSSArticle::getLink()
{
    return link_;
}

QString RSSArticle::getText()
{
    return text_;
}

QString RSSArticle::getDate()
{
    return date_;
}


//set
void RSSArticle::setTitle(QString title)
{
    title_ = title;
}

void RSSArticle::setLink(QString link)
{
    link_ = link;
}

void RSSArticle::setText(QString text)
{
    text_ = text;
}

void RSSArticle::setDate(QString date)
{
    date_ = date;
}

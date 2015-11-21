#include "parserss.h"

ParseRSS::ParseRSS(Data *data_tmp)
{
        data = data_tmp;
}



void ParseRSS::findFeedDataRSS(int &index, QString content, RSSArticle &ar)
{
    int item_b_index=index, item_e_index=index;
    CSearch cs;
    int n = content.length();

    while (1)
    {
         cs.search_After(content,"<item", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.search_Before(content,"</item", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         if (item_b_index<n)
         {
             if (content[item_b_index] == 's') //if found <items tag
                 continue;
         }
         index = item_e_index;
         break;
    }

    index = item_e_index;
    QString title, link, text;

    if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
         return;
    convert_string(title, false);
    if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
         return;
    convert_string(link, true);
    getDescription(item_b_index, item_e_index, text, content);

    ar.setLink(link);
    ar.setText(text);
    ar.setTitle(title);
}

void ParseRSS::findFeedDataRDF(int &index, QString content, RSSArticle &ar)
{
    int item_b_index=index, item_e_index=index;
    CSearch cs;

     while (1)
     {
         cs.search_After(content,"<entry", &item_b_index);
         if (item_b_index == -1) // if not found <item
         {
             index = -1;
             return;
         }

         item_e_index = item_b_index;
         cs.search_Before(content,"</entry", &item_e_index);

         if (item_e_index == -1)
         {
             index = -1;
             return;
         }

         index = item_e_index;
         break;
     }

     index = item_e_index;
     QString title, link, text;

     if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
         return;
     convert_string(title, false);
     int index_link = item_b_index;
     cs.search_Before(content, "<link", &index_link);
     if (index_link == -1 || index_link>item_e_index)
         return;
     link = returnURL(content, index_link);
     convert_string(link, true);

     getContent(item_b_index, item_e_index, text, content);

     ar.setLink(link);
     ar.setText(text);
     ar.setTitle(title);
}



int ParseRSS::getTextBetweenIndexes(int item_b_index, int item_e_index, QString begin_text, QString end_text, QString &text, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,begin_text, &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, end_text, &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;


    if (begin_text[begin_text.length()-1] != '>')//version == 2005
    {
        while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
            tag_b_index++;
        tag_b_index++;
    }

    text = "";
    for (int i=tag_b_index; i <tag_e_index; i++)
        text+=content[i];

    return 0;

}

int ParseRSS::getDescription(int item_b_index, int item_e_index, QString &description, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,"<description>", &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, "</description>", &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;


    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.search_After(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                    return 1;
                if (index_tmp <= tag_e_index)
                    i = index_tmp-1;
                continue;
            }
        }
        if (cdata && content[i]=='[')
            continue;
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
                break;
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!' && content[i+2] == '[' && content[i+3] == 'C' && content[i+4] == 'D' && content[i+5] == 'A' && content[i+6] == 'T' && content[i+7] == 'A' && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

//Get articles from rss source
int ParseRSS::getArticlesFromRSSContent(QString content, RSSData *data)
{
    int item_b_index=0, item_e_index=0;
    CSearch cs;
    int n = content.length();

    while(1)
    {
        cs.search_After(content,"<item", &item_b_index);
        if (item_b_index == -1)
            break;

        item_e_index = item_b_index;
        cs.search_Before(content,"</item", &item_e_index);

        if (item_e_index == -1)
            break;

        if (item_b_index<n)
        {
            if (content[item_b_index] == 's') //if found <items tag
                continue;
        }

        QString title, link, text;
        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title>", "</title>", title, content))
            break;
        convert_string(title, false);
        if (getTextBetweenIndexes(item_b_index, item_e_index, "<link>", "</link>", link,content))
            break;

        convert_string(link, true);
        getDescription(item_b_index, item_e_index, text, content);

        RSSArticle art;
        art.setLink(link);
        art.setText(text);
        art.setTitle(title);

        data->articlesPushBack(art);
    }
    return 0;
}

//Get articles from rdf xml
int ParseRSS::getArticlesFromRDFContent(QString content, RSSData *data)
{
    int item_b_index=0, item_e_index=0;
    CSearch cs;

    while(1)
    {
        cs.search_After(content,"<entry", &item_b_index);
        if (item_b_index == -1)
            break;

        item_e_index = item_b_index;
        cs.search_Before(content,"</entry", &item_e_index);

        if (item_e_index == -1)
            break;

        QString title, link, text;

        if(getTextBetweenIndexes(item_b_index, item_e_index, "<title", "</title>", title, content))
            break;

        convert_string(title, false);

        int index_link = item_b_index;
        cs.search_Before(content, "<link", &index_link);
        if (index_link == -1 || index_link>item_e_index)
            break;
        link = returnURL(content, index_link);
        convert_string(link, true);
        getContent(item_b_index, item_e_index, text, content);

        RSSArticle art;

        art.setLink(link);
        art.setText(text);
        art.setTitle(title);

        data->articlesPushBack(art);
    }
    return 0;
}

void ParseRSS::convert_string (QString &str, bool link)
{
    QString entitie;
    QString str_tmp = "";
    bool cdata=false;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] == '&' && !link)
        {
            int c = i;
            entitie = "";
            while(str[i]!=';'&& i<str.length() && (i-c)<7)
            {
                entitie += str[i];
                i++;
            }
            QString conv = convert_entitie(entitie);
            if (conv == "")
                i=c;
            else
                str_tmp += conv;
            continue;
        }
        if (cdata && str[i] == ']')
        {
            cdata = false;
            if (i+2>=str.length())
                break;
            i+=2;
            continue;
        }
        if (str[i] == '<')
        {
            if (str.length()<=i+9)
            {
                str_tmp +=str[i];
                continue;
            }
            //<![CDATA["
            if (str[i+1] == '!' && str[i+2] == '[' && str[i+3] == 'C' && str[i+4] == 'D' && str[i+5] == 'A' && str[i+6] == 'T' && str[i+7] == 'A' && str[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        str_tmp+=str[i];
    }
    str = str_tmp;
}

QString ParseRSS::returnURL(QString source, int index)
{
    if (index <0 || index>source.length())
        return "";

    QString label = "href=";
    int n = source.length();
    int n1 = label.length();


    int j = 0;
    while (source[index]!='>' && index<n)
    {
        if (j==n1) //found 'href' before '>'
            break;

        if (source[index]!=label[j])
        {
            j=0;
            index++;
            continue;
        }
        j++;
        index++;
    }
    if (index >= n) //if not found href= in source
        return "";

    while (source[index]!='\"' && index<n)
        index++;
    index++;
    QString url = "";
    while (source[index]!='\"' && index<n)
        url+=source[index++];

    return url;
}

int ParseRSS::getContent(int item_b_index, int item_e_index, QString &description, QString content)
{
    CSearch cs;
    int tag_b_index, tag_e_index;

    tag_b_index =item_b_index;
    cs.search_After(content,"<content", &tag_b_index);

    if (tag_b_index == -1)
        return 1;
    if (tag_b_index<item_b_index || tag_b_index > item_e_index)
        return 1;

    tag_e_index = tag_b_index;
    cs.search_Before(content, "</content>", &tag_e_index);

    if (tag_e_index == -1)
        return 1;
    if (tag_e_index<item_b_index || tag_e_index > item_e_index)
        return 1;

    while(content[tag_b_index]!='>' && tag_b_index<tag_e_index)
        tag_b_index++;
    tag_b_index++;

    description = "";
    bool cdata = false;
    for (int i=tag_b_index; i <tag_e_index; i++)
    {
        if (content[i]=='&' && i+3 < tag_e_index)
        {
            if (content[i+1] == 'a' && content[i+2] == 'm' && content[i+3] == 'p')
            {
                description+='&';
                i+=5;
            }
            if(content[i+1] == 'l' && content[i+2]=='t' && content[i+3] == ';')
            {
                int index_tmp = i;
                cs.search_After(content,"&gt;",&index_tmp);
                if (index_tmp == -1)
                    return 1;
                if (index_tmp <= tag_e_index)
                    i = index_tmp-1;
                continue;
            }
        }
        if (cdata && content[i]=='[')
            continue;
        if (cdata && content[i] == ']')
        {
            if (i+2>=item_e_index)
                break;
            if (content[i+1] == ']' && content[i+2] == '>')
            {
                cdata = false;
                i+=2;
            }
            continue;
        }
        if (content[i] == '<')
        {
            if (item_e_index<=i+9)
            {
                description+=content[i];
                continue;
            }
            //<![CDATA["
            if (content[i+1] == '!' && content[i+2] == '[' && content[i+3] == 'C' && content[i+4] == 'D' && content[i+5] == 'A' && content[i+6] == 'T' && content[i+7] == 'A' && content[i+8] == '[')
            {
                i+=8;
                cdata = true;
                continue;
            }
        }
        description+=content[i];
    }
    return 0;
}

QString ParseRSS::convert_entitie(QString entitie)
{

    if (entitie == "&quot")
        return "\"";
    else if (entitie == "&nbsp" || entitie =="&#160")
        return " ";
    else if (entitie == "&amp" || entitie == "&#38")
        return "&";
    else if (entitie == "&lt" || entitie == "&#60")
        return "<";
    else if (entitie == "&qt" || entitie == "&#62")
        return ">";
    else if (entitie == "&OElig")
        return "Œ";
    else if (entitie == "&oelig")
        return "œ";
    else if (entitie == "&Scaron")
        return "Š";
    else if (entitie == "&scaron")
        return "š";
    else if (entitie == "&Yuml")
        return "Ÿ";
    else if (entitie == "&circ")
        return "ˆ";
    else if (entitie == "&tilde")
        return "~";
    else if (entitie == "&ndash")
        return "–";
    else if (entitie == "&ndash")
        return "–";
    else if (entitie == "&mdash")
        return "—";
    else if (entitie == "&lsquo")
        return "‘";
    else if (entitie == "&rsquo")
        return "’";
    else if (entitie == "&sbquo")
        return "‚";
    else if (entitie == "&ldquo")
        return "“";
    else if (entitie == "&rdquo")
        return "”";
    else if (entitie == "&bdquo")
        return "„";
    else if (entitie == "&dagger")
        return "†";
    else if (entitie == "&Dagger")
        return "‡";
    else if (entitie == "&permil")
        return "‰";
    else if (entitie == "&lsaquo")
        return "‹";
    else if (entitie == "&rsaquo")
        return "›";
    else if (entitie == "&euro" || entitie == "&#8364")
        return "€";
    else if (entitie == "&cent" || entitie == "&#162" )
        return "¢";
    else if (entitie == "&pound" || entitie == "&#163")
        return "£";
    else if (entitie == "&yen" || entitie == "&#165")
        return "¥";
    else if (entitie == "&copy" || entitie == "&#169")
        return "©";
    else if (entitie == "&reg" || entitie == "&#174")
        return "®";
    else
        return "";
}

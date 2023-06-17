#ifndef JELYAZKA_SCREEN_H
#define JELYAZKA_SCREEN_H

#include <QScreen>
#include <QWidget>
#include <QWindow>

class Screen: public QObject
{
    Q_OBJECT
public:
    Screen() = default;
    virtual ~Screen() = default;
    QScreen* getAcriveScreen (QWidget *widget) const;
};

#endif // SCREEN_H

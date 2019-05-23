#ifndef JELAYZKA_STATE_H
#define JELAYZKA_STATE_H

#include <QObject>
#include <QString>
#include <QtDebug>
namespace Jelyazka
{

class IState: public QObject
{
    Q_OBJECT
public:
      IState () {}
      virtual ~IState () {}

      virtual QString   getName() const = 0;
      virtual void      onEntry() = 0;
      virtual void      onState() = 0;
      virtual void      onExit () = 0;
};

}

#endif

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
      IState () = default;
      virtual ~IState () = default;

      virtual QString   getName() const = 0;
      virtual void      onEntry(const QString &event) = 0;
      virtual void      onState(const QString &event) = 0;
      virtual void      onExit (const QString &event) = 0;
};

}

#endif

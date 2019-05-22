#ifndef JELAYZKA_STATE_H
#define JELAYZKA_STATE_H

#include <QtDebug>

class IState
{
public:
      IState () {}
      virtual void onEntry() = 0;
      virtual void onState() = 0;
      virtual void onExit () = 0;
};

#endif

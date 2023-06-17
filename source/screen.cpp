#include "screen.h"
#include "qwidget.h"


QScreen* Screen::getAcriveScreen (QWidget *widget) const
{
    QScreen* pActive = nullptr;

    while (widget)
    {
        auto window = widget->windowHandle();
        if (window != nullptr)
        {
            pActive = window->screen();
            break;
        }
        else
        {
            widget = widget->parentWidget();
        }
    }

    return pActive;
}

#ifndef IOPTIONS_H
#define IOPTIONS_H

class IOptions
{
public:
    IOptions() = default;

    virtual ~IOptions() = default;

    virtual void confirmSettngs () = 0;
    virtual void hide () = 0;
    virtual void initilize ()=0;
    virtual void loadSettings () = 0;
    virtual void resize () = 0;
    virtual void rollbackSettings () = 0;
    virtual void saveSettings () = 0;
    virtual void setupGui () = 0;
    virtual void show () = 0;

};
#endif // IOPTIONS_H

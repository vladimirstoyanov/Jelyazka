#ifndef IOPTIONS_H
#define IOPTIONS_H

class IOptions
{
public:
    IOptions() = default;

    virtual ~IOptions() = default;

    virtual void hide () = 0;
    virtual void initilize ()=0;
    virtual void loadSettings () = 0;
    virtual void resize () = 0;
    virtual void saveSettings () = 0; //it delegates 'OK' button
    virtual void setupGui () = 0;
    virtual void show () = 0;

};
#endif // IOPTIONS_H

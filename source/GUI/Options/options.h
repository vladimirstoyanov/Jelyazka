#ifndef IOPTIONS_H
#define IOPTIONS_H

class IOptions
{
public:
    IOptions() = default;

    virtual ~IOptions() = default;

    virtual void resize (const int width, const int height) = 0;
    virtual void saveSettings () = 0;
    virtual void loadSettings () = 0;
    virtual void setupGui () = 0;
    virtual void show () = 0;
    virtual void hide () = 0;
};
#endif // IOPTIONS_H

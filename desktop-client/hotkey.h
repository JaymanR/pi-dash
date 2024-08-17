#ifndef HOTKEY_H
#define HOTKEY_H

#include <QObject>
#include <QSettings>
#include <Windows.h>

class Hotkey
{
public:
    explicit Hotkey();

    void setCtrl();
    void setAlt();
    void setShift();
    void setWin();
    void setKey(Qt::Key key);

    void reset();

    Qt::Key getRegularKey() const;
    QString toString() const;
    void execute() const;

private:
    Qt::Key regularKey{Qt::Key_unknown};
    bool ctrl{false};
    bool alt{false};
    bool shift{false};
    bool win{false};

    INPUT createKeyInput(WORD vk, bool keyDown) const;
    WORD keyToVirtualKey(Qt::Key key) const;
};

#endif // HOTKEY_H

#ifndef HOTKEYEDIT_H
#define HOTKEYEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QList>
#include "hotkey.h"

class HotkeyEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HotkeyEdit(QWidget* parent = nullptr);

    Hotkey getHotkey() const;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

private:
    Hotkey hotkey;
    QList<int> keySequence;
    QList<int> modifierKeys = {
        Qt::Key_Control,
        Qt::Key_Shift,
        Qt::Key_Alt,
        Qt::Key_Meta
    };

};

#endif // HOTKEYEDIT_H

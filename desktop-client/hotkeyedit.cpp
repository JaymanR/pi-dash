#include "hotkeyedit.h"
#include <QDebug>

HotkeyEdit::HotkeyEdit(QWidget *parent) : QLineEdit(parent)
{
    setReadOnly(true);
}

void HotkeyEdit::focusInEvent(QFocusEvent *event)
{
    setStyleSheet("border: 2px solid white;");
    hotkey.reset();
    if(!keySequence.isEmpty()) {
        keySequence.clear();
    }
    setText("");
}

void HotkeyEdit::focusOutEvent(QFocusEvent *event)
{
    setStyleSheet("border: none;");
}

void HotkeyEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_unknown) return;

    if (event->isAutoRepeat()) return;

    if (!keySequence.contains(event->key())) {
        keySequence.append(event->key());

        if (event->modifiers() & Qt::ControlModifier) hotkey.setCtrl();
        if (event->modifiers() & Qt::AltModifier) hotkey.setAlt();
        if (event->modifiers() & Qt::ShiftModifier) hotkey.setShift();
        if (event->modifiers() & Qt::MetaModifier) hotkey.setWin();
        if (!modifierKeys.contains(event->key())) {
            hotkey.setKey(static_cast<Qt::Key>(event->key()));
        }
        setText(hotkey.toString());
    }
}

void HotkeyEdit::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    keySequence.removeOne(event->key());

    if (keySequence.isEmpty()) {
        this->clearFocus();
        qDebug() << getHotkey().toString();
    }
}

Hotkey HotkeyEdit::getHotkey() const
{
    return hotkey;
}

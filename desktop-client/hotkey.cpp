#include "hotkey.h"
#include <QKeySequence>

Hotkey::Hotkey() {}

void Hotkey::setCtrl()
{
    ctrl = true;
}

void Hotkey::setAlt()
{
    alt = true;
}

void Hotkey::setShift()
{
    shift = true;
}

void Hotkey::setWin()
{
    win = true;
}

void Hotkey::setKey(Qt::Key key)
{
    this->regularKey = key;
}

Qt::Key Hotkey::getRegularKey() const
{
    return regularKey;
}

void Hotkey::reset()
{
    regularKey = Qt::Key_unknown;
    ctrl = false;
    alt = false;
    shift = false;
    win = false;
}

QString Hotkey::toString() const
{
    QStringList parts;

    if (ctrl) parts << "Ctrl";
    if (alt) parts << "Alt";
    if (shift) parts << "Shift";
    if (win) parts << "Win";
    if (regularKey != Qt::Key_unknown) parts << QKeySequence(regularKey).toString();

    return parts.join(" + ");
}

void Hotkey::execute() const {
    INPUT inputs[5] = {};

    int inputCount{0};

    if (ctrl) inputs[inputCount++] = createKeyInput(VK_CONTROL, true);
    if (alt) inputs[inputCount++] = createKeyInput(VK_MENU, true);
    if (shift) inputs[inputCount++] = createKeyInput(VK_SHIFT, true);
    if (win) inputs[inputCount++] = createKeyInput(VK_LWIN, true);

    inputs[inputCount++] = createKeyInput(keyToVirtualKey(regularKey), true);
    inputs[inputCount++] = createKeyInput(keyToVirtualKey(regularKey), false);

    for (int i{inputCount - 2}; i >= 0; i--) {
        inputs[inputCount++] = createKeyInput(inputs[i].ki.wVk, false);
    }
    SendInput(inputCount, inputs, sizeof(INPUT));
}

INPUT Hotkey::createKeyInput(WORD vk, bool keyDown) const {
    INPUT input = {};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk;
    input.ki.dwFlags = keyDown ? 0 : KEYEVENTF_KEYUP;
    return input;
}

WORD Hotkey::keyToVirtualKey(Qt::Key key) const {
    int qtKey{static_cast<int>(key)};

    QKeySequence keySequence(qtKey);
    QString keyString = keySequence.toString();

    int nativeKey = keyString.isEmpty() ? 0 : keyString[0].unicode();

    if (qtKey >= Qt::Key_F1 && qtKey <= Qt::Key_F35) {
        nativeKey = VK_F1 + (qtKey - Qt::Key_F1);
    } else if (qtKey >= Qt::Key_0 && qtKey <= Qt::Key_9) {
        nativeKey = qtKey;
    } else if (qtKey >= Qt::Key_A && qtKey <= Qt::Key_Z) {
        nativeKey = qtKey;
    }

    return static_cast<WORD>(nativeKey);
}






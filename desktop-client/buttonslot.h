#ifndef BUTTONSLOT_H
#define BUTTONSLOT_H

#include <QWidget>

class ButtonSlot : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonSlot(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool m_isHovered{false};
};

#endif // BUTTONSLOT_H

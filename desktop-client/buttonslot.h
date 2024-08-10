#ifndef BUTTONSLOT_H
#define BUTTONSLOT_H

#include <QWidget>

class ButtonSlot : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonSlot(QWidget *parent = nullptr, int id = 0);

    int id() const;
    bool isSelected() const;
    void setSelected(bool state);

signals:
    void buttonSelected(int buttonId);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    bool m_isHovered{false};
    bool m_isSelected{false};
    const int m_buttonId;
};

#endif // BUTTONSLOT_H

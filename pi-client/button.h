#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>

class Button : public QWidget
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr, int id = 0);

    int id() const;

signals:
    void clicked(int buttonId);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    const int m_buttonId;
    bool m_isClicked{false};
};

#endif // BUTTON_H

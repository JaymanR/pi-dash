#include "button.h"
#include <QPainter>
#include <QPainterPath>

constexpr int s_borderSize{4};
constexpr int s_borderRadius{10};
constexpr QColor s_defaultBorderColor{69, 69, 69}; // #454545
constexpr QColor s_backgroundColor{18, 18, 18}; // #121212
constexpr QColor s_highlightColor{255, 255, 255}; // #696969

Button::Button(QWidget *parent, int buttonId)
    : QWidget{parent}, m_buttonId{buttonId}
{
    setMaximumSize(80, 80);
}

int Button::id() const
{
    return m_buttonId;
}

void Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor borderColor = m_isClicked ? s_highlightColor : s_defaultBorderColor;

    QRectF rect(s_borderSize / 2.0, s_borderSize / 2.0,
                width() - s_borderSize, height() - s_borderSize);

    QPainterPath path;

    path.addRoundedRect(rect, s_borderRadius, s_borderRadius);
    QPen pen(borderColor, s_borderSize);
    painter.setPen(pen);
    painter.fillPath(path, s_backgroundColor);
    painter.drawPath(path);
}

void Button::mousePressEvent(QMouseEvent *event)
{
    emit clicked(m_buttonId);
    m_isClicked = true;
    update();
}

void Button::mouseReleaseEvent(QMouseEvent *event)
{
    m_isClicked = false;
    update();
}

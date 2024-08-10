#include "buttonslot.h"

#include <QPainter>
#include <QPainterPath>

constexpr int s_borderSize{4};
constexpr int s_borderRadius{10};
constexpr QColor s_defaultBorderColor{69, 69, 69}; // #454545
constexpr QColor s_backgroundColor{18, 18, 18}; // #121212
constexpr QColor s_highlightColor{255, 255, 255}; // #696969

ButtonSlot::ButtonSlot(QWidget *parent, int buttonId)
    : QWidget(parent), m_buttonId{buttonId}
{
    setMaximumSize(80,80);
    setMouseTracking(true);
}

int ButtonSlot::id() const
{
    return m_buttonId;
}

bool ButtonSlot::isSelected() const
{
    return m_isSelected;
}

void ButtonSlot::setSelected(bool state)
{
    m_isSelected = state;
    update();
}

void ButtonSlot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor borderColor = m_isHovered || m_isSelected ? s_highlightColor : s_defaultBorderColor;

    QRectF rect(s_borderSize / 2.0, s_borderSize / 2.0,
                width() - s_borderSize, height() - s_borderSize);

    QPainterPath path;

    path.addRoundedRect(rect, s_borderRadius, s_borderRadius);
    QPen pen(borderColor, s_borderSize);
    painter.setPen(pen);
    painter.fillPath(path, s_backgroundColor);
    painter.drawPath(path);
}

void ButtonSlot::enterEvent(QEnterEvent *event)
{
    m_isHovered = true;
    update();
}

void ButtonSlot::leaveEvent(QEvent *event) {
    m_isHovered = false;
    update();
}

void ButtonSlot::mousePressEvent(QMouseEvent *event)
{
    emit buttonSelected(m_buttonId);
}

#include "buttonslot.h"

#include <QPainter>
#include <QPainterPath>

static const int s_borderSize{2};
static const int s_borderRadius{10};
static const QColor s_defaultBorderColor{69, 69, 69}; // #454545
static const QColor s_backgroundColor{18, 18, 18}; // #121212
static const QColor s_highlightColor{255, 255, 255}; // #696969

ButtonSlot::ButtonSlot(QWidget *parent)
    : QWidget(parent)
{
    setMaximumSize(80,80);
    setMouseTracking(true);
}

void ButtonSlot::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor borderColor = m_isHovered ? s_highlightColor : s_defaultBorderColor;
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
/*void ButtonSlot::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor backgroundColor(18, 18, 18);

    QPainterPath path;
    path.addRoundedRect(rect().adjusted(s_borderSize/2, s_borderSize/2, -s_borderSize/2, -s_borderSize/2), s_borderRadius, s_borderRadius);

    painter.fillPath(path, backgroundColor);

    // Set the pen for the border
    QPen pen(s_defaultBorderColor, s_borderSize);
    painter.setPen(pen);

    // Draw the border
    painter.drawPath(path);
}

void ButtonSlot::shapeSlot() {
    QPixmap pixmap(size());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(rect(), s_borderRadius, s_borderRadius);

    setMask(pixmap.mask());
}*/

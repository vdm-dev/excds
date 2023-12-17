#include "headerbar.h"

#include <QPainter>
#include <QPixmapCache>

#include <stylehelper.h>


// Clamps float color values within (0, 255)
static int clamp(double x)
{
    const int val = x > 255.0 ? 255 : static_cast<int>(x);
    return val < 0 ? 0 : val;
}


HeaderBar::HeaderBar(QWidget*parent)
    : QWidget(parent)
{
    _baseColor = QColor(0, 170, 255);

    QFont panelFont(font());
    panelFont.setBold(true);

#if defined(Q_OS_MAC)
    panelFont.setPointSizeF(10);
#else
    panelFont.setPointSizeF(7.5);
#endif

    QFontMetrics metrics(panelFont);

    int height = metrics.height() + 40;

    setFixedHeight(height);

    _fontHeight = height / 2;

    panelFont.setPixelSize(_fontHeight);

    setFont(panelFont);
}

void HeaderBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    // Map offset for global window gradient
    QPoint offset = window()->mapToGlobal(rect().topLeft()) - mapToGlobal(rect().topLeft());

    QRect gradientSpan = QRect(offset, window()->size());

    QPainter painter(this);

    QString key;
    key.sprintf("mh_horizontal %d %d %d %d %d %d",
        gradientSpan.width(), gradientSpan.height(), rect().width(),
        rect().height(), _baseColor.rgb(), gradientSpan.x());

    QPixmap pixmap;

    if (!QPixmapCache::find(key, pixmap))
    {
        pixmap = QPixmap(rect().size());

        QPainter p(&pixmap);

        QRect r = QRect(0, 0, rect().width(), rect().height());

        QColor highlight = highlightColor(_baseColor);
        QColor shadow = shadowColor(_baseColor);

        QLinearGradient grad(r.topLeft(), r.bottomLeft());

        grad.setColorAt(0, highlight.lighter(120));

        /*
        if (r.height() == StyleHelper::navigationWidgetHeight()) {
            grad.setColorAt(0.4, highlight);
            grad.setColorAt(0.401, base);
        }
        */

        grad.setColorAt(1, shadow);
        p.fillRect(r, grad);

        QLinearGradient shadowGradient(gradientSpan.topLeft(), gradientSpan.topRight());
            shadowGradient.setColorAt(0, QColor(0, 0, 0, 30));

        QColor lighterHighlight;
        lighterHighlight = highlight.lighter(130);
        lighterHighlight.setAlpha(100);
        shadowGradient.setColorAt(0.7, lighterHighlight);
            shadowGradient.setColorAt(1, QColor(0, 0, 0, 40));
        p.fillRect(r, shadowGradient);

        p.end();
        QPixmapCache::insert(key, pixmap);
    }

    painter.drawPixmap(rect().topLeft(), pixmap);

    painter.setPen(Manhattan::Utils::StyleHelper::borderColor());
    painter.drawLine(rect().bottomLeft(), rect().bottomRight());

    painter.setPen(QColor(255, 255, 255, 40));
    painter.drawLine(rect().topLeft(), rect().topRight());

    if (!_text.isEmpty())
    {
        QRect textRect = rect();
        textRect.setLeft(_fontHeight);

        textRect.translate(0, 1);
        painter.setPen(QColor(0, 0, 0, 110));
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, _text);

        textRect.translate(0, -1);
        painter.setPen(Manhattan::Utils::StyleHelper::panelTextColor());
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, _text);
    }
}

QColor HeaderBar::highlightColor(const QColor& baseColor)
{
    QColor result = baseColor;
    result.setHsv(result.hue(), clamp(result.saturation()), clamp(result.value() * 1.16));
    return result;
}

QColor HeaderBar::shadowColor(const QColor& baseColor)
{
    QColor result = baseColor;
    result.setHsv(result.hue(), clamp(result.saturation() * 1.1), clamp(result.value() * 0.70));
    return result;
}

QColor HeaderBar::borderColor(const QColor& baseColor)
{
    QColor result = baseColor;
    result.setHsv(result.hue(), result.saturation(), result.value() / 2);
    return result;
}

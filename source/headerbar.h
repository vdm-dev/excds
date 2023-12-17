#ifndef HEADERBAR_H
#define HEADERBAR_H


#include <QWidget>


class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderBar(QWidget* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QColor highlightColor(const QColor& baseColor);
    QColor shadowColor(const QColor& baseColor);
    QColor borderColor(const QColor& baseColor);

    QColor _baseColor;
    QString _text;

    int _fontHeight;
};


inline QString HeaderBar::text() const
{
    return _text;
}

inline void HeaderBar::setText(const QString& text)
{
    _text = text;
    update();
}


#endif // HEADERBAR_H

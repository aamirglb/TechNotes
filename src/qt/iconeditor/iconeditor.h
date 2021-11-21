#pragma once

#include <QColor>
#include <QImage>
#include <QWidget>

class IconEditor : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QColor penColor   READ penColor   WRITE setPenColor)
    Q_PROPERTY(QImage iconImage  READ iconImage  WRITE setIconImage)
    Q_PROPERTY(int    zoomFactor READ zoomFactor WRITE setZoomFactor)

public:
    IconEditor(QWidget *parent = nullptr);

    void setPenColor(const QColor &newColor);
    QColor penColor() const { return curColor; }
    void setZoomFactor(int newZoom);
    int zoomFactor() const { return zoom; }
    void setIconImage(const QImage &newImage);
    QImage iconImage() const { return image; }
    QSize sizeHint() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage image;
    int zoom;
};
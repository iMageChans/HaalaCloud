#ifndef FILESHEADERVIEW_H
#define FILESHEADERVIEW_H

#include <QHeaderView>

class FilesHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    FilesHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);

    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

public slots :
    void onStateChanged(int state);

signals :
    void stateChanged(int state);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;


private:
    bool m_bPressed;
    bool m_bChecked;
    bool m_bTristate;
    bool m_bNoChange;
    bool m_bMoving;
};

#endif // FILESHEADERVIEW_H

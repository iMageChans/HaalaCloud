#include "filesheaderview.h"

#include <QPainter>
#include <QCheckBox>
#include <QMouseEvent>

FilesHeaderView::FilesHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent),
      m_bPressed(false),
      m_bChecked(false),
      m_bTristate(false),
      m_bNoChange(false),
      m_bMoving(false)
{
    setHighlightSections(false);
    setMouseTracking(true);
    setSectionsClickable(true);
}

void FilesHeaderView::onStateChanged(int state)
{
    if (state == Qt::PartiallyChecked) {
        m_bTristate = true;
        m_bNoChange = true;
    } else {
        m_bNoChange = false;
    }

    m_bChecked = (state != Qt::Unchecked);
    update();
}

void FilesHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    if (logicalIndex == 0)
    {
        QStyleOptionButton option;
        option.initFrom(this);

        if (m_bChecked)
            option.state |= QStyle::State_Sunken;

        if (m_bTristate && m_bNoChange)
            option.state |= QStyle::State_NoChange;
        else
            option.state |= m_bChecked ? QStyle::State_On : QStyle::State_Off;

        if (testAttribute(Qt::WA_Hover) && underMouse()) {
            if (m_bMoving)
                option.state |= QStyle::State_MouseOver;
            else
                option.state &= ~QStyle::State_MouseOver;
        }

        QCheckBox checkBox;
        option.iconSize = QSize(12, 12);
#if defined(Q_OS_MAC)
        option.rect = QRect(5, 6, 12, 12);
#elif defined(Q_OS_WIN32)
        option.rect = QRect(8, 6, 12, 12);
#endif
        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter, &checkBox);
    }
}

void FilesHeaderView::mousePressEvent(QMouseEvent *event)
{
    int nColumn = logicalIndexAt(event->pos());
    if ((event->buttons() & Qt::LeftButton) && (nColumn == 0))
        m_bPressed = true;
    else
        QHeaderView::mousePressEvent(event);
}

void FilesHeaderView::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_bPressed)
    {
        if (m_bTristate && m_bNoChange){
            m_bChecked = true;
            m_bNoChange = false;
        }
        else{
            m_bChecked = !m_bChecked;
        }
        update();

        Qt::CheckState state = m_bChecked ? Qt::Checked : Qt::Unchecked;

        emit stateChanged(state);
    }
    else
    {
        QHeaderView::mouseReleaseEvent(event);
    }

    m_bPressed = false;
}

bool FilesHeaderView::event(QEvent *event)
{
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave)
    {
        QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);
        int nColumn = logicalIndexAt(pEvent->x());
        if (nColumn == 0)
        {
            m_bMoving = (event->type() == QEvent::Enter);

            update();
            return true;
        }
    }

    return QHeaderView::event(event);
}

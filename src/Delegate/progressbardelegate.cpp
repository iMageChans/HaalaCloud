#include "progressbardelegate.h"

#include <QProgressBar>

ProgressBarDelegate::ProgressBarDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void ProgressBarDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, viewOption, index);

    if (index.column() == FILE_DOWNLOAD_PROGRESS_COLUMN)
    {
        int nProgress = index.model()->data(index, Qt::UserRole).toInt();
        int nLeft = 8;
        int nTop = 8;
        int nWidth = option.rect.width() - 2 * nLeft;
        int nHeight = option.rect.height() - 2 * nTop;

        // 设置进度条的风格
        QStyleOptionProgressBar progressBarOption;
        progressBarOption.initFrom(option.widget);
        // 设置进度条显示的区域
        progressBarOption.rect = QRect(option.rect.left() + nLeft, option.rect.top() + nTop,  nWidth, nHeight);
        // 设置最小值
        progressBarOption.minimum = 0;
        // 设置最大值
        progressBarOption.maximum = 100;
        // 设置对齐方式
        progressBarOption.textAlignment = Qt::AlignCenter;
        // 设置进度
        progressBarOption.progress = nProgress;
        // 设置文本（百分比）
        progressBarOption.text = QString("%1%").arg(nProgress);
        // 设置文本可见
        progressBarOption.textVisible = true;

        QProgressBar progressBar;
        progressBar.setStyleSheet("QProgressBar{border:none;background:#E9E9E9;border-radius:5px;}"
                                  "QProgressBar::chunk {background-color:#2EC17C;border-radius:5px;}");

        //绘制进度条
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter, &progressBar);
    }
}

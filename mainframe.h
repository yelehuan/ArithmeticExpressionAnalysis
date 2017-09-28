#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
class QLineEdit;
class QVBoxLayout;
class QLabel;
class MainFrame : public QWidget
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = 0);

signals:

public slots:
    void slotHandleExpression();
private:
    void initLayout();
    void connects();
private:
    QLineEdit *mCinWidget;
    QLabel *mResultLabelTip;
    QLabel *mResultLabel;
    QVBoxLayout *mMainLayout;
    QLabel *mJsResultTip;
    QLabel *mJsResult;
};

#endif // MAINFRAME_H

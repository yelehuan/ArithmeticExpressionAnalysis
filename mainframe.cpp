#include "mainframe.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QJSEngine>
#include "expressionparse.h"

MainFrame::MainFrame(QWidget *parent)
    : QWidget(parent)
    , mCinWidget(Q_NULLPTR)
    , mMainLayout(Q_NULLPTR)
    , mResultLabel(Q_NULLPTR)
{
    initLayout();
    connects();
}

void MainFrame::slotHandleExpression()
{
    if (mCinWidget && !mCinWidget->text().isEmpty()) {
        ExpressionParse parse;
        QString resultStr;
        QString expression = mCinWidget->text();
        parse.expressionExcute(expression, resultStr);
        mResultLabel->setText(resultStr);

        QJSEngine engine;
        QJSValue value = engine.evaluate(expression);
        mJsResult->setText(value.toString());
    }
}

void MainFrame::initLayout()
{
    mCinWidget = new QLineEdit(this);
    mResultLabelTip = new QLabel(QStringLiteral("Result: "), this);
    mResultLabel = new QLabel(this);
    QHBoxLayout *resultLayout = new QHBoxLayout;
    resultLayout->addWidget(mResultLabelTip);
    resultLayout->addWidget(mResultLabel);

    mJsResultTip = new QLabel(QStringLiteral("QJSEngine Result: "), this);
    mJsResult = new QLabel(this);
    QHBoxLayout *jsResultLayout = new QHBoxLayout;
    jsResultLayout->addWidget(mJsResultTip);
    jsResultLayout->addWidget(mJsResult);

    mMainLayout = new QVBoxLayout(this);
    mMainLayout->addWidget(mCinWidget);
    mMainLayout->addLayout(resultLayout);
    mMainLayout->addLayout(jsResultLayout);
    this->resize(400, 100);
}

void MainFrame::connects()
{
    connect(mCinWidget, SIGNAL(editingFinished()), this, SLOT(slotHandleExpression()));
}

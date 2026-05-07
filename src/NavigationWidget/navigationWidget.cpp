#include "navigationWidget.h"

#include <QtWebEngineQuick/QtWebEngineQuick>
#include <QUrl>
#include <QVBoxLayout>

namespace Procrastination::Internal {

NavigationWidget::NavigationWidget(QWidget *parent) :
    QWidget(parent) , m_quickWidget(new QQuickWidget(this)) {

    const auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_quickWidget);

    m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_quickWidget->setSource(QUrl("qrc:/main.qml"));
}

} // namespace Procrastination::Internal

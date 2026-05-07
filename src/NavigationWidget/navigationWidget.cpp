#include "navigationWidget.h"

#include <QUrl>
#include <QVBoxLayout>

namespace Procrastination::Internal {

NavigationWidget::NavigationWidget(QWidget *parent)
    : QWidget(parent)
    , m_quickView(new QQuickView)
{
    m_quickView->setResizeMode(QQuickView::SizeRootObjectToView);
    m_quickView->setSource(QUrl("qrc:/main.qml"));

    auto *container = QWidget::createWindowContainer(m_quickView, this);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(container);
}

} // namespace Procrastination::Internal

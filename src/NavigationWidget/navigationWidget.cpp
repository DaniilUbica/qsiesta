#include "navigationWidget.h"

namespace Procrastination::Internal {

NavigationWidget::NavigationWidget(QWidget* parent) : QWidget(parent) {
    m_currentView = new QQuickView();
    m_currentView->setResizeMode(QQuickView::SizeRootObjectToView);
    m_currentView->setVisible(false);

    m_currentViewContainer = QWidget::createWindowContainer(m_currentView, this);
    m_currentViewContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_viewsModel = new ViewsModel(this);

    m_treeView = new Utils::NavigationTreeView(this);
    m_treeView->setModel(m_viewsModel);
    m_treeView->setHeaderHidden(true);
    m_treeView->setRootIsDecorated(false);

    m_layout = new QStackedLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_treeView);
    m_layout->addWidget(m_currentViewContainer);
    m_layout->setCurrentWidget(m_treeView);

    connect(m_treeView, &QAbstractItemView::clicked, this, &NavigationWidget::onModelItemClicked);
}

void NavigationWidget::openViewsList() {
    if (m_layout->currentWidget() != m_treeView) {
        m_layout->setCurrentWidget(m_treeView);
        Q_EMIT viewsListVisibleChanged(true);
    }
}

void NavigationWidget::onModelItemClicked(const QModelIndex& index) {
    if (const auto item = m_viewsModel->itemFromIndex(index)) {
        m_currentView->setSource(item->data(ViewsModel::SourceRole).toUrl());
        m_layout->setCurrentWidget(m_currentViewContainer);
        Q_EMIT viewsListVisibleChanged(false);
    }
}

} // namespace Procrastination::Internal

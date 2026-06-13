#include "navigationWidget.h"

#include "Base/gameManagerBase.h"

#include <QQmlFileSelector>

namespace QSiesta::Internal {

const unsigned int ICON_SIZE = 10;

NavigationWidget::NavigationWidget(QWidget* parent) : QWidget(parent) {
    m_contentView = new QQuickView();
    m_contentView->setResizeMode(QQuickView::SizeRootObjectToView);
    new QQmlFileSelector(m_contentView->engine(), m_contentView);

    m_miniGamesManager = new minigame::MiniGamesManager(this);
    m_miniGamesManager->setupContext(m_contentView);

    m_contentViewContainer = QWidget::createWindowContainer(m_contentView, this);
    m_contentViewContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_viewsModel = new ViewsModel(m_miniGamesManager, this);

    m_treeView = new Utils::NavigationTreeView(this);
    m_treeView->setModel(m_viewsModel);
    m_treeView->setHeaderHidden(true);
    m_treeView->setRootIsDecorated(false);
    m_treeView->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    m_layout = new QStackedLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addWidget(m_treeView);
    m_layout->addWidget(m_contentViewContainer);
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
    const auto item = m_viewsModel->itemFromIndex(index);
    if (!item) {
        return;
    }

    const auto gameVariant = item->data(ViewsModel::GameRole);
    if (gameVariant.isValid()) {
        auto* game = gameVariant.value<minigame::base::GameManagerBase*>();
        if (game) {
            m_miniGamesManager->setCurrentGame(game);
        }
    }

    m_contentView->setSource(item->data(ViewsModel::SourceRole).toUrl());
    m_layout->setCurrentWidget(m_contentViewContainer);
    Q_EMIT viewsListVisibleChanged(false);
}

} // namespace QSiesta::Internal

#include "navigationWidgetFactory.h"

#include "procrastinationTr.h"
#include "procrastinationConstants.h"
#include "navigationWidget.h"

#include <QToolButton>

namespace Procrastination::Internal {

NavigationWidgetFactory::NavigationWidgetFactory(QQuickView* contentView) {
    m_contentView = contentView;

    setDisplayName(Tr::tr(Constants::PLUGIN_ID));
    setPriority(500);
    setId(Constants::PLUGIN_ID);
}

Core::NavigationView NavigationWidgetFactory::createWidget() {
    const auto widget = new NavigationWidget(m_contentView);

    const auto backButton = new QToolButton();
    backButton->setIcon(QIcon::fromTheme("go-previous"));
    backButton->setToolTip(Tr::tr("Back to views list"));
    backButton->setVisible(false);

    connect(backButton, &QToolButton::clicked, widget, &NavigationWidget::openViewsList);
    connect(widget, &NavigationWidget::viewsListVisibleChanged, backButton, [backButton](bool visible) {
        backButton->setVisible(!visible);
    });

    return { widget, { backButton } };
}

} // namespace Procrastination::Internal

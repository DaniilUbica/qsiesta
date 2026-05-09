#include "navigationWidgetFactory.h"

#include "qsiestaTr.h"
#include "qsiestaConstants.h"
#include "navigationWidget.h"

#include <QToolButton>

namespace QSiesta::Internal {

NavigationWidgetFactory::NavigationWidgetFactory() {
    setDisplayName(Tr::tr(Constants::PLUGIN_ID));
    setPriority(500);
    setId(Constants::PLUGIN_ID);
}

Core::NavigationView NavigationWidgetFactory::createWidget() {
    const auto widget = new NavigationWidget();

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

} // namespace QSiesta::Internal

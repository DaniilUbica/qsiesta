#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

#include <QWidget>

namespace QSiesta::Internal {

class NavigationWidget;

class NavigationWidgetFactory : public Core::INavigationWidgetFactory {
    Q_OBJECT
public:
    NavigationWidgetFactory();

    Core::NavigationView createWidget() override;
};

} // namespace QSiesta::Internal

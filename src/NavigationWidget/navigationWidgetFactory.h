#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

#include <QQuickWidget>
#include <QWidget>

namespace Procrastination::Internal {

class NavigationWidget;

class NavigationWidgetFactory : public Core::INavigationWidgetFactory {
    Q_OBJECT
public:
    NavigationWidgetFactory();

    Core::NavigationView createWidget() override;
};

} // namespace Procrastination::Internal

#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

#include <QQuickWidget>
#include <QWidget>
#include <QQuickView>

namespace QSiesta::Internal {

class NavigationWidget;

class NavigationWidgetFactory : public Core::INavigationWidgetFactory {
    Q_OBJECT
public:
    NavigationWidgetFactory(QQuickView* contentView);

    Core::NavigationView createWidget() override;

private:
    QQuickView* m_contentView;
};

} // namespace QSiesta::Internal

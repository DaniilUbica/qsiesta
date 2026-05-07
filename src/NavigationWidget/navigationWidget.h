#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

#include <QQuickWidget>
#include <QWidget>

namespace Procrastination::Internal {

class NavigationWidget : public QWidget {
    Q_OBJECT
public:
    explicit NavigationWidget(QWidget *parent = nullptr);

private:
    QQuickWidget* m_quickWidget;
};

} // namespace Procrastination::Internal

#pragma once

#include <coreplugin/inavigationwidgetfactory.h>

#include <QQuickView>
#include <QWidget>

namespace Procrastination::Internal {

class NavigationWidget : public QWidget {
    Q_OBJECT
public:
    explicit NavigationWidget(QWidget *parent = nullptr);

private:
    QQuickView *m_quickView;
};

} // namespace Procrastination::Internal

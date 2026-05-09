#pragma once

#include <coreplugin/inavigationwidgetfactory.h>
#include <utils/navigationtreeview.h>

#include <QStackedLayout>
#include <QQuickView>
#include <QStandardItemModel>
#include <QWidget>

#include "NavigationWidget/viewsModel.h"

namespace QSiesta::Internal {

class NavigationWidget : public QWidget {
    Q_OBJECT
public:
    explicit NavigationWidget(QWidget* parent = nullptr);

    void openViewsList();

    Q_SLOT void onModelItemClicked(const QModelIndex& index);

    Q_SIGNAL void viewsListVisibleChanged(bool visible);

private:
    QQuickView* m_contentView = nullptr;
    QWidget* m_contentViewContainer = nullptr;

    ViewsModel* m_viewsModel = nullptr;
    Utils::NavigationTreeView* m_treeView = nullptr;

    QStackedLayout* m_layout = nullptr;
};

} // namespace QSiesta::Internal

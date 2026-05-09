#include "viewsModel.h"

#include <utils/theme/theme.h>

namespace QSiesta::Internal {

ViewsModel::ViewsModel(QObject* parent) : QStandardItemModel(parent) {
    const auto iconsPath = QString(":/icons/") +
            (Utils::creatorTheme()->flag(Utils::Theme::DarkUserInterface) ? "dark-theme/" : "light-theme/");

    addView(views::names::tikTok, QUrl("qrc:/views/QMTikTokView.qml"), iconsPath + "tiktok.svg");
}

void ViewsModel::addView(const QString& name, const QUrl& source, const QString& icon) {
    const auto item = new QStandardItem(name);
    item->setData(source, SourceRole);
    item->setEditable(false);
    item->setIcon(QIcon(icon));

    appendRow(item);
}

} // namespace QSiesta::Internal

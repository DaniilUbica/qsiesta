#include "viewsModel.h"

#include "MiniGamesManager/miniGamesManager.h"
#include "Base/gameManagerBase.h"

#include <utils/theme/theme.h>

namespace QSiesta::Internal {

ViewsModel::ViewsModel(minigame::MiniGamesManager* manager, QObject* parent) : QStandardItemModel(parent) {
    const auto iconsPath = QString(":/icons/") +
            (Utils::creatorTheme()->flag(Utils::Theme::DarkUserInterface) ? "dark-theme/" : "light-theme/");

    addView(views::names::tikTok, QUrl("qrc:/views/QMTikTokView.qml"), iconsPath + "tiktok.svg");

    for (auto* game : manager->games()) {
        addGame(game, iconsPath + game->gameDescription().iconName);
    }
}

void ViewsModel::addView(const QString& name, const QUrl& source, const QString& icon) {
    const auto item = new QStandardItem(name);
    item->setData(source, SourceRole);
    item->setEditable(false);
    item->setIcon(QIcon(icon));
    appendRow(item);
}

void ViewsModel::addGame(minigame::base::GameManagerBase* game, const QString& icon) {
    const auto item = new QStandardItem(game->gameDescription().name);
    item->setData(QUrl("qrc:/views/QMGameView.qml"), SourceRole);
    item->setData(QVariant::fromValue<minigame::base::GameManagerBase*>(game), GameRole);
    item->setEditable(false);
    item->setIcon(QIcon(icon));
    appendRow(item);
}

} // namespace QSiesta::Internal

#pragma once

#include <QStandardItemModel>
#include <QUrl>

#include "MiniGames/MiniGamesManager/miniGamesManager.h"

namespace QSiesta::Internal {

namespace views::names {
    static const QString tikTok = QStringLiteral("TikTok");
    static const QString snake  = QStringLiteral("Snake");
}

class ViewsModel : public QStandardItemModel {
    Q_OBJECT
public:
    enum Roles {
        SourceRole = Qt::UserRole + 1,
        GameRole
    };

    ViewsModel(QObject* parent = nullptr);

private:
    void addView(const QString& name, const QUrl& source, const QString& icon = "");
    void addGame(const QString& name, minigame::MiniGame game, const QString& icon = "");
};

} // namespace QSiesta::Internal

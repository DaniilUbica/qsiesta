#pragma once

#include <QStandardItemModel>
#include <QUrl>

namespace QSiesta::Internal {

namespace minigame { class MiniGamesManager; }
namespace minigame::base { class GameManagerBase; }

namespace views::names {
    static const QString tikTok = QStringLiteral("TikTok");
}

class ViewsModel : public QStandardItemModel {
    Q_OBJECT
public:
    enum Roles {
        SourceRole = Qt::UserRole + 1,
        GameRole
    };

    ViewsModel(minigame::MiniGamesManager* manager, QObject* parent = nullptr);

private:
    void addView(const QString& name, const QUrl& source, const QString& icon = "");
    void addGame(minigame::base::GameManagerBase* game, const QString& icon = "");
};

} // namespace QSiesta::Internal

#pragma once

#include <QStandardItemModel>
#include <QUrl>

namespace QSiesta::Internal {

namespace views::names {
    static const QString tikTok  = QStringLiteral("TikTok");
}

class ViewsModel : public QStandardItemModel {
    Q_OBJECT
public:
    enum Roles {
        SourceRole = Qt::UserRole + 1
    };

    ViewsModel(QObject* parent = nullptr);

private:    
    void addView(const QString& name, const QUrl& source, const QString& icon = "");
};

} // namespace QSiesta::Internal

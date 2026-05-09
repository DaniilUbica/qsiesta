#pragma once

#include <QStandardItemModel>
#include <QUrl>

namespace Procrastination::Internal {

namespace views::names {
    static const QString tikTok  = QStringLiteral("TikTok");
}

class ViewsModel : public QStandardItemModel {
    Q_OBJECT
public:
    enum Roles {
        SourceRole = Qt::UserRole + 1,
    };

    ViewsModel(QObject* parent = nullptr);

private:    
    void addView(const QString& name, const QUrl& source);
};

} // namespace Procrastination::Internal

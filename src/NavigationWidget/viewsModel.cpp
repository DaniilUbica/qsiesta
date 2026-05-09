#include "viewsModel.h"

namespace Procrastination::Internal {

ViewsModel::ViewsModel(QObject *parent) : QStandardItemModel(parent) {
    addView(views::names::tikTok, QUrl("qrc:/views/QMTikTokView.qml"));
}

void ViewsModel::addView(const QString& name, const QUrl& source) {
    const auto item = new QStandardItem(name);
    item->setData(source, SourceRole);
    item->setEditable(false);

    appendRow(item);
}

} // namespace Procrastination::Internal

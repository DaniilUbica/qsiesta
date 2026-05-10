#pragma once

#include <QObject>
#include <QUrl>

namespace QSiesta::Internal {
namespace minigame::defines {

struct MiniGameEntry {
    QUrl qmlSource;
    QObject* manager = nullptr;
};

} // namespace minigame
} // namespace QSiesta::Internal
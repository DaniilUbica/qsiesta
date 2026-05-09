#include "NavigationWidget/navigationWidgetFactory.h"

#include <extensionsystem/iplugin.h>

#include "WebView/webViewRegister.hpp"

using namespace Core;

namespace QSiesta::Internal {

class QSiestaPlugin final : public ExtensionSystem::IPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QSiesta.json")

public:
    QSiestaPlugin() = default;
    ~QSiestaPlugin() final {}

    void initialize() final {
        webViewRegister::registerPlatformType();
        m_factory = std::make_unique<NavigationWidgetFactory>();
    }

    void extensionsInitialized() final {}

    ShutdownFlag aboutToShutdown() final {
        return SynchronousShutdown;
    }

private:
    std::unique_ptr<NavigationWidgetFactory> m_factory;
};

} // namespace QSiesta::Internal

#include <qsiesta.moc>

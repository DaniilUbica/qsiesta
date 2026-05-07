#include "NavigationWidget/navigationWidgetFactory.h"

#include <extensionsystem/iplugin.h>

#include <QtWebEngineQuick/QtWebEngineQuick>

using namespace Core;

namespace Procrastination::Internal {

class ProcrastinationPlugin final : public ExtensionSystem::IPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Procrastination.json")

public:
    ProcrastinationPlugin() = default;

    ~ProcrastinationPlugin() final {}

    void initialize() final {
        QtWebEngineQuick::initialize();

        const auto factory = new NavigationWidgetFactory();
    }

    void extensionsInitialized() final {

    }

    ShutdownFlag aboutToShutdown() final {
        return SynchronousShutdown;
    }

private:
    std::unique_ptr<NavigationWidgetFactory> m_factory;
};

} // namespace Procrastination::Internal

#include <procrastination.moc>

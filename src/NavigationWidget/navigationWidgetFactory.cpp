#include "navigationWidgetFactory.h"

#include "procrastinationTr.h"
#include "procrastinationConstants.h"
#include "navigationWidget.h"

namespace Procrastination::Internal {

NavigationWidgetFactory::NavigationWidgetFactory() {
    setDisplayName(Tr::tr(Constants::PLUGIN_ID));
    setPriority(500);
    setId(Constants::PLUGIN_ID);
}

Core::NavigationView NavigationWidgetFactory::createWidget() {
    return { new NavigationWidget, {} };
}

} // namespace Procrastination::Internal

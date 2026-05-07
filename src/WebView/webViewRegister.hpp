#ifdef __APPLE__
    #include "WebView/macOS/webView.h"
#else
    #include "WebView/webViewBase.h"
#endif

#include "procrastinationConstants.h"

namespace Procrastination::Internal {
namespace webViewRegister {

    static void registerPlatformType() {
        #ifdef __APPLE__
            qmlRegisterType<WebView>(Constants::PLUGIN_ID, 1, 0, "WebView");
        #else
            qmlRegisterType<WebViewBase>("Procrastination", 1, 0, "WebView");
        #endif
    }

}
}
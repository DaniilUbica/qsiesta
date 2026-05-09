#ifdef __APPLE__
    #include "macOS/webView.h"
#endif

namespace Procrastination::Internal {
namespace webViewRegister {

    static void registerPlatformType() {
        #ifdef __APPLE__
            qmlRegisterType<WebView>("procrastination.plugin.types", 1, 0, "WKWebView");
        #endif
    }

}
}
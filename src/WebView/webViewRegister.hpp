#ifdef __APPLE__
    #include "macOS/webView.h"
#endif

namespace QSiesta::Internal {
namespace webViewRegister {

    static void registerPlatformType() {
        #ifdef __APPLE__
            qmlRegisterType<WebView>("qsiesta.plugin.types", 1, 0, "WKWebView");
        #endif
    }

}
}
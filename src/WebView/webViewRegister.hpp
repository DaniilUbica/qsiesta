#ifdef __APPLE__
    #include "WebView/macOS/webView.h"
#else
    #include "WebView/webViewBase.h"
#endif

namespace Procrastination::Internal {
namespace webViewRegister {

    static void registerPlatformType() {
        #ifdef __APPLE__
            qmlRegisterType<WebView>("procrastination.plugin.types", 1, 0, "WebView");
        #else
            qmlRegisterType<WebViewBase>("procrastination.plugin.types", 1, 0, "WebView");
        #endif
    }

}
}
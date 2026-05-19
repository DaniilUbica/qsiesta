#ifdef __APPLE__
    #include "macOS/webView.h"
#elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
    #include <QtWebEngineQuick/QtWebEngineQuick>
#endif

namespace QSiesta::Internal {
namespace webViewRegister {

    static void registerPlatformType() {
        #ifdef __APPLE__
            qmlRegisterType<WebView>("qsiesta.plugin.types", 1, 0, "WKWebView");
        #elif defined(Q_OS_LINUX) || defined(Q_OS_WIN)
            QtWebEngineQuick::initialize();
        #endif
    }

}
}

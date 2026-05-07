import QtQuick

import "views"

Item {
    id: root

    QMWebView {
        id: webView
        anchors.fill: parent
        url: "https://www.tiktok.com/login"
    }
}

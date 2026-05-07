#pragma once

#include "WebView/webViewBase.h"

namespace Procrastination::Internal {

class WebView : public WebViewBase {
    Q_OBJECT

public:
    explicit WebView(QQuickItem *parent = nullptr);
    ~WebView();

    void setUrl(const QUrl &url) override;

private:
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void itemChange(ItemChange change, const ItemChangeData &data) override;

    void attachToWindow();
    void updateFrame();

    class Private;
    std::unique_ptr<Private> d;

    QUrl m_url;
};

} // namespace Procrastination::Internal

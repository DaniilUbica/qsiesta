#pragma once

#include <QQuickItem>

namespace Procrastination::Internal {

class WebView : public QQuickItem {
    Q_OBJECT

public:
    explicit WebView(QQuickItem* parent = nullptr);
    ~WebView();

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    QUrl url() const { return m_url; };
    virtual void setUrl(const QUrl& url);
    Q_SIGNAL void urlChanged(const QUrl& url);

private:
    void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;
    void itemChange(ItemChange change, const ItemChangeData& data) override;

    void attachToWindow();
    void updateFrame();

    class Private;
    std::unique_ptr<Private> d;

    QUrl m_url;
};

} // namespace Procrastination::Internal

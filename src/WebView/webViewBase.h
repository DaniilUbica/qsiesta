#pragma once

#include <QQuickItem>
#include <QUrl>

namespace Procrastination::Internal {

class WebViewBase : public QQuickItem {
    Q_OBJECT

public:
    explicit WebViewBase(QQuickItem* parent = nullptr);
    ~WebViewBase();

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    QUrl url() const { return m_url; };
    virtual void setUrl(const QUrl& url);
    Q_SIGNAL void urlChanged(const QUrl& url);

protected:
    virtual void geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) override;
    virtual void itemChange(ItemChange change, const ItemChangeData& data) override;

    QUrl m_url;
};

} // namespace Procrastination::Internal

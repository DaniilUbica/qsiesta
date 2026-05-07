#include "webViewBase.h"

using namespace Procrastination::Internal;

WebViewBase::WebViewBase(QQuickItem* parent) : QQuickItem(parent) {}

WebViewBase::~WebViewBase() {}

void WebViewBase::setUrl(const QUrl& url) {
    if (m_url != url) {
        m_url = url;
        Q_EMIT urlChanged(m_url);
    }
}

void WebViewBase::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) {
    QQuickItem::geometryChange(newGeometry, oldGeometry);
}

void WebViewBase::itemChange(ItemChange change, const ItemChangeData& data) {
    QQuickItem::itemChange(change, data);
}
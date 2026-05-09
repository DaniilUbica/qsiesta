#import <WebKit/WebKit.h>
#import <AppKit/AppKit.h>

#include "webView.h"

#include <QQuickWindow>

namespace Procrastination::Internal {

class WebView::Private {
public:
    ~Private() {
        if (wkView) {
            [wkView removeFromSuperview];
            [wkView release];
            wkView = nullptr;
        }
    }

    WKWebView* wkView = nil;
};

WebView::WebView(QQuickItem* parent) : WebViewBase(parent) {
    setFlag(ItemHasContents, false);

    d = std::make_unique<WebView::Private>();

    WKWebViewConfiguration* config = [[WKWebViewConfiguration alloc] init];
    config.mediaTypesRequiringUserActionForPlayback = WKAudiovisualMediaTypeNone;
    config.websiteDataStore = [WKWebsiteDataStore defaultDataStore];

    d->wkView = [[WKWebView alloc] initWithFrame:NSZeroRect configuration:config];
    d->wkView.hidden = YES;

    connect(this, &QQuickItem::windowChanged, this, &WebView::attachToWindow);
}

WebView::~WebView() {
    disconnect(this, &QQuickItem::windowChanged, this, &WebView::attachToWindow);
    if (d->wkView) {
        [d->wkView removeFromSuperview];
        d->wkView = nil;
    }
}

void WebView::setUrl(const QUrl& url) {
    qDebug() << "setUrl" << url;
    WebViewBase::setUrl(url);

    if (!d->wkView) {
        return;
    }

    NSURL* nsUrl = [NSURL URLWithString:url.toString().toNSString()];
    [d->wkView loadRequest:[NSURLRequest requestWithURL:nsUrl]];
}

void WebView::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) {
    WebViewBase::geometryChange(newGeometry, oldGeometry);
    updateFrame();
}

void WebView::itemChange(ItemChange change, const ItemChangeData& data) {
    WebViewBase::itemChange(change, data);
    if (change == ItemSceneChange || change == ItemVisibleHasChanged) {
        attachToWindow();
    }
}

void WebView::attachToWindow() {
    if (!d->wkView || !window()) {
        return;
    }

    NSView* hostView = (__bridge NSView *)reinterpret_cast<void *>(window()->winId());
    if (!hostView) {
        return;
    }

    if (d->wkView.superview != hostView) {
        [d->wkView removeFromSuperview];
        [hostView addSubview:d->wkView];
    }

    d->wkView.hidden = !isVisible();
    updateFrame();

    if (!m_url.isEmpty() && d->wkView.URL == nil) {
        setUrl(m_url);
    }
}

void WebView::updateFrame() {
    if (!d->wkView || !window()) {
        return;
    }

    NSView* hostView = (__bridge NSView *)reinterpret_cast<void *>(window()->winId());
    if (!hostView) {
        return;
    }

    QPointF scenePos = mapToScene(QPointF(0, 0));
    CGFloat hostHeight = hostView.bounds.size.height;

    d->wkView.frame = NSMakeRect(
        scenePos.x(),
        hostHeight - scenePos.y() - height(),
        width(),
        height()
    );
    d->wkView.hidden = !isVisible();
}

} // namespace Procrastination::Internal

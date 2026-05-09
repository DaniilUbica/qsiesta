#import <WebKit/WebKit.h>
#import <AppKit/AppKit.h>

#include "webView.h"

#include <QQuickWindow>

namespace QSiesta::Internal {

class WebView::Private {
public:
    Private() {
        WKWebViewConfiguration* config = [[WKWebViewConfiguration alloc] init];
        config.mediaTypesRequiringUserActionForPlayback = WKAudiovisualMediaTypeNone;
        config.websiteDataStore = [WKWebsiteDataStore defaultDataStore];

        wkView = [[WKWebView alloc] initWithFrame:NSZeroRect configuration:config];
        wkView.hidden = YES;
    }

    ~Private() {
        if (wkView) {
            [wkView removeFromSuperview];
            [wkView release];
            wkView = nil;
        }
    }

    WKWebView* wkView = nil;
};

WebView::WebView(QQuickItem* parent) : QQuickItem(parent) {
    setFlag(ItemHasContents, false);

    d = std::make_unique<WebView::Private>();

    connect(this, &QQuickItem::windowChanged, this, [this](QQuickWindow* win) {
        if (win) {
            attachToWindow();
        }
    });
}

WebView::~WebView() {}

void WebView::setUrl(const QUrl& url) {
    if (!d->wkView || m_url == url) {
        return;
    }

    m_url = url;
    Q_EMIT urlChanged(m_url);

    NSURL* nsUrl = [NSURL URLWithString:url.toString().toNSString()];
    [d->wkView loadRequest:[NSURLRequest requestWithURL:nsUrl]];
}

void WebView::geometryChange(const QRectF& newGeometry, const QRectF& oldGeometry) {
    QQuickItem::geometryChange(newGeometry, oldGeometry);
    updateFrame();
}

void WebView::itemChange(ItemChange change, const ItemChangeData& data) {
    QQuickItem::itemChange(change, data);

    if (change == ItemSceneChange) {
        if (window()) {
            attachToWindow();
        }
        else if (d->wkView) {
            [d->wkView removeFromSuperview];
            d->wkView.hidden = YES;
        }
    }
    else if (change == ItemVisibleHasChanged) {
        if (window()) {
            attachToWindow();
        }
    }
}

void WebView::attachToWindow() {
    if (!d->wkView || !window()) {
        return;
    }

    NSView* hostView = (__bridge NSView *)reinterpret_cast<void*>(window()->winId());
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

    NSView* hostView = (__bridge NSView *)reinterpret_cast<void*>(window()->winId());
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

} // namespace QSiesta::Internal

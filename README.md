# QSiesta

## A plugin for Qt Creator to relax from coding

Because every build deserves a little siesta.

---

### Preview

![QSiesta preview](.github/imgs/preview.gif)

---

### What is it?

QSiesta embeds a web browser and mini-games directly into Qt Creator's navigation panel — right where your file tree usually lives. While your project compiles, you don't have to alt-tab anywhere. Just lean back, scroll TikTok, and pretend you're thinking about architecture.

---

### Why?

Build times happen. Code reviews drag on. CI pipelines do whatever CI pipelines do. QSiesta turns that dead time into something enjoyable without making you leave the IDE.

---

### What's available now

- **TikTok** — native macOS WKWebView on macOS, Qt WebEngine on other platforms

---

### What's coming

- Different games
- More social feeds and time sinks, curated for maximum productivity loss  

---

### Installation

Download the latest release for your platform from the [Releases](https://github.com/DaniilUbica/qsiesta/releases) page and place the plugin into your Qt Creator plugins directory:

- **macOS:** `~/Library/Application Support/QtProject/QtCreator/plugins/<qt-version>/`
- **Linux:** `~/.local/share/data/QtProject/QtCreator/plugins/<qt-version>/`
- **Windows:** `%APPDATA%\QtProject\QtCreator\plugins\<qt-version>\`

Restart Qt Creator, enable **QSiesta** in *Help → About Plugins*, restart again.

---

### Building from source

Requires Qt Creator and Qt 6.8+.

Copy `CMakeUserPresets.json.example` to `CMakeUserPresets.json`, fill in your local paths, then:

```bash
cmake --preset local
cmake --build build/local
```

---

### Supported Qt Creator versions

Only Qt Creator 19.0.0 supported at the moment

---

### License

MIT
# QSiesta

## A plugin for Qt Creator to relax from coding

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

- **TikTok** — native macOS WKWebView (macOS only)
- **Snake** — mini-game available on all platforms

> **Note:** Web view (TikTok and other feeds) is currently only supported on macOS. On Linux and Windows the panel will show a "not supported" placeholder. Support for other platforms is planned.

---

### What's coming

- Different games
- More social feeds and time sinks, curated for maximum productivity loss  

---

### Installation

Download the latest release for your platform from the [Releases](https://github.com/DaniilUbica/qsiesta/releases) page.

#### 1. Find your Qt Creator installation directory

| Platform | Typical path |
|----------|-------------|
| macOS | `/Applications/Qt Creator.app/Contents` |
| Linux | `~/Qt/Tools/QtCreator` |
| Windows | `C:\Qt\Tools\QtCreator` |

#### 2. Extract the archive

Extract the downloaded `.7z` **directly into the Qt Creator installation directory** — the archive mirrors Qt Creator's folder structure, so all files land in the right places automatically.

**macOS:**
```bash
cd /Applications/Qt\ Creator.app/Contents
7z x QSiesta-19.0.0-macOS-universal.7z
```

**Linux:**
```bash
cd ~/Qt/Tools/QtCreator
7z x QSiesta-19.0.0-Linux-x64.7z
```

**Windows** (PowerShell):
```powershell
cd "C:\Qt\Tools\QtCreator"
7z x QSiesta-19.0.0-Windows-x64.7z
```

#### 3. Enable the plugin

Restart Qt Creator, open **Help → About Plugins**, find **QSiesta** in the list, check it, and restart once more.

#### 4. Open the panel

The plugin appears in the left navigation panel. Click the panel selector icon and choose **QSiesta**.

---

### Building from source

Requires Qt Creator and Qt 6.8+.

Copy `CMakeUserPresets.json.example` to `CMakeUserPresets.json`, fill in your local paths, then:

```bash
cmake --preset local
cmake --build build/local
```

---

### Adding a mini-game

See [src/MiniGames/README.md](src/MiniGames/README.md) for the architecture overview and a step-by-step guide to adding a new game. In short: implement `GameManagerBase` and add one line to `miniGameRegister.hpp` — nothing else needs to change.

---

### Supported Qt Creator versions

Only Qt Creator 19.0.0 supported at the moment

---

### License

MIT

# 🚀 Console Logger (C++)

A lightweight asynchronous console logger for C++ with colored output.

---

## 📌 Overview

`ConsoleLogger` is a simple thread-safe logging library for C++.

You just call `log()`, and the logger takes care of everything else —  
queueing, formatting, and printing messages in a separate thread.

---

## ✨ Features

- 🧵 Asynchronous logging (worker thread)
- 📥 Thread-safe message queue
- 🎨 Colored output (ANSI escape codes)
- ⏱️ Timestamp formatting
- ⚡ Minimal API (just one method)

---

## 🖼️ Example Output

![Example](assets/example.png)

---

## 🛠️ Installation

```bash
git clone https://github.com/alt-enterssx/console_logger.git
cd console_logger
mkdir build && cd build
cmake ..
make
```

## ⚙️ How It Works
`log() → queue → worker thread → console output`

## 📊 Log Types
```cpp
enum LogType {
    WARGNING,
    DEBUG,
    INFO,
    ERROR,
    CRITICAL
};
```

# synk
`synk` is a peer-to-peer file synchronication tool written in modern C++.

Inspired by the open-source [Syncthing](syncthing.net) project, this tool is being built from scratch to explore systems-level networking, file-monitoring, and performant sync architecture

The focus of this project is on minimalism, speed, and reliability - using modern C++ features and minimal outside dependencies.



## Planned Features
- Per-file content hashing (SHA-256) to detect changes
- Incremental sync with change detection (OS event monitoring or polling)
- Bi-directional synchronization over TCP/UDP
- File conflict detection and resolution
- Optional: encrypted file transfer
- Optional: modern terminal UI (TUI) for usability
- Optional: peer discovery via UDP broadcast or mDNS
- Optional: config file support for custom sync paths and intervals



## Features (Completed)
- Recursive directory scanning via `std::filesystem`



## Build Instructions

### Requirements
- Linux Operating System 
    - (Windows support coming soon)
- C++20 compatible compiler
- CMake 3.15+

### Building from Source

```bash
git clone https://github.com/DanielC5/synk

cd synk

mkdir build && cd build

cmake ..

make

./synk
```
# xv6 Virtual Framebuffer
**Course:** Operating System
**Group:** 02  
**Semester:** 2025.2

A simple **virtual framebuffer implementation for xv6-riscv**, exposing a framebuffer device (`/dev/fb`) that allows user programs to draw text-based graphics using standard file I/O.

---

## Features

- Virtual framebuffer implemented in the xv6 kernel
- Exposed as a character device: `/dev/fb`
- Framebuffer size: **40 × 15 (ASCII characters)**
- User programs draw by writing directly to the device
- Demo program with simple animation

---

## How It Works

- The framebuffer is a kernel-resident memory buffer
- Registered as a device via `devsw[]`
- Uses a custom major number (`3`)
- User–kernel data transfer via `either_copyin()` / `either_copyout()`
- No graphics hardware required (software-only)

---

## Project Structure

```text
kernel/
 ├── defs.h        # Declarations
 ├── file.c        # Framebuffer device (/dev/fb)
 ├── fs.c          # Filesystem support
 └── sysfile.c     # mknod support

user/
 ├── init.c        # Create /dev and framebuffer device at boot
 ├── drawdemo.c    # Framebuffer demo (ASCII animation)
 └── mknod.c       # User-level mknod utility
```
## Build & Run
- Build xv6: make clean make qemu
- Run: drawdemo

---

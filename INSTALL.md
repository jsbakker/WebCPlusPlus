# Building and Installing webcpp

## Prerequisites

- A C++23-capable compiler: GCC 13+ or Clang 16+ (Linux), Xcode 16+ / Apple Clang 16+ (macOS)
- CMake 3.21 or later
- Git

### Installing prerequisites

**macOS**
```sh
xcode-select --install          # installs Apple Clang
brew install cmake              # if you use Homebrew
```

**Debian / Ubuntu**
```sh
sudo apt install cmake g++ git
```

**Fedora / RHEL**
```sh
sudo dnf install cmake gcc-c++ git
```

**Arch**
```sh
sudo pacman -S cmake gcc git
```

---

## 1. Clone the repository

```sh
git clone https://github.com/jeffreybakker/webcpp.git
cd webcpp
```

---

## 2. Configure

Run CMake from the repository root to generate the build system in a `build/`
subdirectory.  Supply `-DCMAKE_INSTALL_PREFIX` to choose where webcpp will be
installed (defaults to `/usr/local`).

```sh
cmake -B build
```

To install into a custom prefix (e.g. `~/.local` for a single-user install):

```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local
```

To build an optimised release binary explicitly:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
```

---

## 3. Build

```sh
cmake --build build
```

To speed things up on a multi-core machine, pass a job count:

```sh
cmake --build build --parallel
```

---

## 4. Install

```sh
cmake --install build
```

If you are installing to a system prefix such as `/usr/local`, `sudo` is
required:

```sh
sudo cmake --install build
```

### What gets installed

| Path | Contents |
|---|---|
| `<prefix>/bin/webcpp` | The webcpp command-line binary |
| `<prefix>/share/webcpp/themes/` | 59 colour-scheme files (`.Scs2`) |
| `<prefix>/share/doc/webcpp/docs.html` | HTML user manual |

---

## 5. Verify

```sh
webcpp
webcpp --languages
```

If the binary is not on your `PATH` after a custom-prefix install, add the
`bin` directory:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

---

## Uninstalling

CMake does not provide an uninstall target by default. To remove the files
that were installed, use the manifest generated during installation:

```sh
sudo xargs rm -f < build/install_manifest.txt
```

Then remove the data directories:

```sh
sudo rm -rf <prefix>/share/webcpp
sudo rm -rf <prefix>/share/doc/webcpp
```

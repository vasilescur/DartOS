# DartOS

DartOS is a toy operating system supposedly built on Google's Dart language but actually built in assembly and C.

## Requirements

- [QEMU](https://www.qemu.org/)
- `gcc` and the GNU binutils
- `make`

## Usage

To run this program in the `qemu` emulator, simply run

```bash
make run
```

### Building on MacOS

Mac comes with a fake version of GCC binutils, including a stripped down version of `ld` which does not support all the options needed to build this project. My workaround was to create an Ubuntu virtual machine with an `sshfs` shared directory, and `ssh` into the Ubuntu machine in order to build the project.

It is a futile effort to attempt to install the real `gcc` and binutils on a Mac; 6 hours have been wasted with this endeavor. Please update this number after you invaraibly reach the same conclusion.

# m5stack-core2-template

esp-idf build system template for M5Stack Core2.

## Require

Toolchain Setup

- [Standard Setup of Toolchain for Windows](https://docs.espressif.com/projects/esp-idf/en/v3.3.4/get-started/windows-setup.html#toolchain-setup)
- [Standard Setup of Toolchain for Linux](https://docs.espressif.com/projects/esp-idf/en/v3.3.4/get-started/linux-setup.html)
- [Standard Setup of Toolchain for Mac OS](https://docs.espressif.com/projects/esp-idf/en/v3.3.4/get-started/macos-setup.html)

```
$ xtensa-esp32-elf-gcc -v
gcc version 5.2.0 (crosstool-NG crosstool-ng-1.22.0-96-g2852398)
```

## Build

![](./workflows/Build/badge.svg)

Project setup

```
# clone repository (REQUIRED: --recursive)
git clone --recursive https://github.com/h1romas4/m5stack-core2-template
cd m5stack-core2-template
# This repository includes eps-idf
export IDF_PATH=$(pwd)/esp-idf
# Pyhton library setup for esp-idf dependencies
python -m pip install --user -r $IDF_PATH/requirements.txt
# setting your serial port
# -> Serial flasher config
make menuconfig
```

Build and flash

```
# This repository includes eps-idf
export IDF_PATH=$(pwd)/esp-idf
# build
make -j4
# flash
make flash
```

## Binary release

Extract [release.tar.gz](./releases) and Assign the binary to the following address:

|address|module|
|-|-|
|`0x1000`|`build/bootloader/bootloader.bin`|
|`0x8000`|`build/default.bin`|
|`0xe000`|`build/ota_data_initial.bin`|
|`0x10000`|`build/m5stack-core2-app.bin`|

```
python ${IDF_PATH}/components/esptool_py/esptool/esptool.py \
    --chip esp32 \
    --port <SET IT TO YOUR COM PORT> \
    --baud 921600 \
    --before default_reset \
    --after hard_reset write_flash -z \
    --flash_mode dio --flash_freq 80m \
    --flash_size detect \
    0x1000 ./build/bootloader/bootloader.bin \
    0x8000 ./build/default.bin \
    0xe000 ./build/ota_data_initial.bin \
    0x10000 ./build/m5stack-core2-app.bin
```

## Dependencies

|name|version|hash|
|-|-|-|
|[esp-idf](https://github.com/espressif/esp-idf)|3.3.4|`b64b375`|
|[arduino-esp32](https://github.com/espressif/arduino-esp32)|latest|`28a8073`|
|[M5Core2](https://github.com/m5stack/M5Core2)|latest|`cc551d4`|

## Note

### Visual Studio Code (C/C++ Extention) settings

Change xtensa-esp32-elf-gcc path

```
$ which xtensa-esp32-elf-gcc
/home/hiromasa/devel/toolchain/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
```

`.vscode/c_cpp_properties.json`
```
{
  "configurations": [
    {
      "compilerPath": "~/devel/toolchain/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc",
    }
  ],
  "version": 4
}
```

Set to VSCode internal terminal for MSYS2/Windows

`.vscode/settings.json`
```
{
    "terminal.integrated.shell.windows": "C:\\develop\\esp\\msys32\\usr\\bin\\bash.exe",
    "terminal.integrated.env.windows": {
        "MSYSTEM": "MINGW32",
        "CHERE_INVOKING": "1"
    },
    "terminal.integrated.shellArgs.windows": [
        "--login"
    ],
    "C_Cpp.intelliSenseEngine": "Default"
}
```

### How to create this repository?

```
# init repository
mkdir m5stack-core2-template
cd m5stack-core2-template
git init
# add esp-idf
git submodule add https://github.com/espressif/esp-idf.git esp-idf
cd esp-idf
git checkout b64b375
git submodule update --init --recursive
# add arduino-esp32
cd ../
mkdir components
cd components
git submodule add https://github.com/espressif/arduino-esp32 arduino
cd arduino
git checkout 28a807306915d68aa584300c91f431a6af22c037
git submodule update --init --recursive
# add M5Core2
cd ../
mkdir m5stack
cd m5stack
git submodule add https://github.com/m5stack/M5Core2 M5Core2
cd M5Core2
git checkout cc551d4fec4dd8f1586dd954003106766bb0efec
```

and add file..

```
components/m5stack/component.mk
main/component.mk
main/main.cpp
Makefile
sdkconfig
```

`components/m5stack/component.mk`
```
#
# Main Makefile. This is basically the same as a component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_SRCDIRS := M5Core2/src M5Core2/src/utility M5Core2/src/Fonts
COMPONENT_ADD_INCLUDEDIRS := M5Core2/src M5Core2/src/Fonts M5Core2/src/Fonts/Custom M5Core2/src/Fonts/GFXFF

CPPFLAGS += -Wno-missing-field-initializers

M5Core2/src/AXP192.o: CPPFLAGS += -Wno-maybe-uninitialized
```

optional files..

```
.github/workflows/m5stack.yml
.vscode/c_cpp_properties.json
.vscode/extensions.json
.gitignore
.editorconfig
```

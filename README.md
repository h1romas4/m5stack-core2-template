# m5stack-core2-template

esp-idf build system template for M5Stack Core2.

## Build

```
git clone --recursive https://github.com/h1romas4/m5stack-core2-template
cd m5stack-core2-template
# This repository includes eps-idf
export IDF_PATH=$(pwd)/esp-idf
# build
make -j4
# setting your serial port
#  Serial flasher config 
make menuconfig
# flash
make menuconfig
```

## Dependencies

|name|version|hash|
|-|-|-|
|[esp-idf](https://github.com/espressif/esp-idf)|3.3.4|`b64b375`|
|[arduino-esp32](https://github.com/espressif/arduino-esp32)|latest|`28a8073`|
|[M5Core2](https://github.com/m5stack/M5Core2)|latest|`cc551d4`|

## How to create this repository

```
# init repository
mkdir m5stack-core2-template
cd m5stack-core2-template
git init
# add esp-idf
git submodule add https://github.com/espressif/esp-idf.git esp-idf
cd esp-idf
git checkout  b64b375
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
.github/workflows/m5stack
.vscode/c_cpp_properties.json
.vscode/extensions.json
.gitignore
```

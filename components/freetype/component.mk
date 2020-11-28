#
# Main Makefile. This is basically the same as a component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_OBJS := \
    M5EPD/src/ffsupport.o \
    M5EPD/src/font_render.o \
    M5EPD/src/base/basepic.o \
    M5EPD/src/base/ftadvanc.o \
    M5EPD/src/base/ftapi.o \
    M5EPD/src/base/ftbase.o \
    M5EPD/src/base/ftbbox.o \
    M5EPD/src/base/ftbitmap.o \
    M5EPD/src/base/ftcalc.o \
    M5EPD/src/base/ftdbgmem.o \
    M5EPD/src/base/ftdebug.o \
    M5EPD/src/base/ftfstype.o \
    M5EPD/src/base/ftgasp.o \
    M5EPD/src/base/ftgloadr.o \
    M5EPD/src/base/ftglyph.o \
    M5EPD/src/base/ftgxval.o \
    M5EPD/src/base/ftinit.o \
    M5EPD/src/base/ftobjs.o \
    M5EPD/src/base/ftoutln.o \
    M5EPD/src/base/ftpic.o \
    M5EPD/src/base/ftrfork.o \
    M5EPD/src/base/ftsnames.o \
    M5EPD/src/base/ftstream.o \
    M5EPD/src/base/ftsystem.o \
    M5EPD/src/base/fttrigon.o \
    M5EPD/src/base/ftutil.o \
    M5EPD/src/base/md5.o \
    M5EPD/src/sfnt/sfdriver.o \
    M5EPD/src/sfnt/sfnt.o \
    M5EPD/src/sfnt/sfntpic.o \
    M5EPD/src/sfnt/sfobjs.o \
    M5EPD/src/sfnt/ttbdf.o \
    M5EPD/src/sfnt/ttcmap.o \
    M5EPD/src/sfnt/ttkern.o \
    M5EPD/src/sfnt/ttload.o \
    M5EPD/src/sfnt/ttmtx.o \
    M5EPD/src/sfnt/ttpost.o \
    M5EPD/src/sfnt/ttsbit.o \
    M5EPD/src/sfnt/ttsbit0.o \
    M5EPD/src/smooth/ftgrays.o \
    M5EPD/src/smooth/ftsmooth.o \
    M5EPD/src/smooth/ftspic.o \
    M5EPD/src/smooth/smooth.o \
    M5EPD/src/truetype/truetype.o \
    M5EPD/src/truetype/ttdriver.o \
    M5EPD/src/truetype/ttgload.o \
    M5EPD/src/truetype/ttinterp.o \
    M5EPD/src/truetype/ttobjs.o \
    M5EPD/src/truetype/ttpic.o \
    M5EPD/src/truetype/ttpload.o \
    M5EPD/src/truetype/ttsubpix.o
COMPONENT_SRCDIRS := \
    M5EPD/src \
    M5EPD/src/base \
    M5EPD/src/freetype \
    M5EPD/src/sfnt \
    M5EPD/src/smooth \
    M5EPD/src/truetype
COMPONENT_ADD_INCLUDEDIRS := \
    M5EPD/src \
    M5EPD/src/base \
    M5EPD/src/base/config \
    M5EPD/src/base/internal \
    M5EPD/src/base/services \
    M5EPD/src/freetype \
    M5EPD/src/sfnt \
    M5EPD/src/smooth \
    M5EPD/src/truetype

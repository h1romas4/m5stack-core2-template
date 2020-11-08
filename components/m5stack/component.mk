#
# Main Makefile. This is basically the same as a component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_SRCDIRS := M5Core2/src M5Core2/src/utility M5Core2/src/Fonts
COMPONENT_ADD_INCLUDEDIRS := M5Core2/src M5Core2/src/Fonts M5Core2/src/Fonts/Custom M5Core2/src/Fonts/GFXFF

CPPFLAGS += -Wno-missing-field-initializers

M5Core2/src/AXP192.o: CPPFLAGS += -Wno-maybe-uninitialized

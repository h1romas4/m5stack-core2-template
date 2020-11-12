#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

# for components/m5stack/M5Core2/src/Fonts/*.h
CPPFLAGS += -Wno-missing-field-initializers

# ----------------------------
# Makefile Options
# ----------------------------

NAME = Fire
ICON = icon.png
DESCRIPTION = "A port of Fire for the TI-84 CE"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)

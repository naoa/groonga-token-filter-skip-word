AM_CFLAGS =					\
	$(GROONGA_CFLAGS)

AM_LDFLAGS =					\
	-avoid-version				\
	-module					\
	-no-undefined

LIBS =						\
	$(GROONGA_LIBS)

token_filters_plugins_LTLIBRARIES =
token_filters_plugins_LTLIBRARIES += skip_word.la 

token_filters_plugins_SOURCE =			\
	skip_word.c

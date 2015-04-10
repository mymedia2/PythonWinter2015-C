cdef extern from "ftw.h":
#	ctypedef struct wordexp_t:
#		size_t we_wordc
#		char **we_wordv
#		size_t we_offs

	int ftw(const char* dir, int (*fn)(const char* file, const void* sb, int flag), int nopenfd); 

cimport ftw_h

__doc__ = "Primitive ftw.h wrapper"

__func = None

#TODO: документировать класс
class BlockError(RuntimeError): pass

cdef int fn_wrapper(const char* file, const void* sb, int flag):
	global __func, __err

	try:
		res = __func(file, flag)
		return res if res is not None else 0
	except Exception as e:
		__err = e
		return 42

def ftw(char* dir, fn, int nopenfd):
	# TODO: доделать строчку
	"ftw(dir, fn, nopenfd)\n\nqwerty"
	global __func, __err

	if __func: raise BlockError("ftw already running")
	__func = fn
	__err = None
	res = ftw_h.ftw(dir, fn_wrapper, nopenfd)
	__func = None
	if __err: raise __err
	return res

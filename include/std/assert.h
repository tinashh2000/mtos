#ifdef NDEBUG
	  #define assert(expression) ((void)0)
#else
	
#define assert(expression) (void)(                                                       \
            (!!(expression)) ||                                                              \
            (fprintf(stderr,"Assertion failed on expression %s in file %s on line %i",#expression, __FILE__, (unsigned)(__LINE__)), 0) \
        )

#endif
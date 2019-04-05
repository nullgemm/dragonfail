#include "dragonfail.h"
#include "dragonfail_private.h"
#include "dragonfail_error.h"

#ifdef DRAGONFAIL_BASIC_LOG
#include <stdio.h>
#endif

// extern
struct dgn dgn;

inline char** dgn_init()
{
	#ifndef DRAGONFAIL_SKIP
		dgn.error = DGN_OK;
		return dgn.log;
	#else
		return NULL;
	#endif
}

inline void dgn_reset()
{
	#ifndef DRAGONFAIL_SKIP
		dgn.error = DGN_OK;
	#endif
}

inline void dgn_basic_log()
{
	#ifdef DRAGONFAIL_BASIC_LOG
	#ifndef DRAGONFAIL_SKIP
		if (dgn.error < DGN_SIZE)
		{
			fprintf(stderr, "%s\n", dgn.log[dgn.error]);
		}
		else
		{
			fprintf(stderr, "%s\n", dgn.log[0]);
		}
	#endif
	#endif
}

inline void dgn_throw(enum dgn_error new_code)
{
	#ifndef DRAGONFAIL_SKIP
		dgn.error = new_code;

		#ifdef DRAGONFAIL_THROW_BASIC_LOG
		#ifdef DRAGONFAIL_BASIC_LOG
			dgn_basic_log();
		#endif
		#endif

		#ifdef DRAGONFAIL_ABORT
			abort();
		#endif
	#endif
}

inline char dgn_catch()
{
	#ifndef DRAGONFAIL_SKIP
		return (dgn.error != DGN_OK);
	#else
		return 0;
	#endif
}

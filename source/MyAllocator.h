#pragma once
#include "stdfx.h"
#include <NxUserAllocator.h>
using namespace std;
class MyAllocator : public NxUserAllocator
{
public:
	void * malloc(NxU32 size)
	{            
		return ::malloc(size);        
	}        
	void * mallocDEBUG(NxU32 size,const char *fileName, int line)
	{            
		return ::_malloc_dbg(size,_NORMAL_BLOCK, fileName, line);        
	}        
	void * realloc(void * memory, NxU32 size)        
	{            
		return ::realloc(memory,size);        
	}        
	void free(void * memory)        
	{            
		::free(memory);        
	}    
} ;

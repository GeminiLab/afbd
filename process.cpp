#include "process.h"


process::process()
{
	begin = new instruction();
}


process::~process()
{
	delete begin;
}

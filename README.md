# A simple logging library written for C in stb style
### Usage:
```c
#define CLOGGER_IMPLEMENTATION  
#include "clogger.h"  
int main(){  
	clogger_init("logs.log");
	
	LOG_ERROR("This is an error (%s)", "More Info");
	flush_queue();
	
	clogger_quit();
	return 0;
}
```
### Available levels
```c
LOG_FATAL("Message");
LOG_ERROR("Message");
LOG_WARN("Message");
LOG_INFO("Message");
LOG_DEBUG("Message");
LOG_TRACE("Message");
```
```
[2021-09-09 13:00:20][FTL]: Message
[2021-09-09 13:00:20][ERR]: Message
[2021-09-09 13:00:20][WAR]: Message
[2021-09-09 13:00:20][INF]: Message
[2021-09-09 13:00:20][DBG]: Message
[2021-09-09 13:00:20][TRC]: Message
```

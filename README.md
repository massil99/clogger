# A simple logging library written for C in stb style

### Usage:
```c
#define CLOGGER_IMPLEMENTATION  
#include "clogger.h"  
int main(){  
	clogger_init();
	
	LOG_ERROR("This is an error (%s)", "More Info");
	flush_queue();
	
	clogger_quit();
	return 0;
}
```
### Available levels
```c
LOG_FATAL("Message")
LOG_ERROR("Message")
LOG_WARN("Message")
LOG_INFO("Message")
LOG_DEBUG("Message")
LOG_TRACE("Message")
```
```{css, echo=FALSE}
.watch-out {
  background-color: lightpink;
  border: 3px solid red;
  font-weight: bold;
}
```
```{r class.source="watch-out"}
[2021-09-09 13:00:20][FTL]: main.c Message
[2021-09-09 13:00:20][ERR]: main.c Message
[2021-09-09 13:00:20][WAR]: main.c Message
[2021-09-09 13:00:20][INF]: main.c Message
[2021-09-09 13:00:20][DBG]: main.c Message
[2021-09-09 13:00:20][TRC]: main.c Message
```

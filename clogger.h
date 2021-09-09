#ifndef CLOGGER_H_
#define CLOGGER_H_

#define FATAL_PREFIX "\033[1;31m[FTL]: \033[0m"
#define ERROR_PREFIX "\033[1;31m[ERR]: \033[0m"
#define WARN_PREFIX  "\033[1;33m[WAR]: \033[0m"
#define INFO_PREFIX  "\033[1;37m[INF]: \033[0m"
#define DEBUG_PREFIX "\033[1;36m[DBG]: \033[0m"
#define TRACE_PREFIX "\033[1;35m[TRC]: \033[0m"
#define GRAY_TEXT(m)\
	 "\033[1;90m"m"\033[1;0m "

#define LOG_FATAL(m, ...)\
	queue_up(FATAL_PREFIX GRAY_TEXT(__FILE__) m,  ##__VA_ARGS__)
#define LOG_ERROR(m, ...)\
	queue_up(ERROR_PREFIX GRAY_TEXT(__FILE__) m, ##__VA_ARGS__)
#define LOG_WARN(m, ...)\
	queue_up(WARN_PREFIX GRAY_TEXT(__FILE__) m, ##__VA_ARGS__)
#define LOG_INFO(m, ...)\
	queue_up(INFO_PREFIX GRAY_TEXT(__FILE__) m, ##__VA_ARGS__)
#define LOG_DEBUG(m, ...)\
	queue_up(DEBUG_PREFIX GRAY_TEXT(__FILE__) m, ##__VA_ARGS__)
#define LOG_TRACE(m, ...)\
	queue_up(TRACE_PREFIX GRAY_TEXT(__FILE__) m, ##__VA_ARGS__)

void flush_queue();
#endif //CLOGGER_H_

#ifdef CLOGGER_IMPLEMENTATION
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

struct message{
	char content[256];
	struct message* prev;
};

struct message_queue{
	struct message* first;
	struct message* last;
};
int output_file = STDOUT_FILENO;
struct message_queue q;

void clogger_init(){
	q.first = NULL;
	q.last = NULL;
}

char* get_date_time(){
	time_t rawtime = time(NULL);
    if (rawtime == -1) {
        fprintf(stderr, "The time() function failed");
		exit(1);
    }
    
    struct tm *ptm = localtime(&rawtime);
    if (ptm == NULL) {
        fprintf(stderr, "The localtime() function failed");
		exit(1);
    }
    
	char *res = malloc(sizeof(char) * 256);
    sprintf(res, "\033[1m[%04d-%02d-%02d %02d:%02d:%02d]\033[0m", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	return res;
}

void queue_up(char msg[256], ...){
	char *dt = get_date_time();
	va_list args;
	struct message* m_msg = malloc(sizeof(struct message));

	va_start(args, msg);
	strcpy(m_msg->content, strcat(dt, msg));	
	vsprintf(m_msg->content, m_msg->content, args);
	va_end(args);

	if(q.last == NULL && q.first == NULL){
		m_msg->prev = NULL;
		q.first = m_msg;
		q.last = m_msg;
	}else{
		m_msg->prev = NULL;
		q.last->prev = m_msg;
		q.last = m_msg;
	}
	free(dt);
}

struct message* dequeue(){
	struct message* l = q.first;
	if(l != NULL)
		q.first = l->prev; 
	return l;
}

void flush_queue(){
	while(q.first != NULL){
		struct message* l = dequeue();
		printf("%s\n", l->content);
		free(l);
	}
}

void clogger_quit(){
	while(q.first != NULL){
		struct message* l = dequeue();
		free(l);
	}
}

#endif //CLOGGER_IMPLEMENT

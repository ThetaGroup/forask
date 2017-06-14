#define LOG_SWITCH 0
#define LOG(f,...) {if (LOG_SWITCH) printf(f,##__VA_ARGS__);}

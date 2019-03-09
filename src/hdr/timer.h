#ifndef TIMER
#define TIMER

//FRAME_RATE = F_CPU/(TIMER2_PRESCALLER*FRAMES) - 1
#define FRAME 				50UL
#define TIMER2_PRESCALLER   1024UL
#define FRAME_RATE          F_CPU/(TIMER2_PRESCALLER*FRAME) - 1

// Индексы счётчика фреймов
#define COMMON_FRAME_CNTR	0
#define SECUNDS_FRAME_CNTR	1

//Индексы счётчика секунд
#define COMMON_SECUNDS_CNTR	0
#define MINUTES_SECUNDS_CNTR	1
#define PAUSE_SECUNDS_CNTR	2

void Init_timer(void);
void Pause_s (uint8_t secunds);

#endif
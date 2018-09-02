#ifndef TIMER
#define TIMER

//FRAME_RATE = F_CPU/(TIMER2_PRESCALLER*FRAMES) - 1
#define FRAME 				100UL
#define TIMER2_PRESCALLER   1024UL
#define FRAME_RATE          F_CPU/(TIMER2_PRESCALLER*FRAME) - 1

void Init_timer(void);
uint8_t Get_frame(void);

#endif
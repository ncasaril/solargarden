#ifndef _OLED_H
#define _OLED_H

typedef struct{
    float g;
    float l;
} solargraph_t;

class OLed {
public: 
    void displayOn(void);
    void reset_display(void);
    void displayOff(void);
    void reset(void);
    void clear();
    void clear_row(unsigned char k);
    void SendChar(unsigned char data);
    void sendCharXY(unsigned char data, int X, int Y);
    void sendcommand(unsigned char com);
    void beginDataTransaction();
    void data(unsigned char d);
    void endDataTransaction();

    void setXY(unsigned char row,unsigned char col);
    void clear_display(void);
    void sendStr(unsigned char *string);
    void sendStrXY(const char *string, int X, int Y);
    void init_OLED(void);
    void Draw_WIFI();
    void Draw_WAVES();
    void Draw_Plot(solargraph_t *slog, int fi, int maxn);
    void StartUp_OLED();

};

#endif

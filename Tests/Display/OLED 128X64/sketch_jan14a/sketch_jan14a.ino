//Include the graphics library.
#include "U8glib.h" 
//Initialize display.
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
void setup(void)
{
    //Set font.
    u8g.setFont(u8g_font_unifont);
}
void loop(void)
{
    u8g.firstPage();
    do {
        draw();
    } while (u8g.nextPage());
    //Delay before repeating the loop.
    delay(50);
}
void draw(void)
{
    //Write text. (x, y, text)
    u8g.drawStr(20, 40, "Hello World.");
}

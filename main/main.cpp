#include <M5Core2.h>
#include "ffsupport.h"
#include "font_render.h"
#include "FS.h"
#include "esp_log.h"
#include "esp_err.h"

#include "UNIT_ENV.h"
SHT3X sht30;
QMP6988 qmp6988;
float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

char str_tmp[64];
char str_hum[64];
char str_pressure[64];

static const char *TAG = "main";

static const int font_size = 22;
static const int font_cache_size = 256;

font_face_t font_face;
font_render_t font_render;

void drawFreetypeBitmap(int32_t cx, int32_t cy, uint16_t bw, uint16_t bh, uint16_t fg, uint8_t *bitmap)
{
    const uint8_t alphamap[16] = {0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255};
    M5.Lcd.startWrite();
    uint32_t pos = 0;
    uint16_t bg = 0;
    for (int y = 0; y < bh; y++) {
        for (int x = 0; x < bw; x++) {
            if (pos & 0x1) {
                M5.Lcd.drawPixel(cx + x, cy + y, M5.Lcd.alphaBlend(alphamap[bitmap[pos >> 1] & 0x0F], fg, bg));
            }
            else {
                M5.Lcd.drawPixel(cx + x, cy + y, M5.Lcd.alphaBlend(alphamap[bitmap[pos >> 1] >> 4], fg, bg));
            }
            pos++;
        }
    }
    M5.Lcd.endWrite();
}

uint16_t decodeUTF8(uint8_t *buf, uint16_t *index, uint16_t remaining)
{
    uint16_t c = buf[(*index)++];
    //
    // 7 bit Unicode
    if ((c & 0x80) == 0x00)
        return c;

    // 11 bit Unicode
    if (((c & 0xE0) == 0xC0) && (remaining > 1))
        return ((c & 0x1F) << 6) | (buf[(*index)++] & 0x3F);

    // 16 bit Unicode
    if (((c & 0xF0) == 0xE0) && (remaining > 2)) {
        c = ((c & 0x0F) << 12) | ((buf[(*index)++] & 0x3F) << 6);
        return c | ((buf[(*index)++] & 0x3F));
    }

    // 21 bit Unicode not supported so fall-back to extended ASCII
    // if ((c & 0xF8) == 0xF0) return c;

    return c; // fall-back to extended ASCII
}

void drawString(const char *string, int32_t poX, int32_t poY, uint16_t fg, font_render_t *render)
{
    int16_t sumX = 0;
    uint16_t len = strlen(string);
    uint16_t n = 0;
    uint16_t base_y = poY;

    while (n < len) {
        uint16_t uniCode = decodeUTF8((uint8_t *)string, &n, len - n);
        if (font_render_glyph(render, uniCode) != ESP_OK) {
            ESP_LOGE(TAG, "Font render faild.");
        }
        drawFreetypeBitmap(poX + render->bitmap_left, base_y - render->bitmap_top, render->bitmap_width, render->bitmap_height, fg, render->bitmap);
        poX += render->advance;
        sumX += render->advance;
    }
}

void setup()
{
    M5.begin();

    // FreeType initialize
    ffsupport_setffs(SD);
    if(font_face_init_fs(&font_face, "/M5STACK/GGOTHIC.TTF") != ESP_OK) {
        ESP_LOGE(TAG, "Font load faild.");
    }
    // Font render initialize
    if(font_render_init(&font_render, &font_face, font_size, font_cache_size) != ESP_OK) {
        ESP_LOGE(TAG, "Render creation failed.");
    }
    // Test render
    if(font_render_glyph(&font_render, 'g') != ESP_OK) {
        ESP_LOGE(TAG, "Font render faild.");
    }

    // Wire init, adding the I2C bus.
    Wire.begin(32, 33);
    if(!qmp6988.init()) {
        ESP_LOGE(TAG, "Could not find a valid qmp6988 sensor");
    }

    // Render
    drawString("M5Stack Core2 ENV.III SENSOR", 8, 22 * 2, 0xffff, &font_render);
    drawString("温度:" , 64, 22 * 5, 0xffff, &font_render);
    drawString("湿度:" , 64, 22 * 7, 0xffff, &font_render);
    drawString("気圧:" , 64, 22 * 9, 0xffff, &font_render);
}

void loop()
{
    // M5Core2
    M5.update();

    pressure = qmp6988.calcPressure() / 100;
    if(sht30.get()==0){ //Obtain the data of shT30.  获取sht30的数据
        tmp = sht30.cTemp;  //Store the temperature obtained from shT30.  将sht30获取到的温度存储
        hum = sht30.humidity; //Store the humidity obtained from the SHT30.  将sht30获取到的湿度存储
    } else {
        tmp=0,hum=0;
    }

    sprintf(str_tmp, "%2.1f 度", tmp);
    sprintf(str_hum, "%2.1f %%", hum);
    sprintf(str_pressure, "%0.2f hPa", pressure);

    drawString(str_tmp , 120, 22 * 5, 0xffff, &font_render);
    drawString(str_hum , 120, 22 * 7, 0xffff, &font_render);
    drawString(str_pressure , 120, 22 * 9, 0xffff, &font_render);

    // M5.Lcd.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%0.2f hPa\r\n", tmp, hum, pressure);

    // arduino-esp32
    delay(1000);
}

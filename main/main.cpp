#include <M5Core2.h>
#include "ffsupport.h"
#include "font_render.h"
#include "FS.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "main";

static const int font_size = 44;
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
    // Render
    drawString("M5Stack Core2", 8, 86, 0xffff, &font_render);
    drawString("TrueType", 64, 134, 0x7b3d, &font_render);
    drawString("源真ゴシック", 42, 184, 0x9665, &font_render);
}

void loop()
{
    // M5Core2
    M5.update();
    // esp-idf
    ESP_LOGI(TAG, "looping now.");
    // arduino-esp32
    delay(1000);
}

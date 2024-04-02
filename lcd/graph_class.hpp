#include "lcd_lib.h"
#include "font8x8.h"
#include "fonts/font8x12_lsb.h"

// Simple graphic interface

struct Point2D {
    int32_t x, y;
};

struct RGB {
    uint8_t r, g, b;
};

class GraphElement {
   public:
    RGB m_fg_color, m_bg_color;  // foreground and background color

    // constructor
    GraphElement(RGB t_fg_color, RGB t_bg_color) : m_fg_color(t_fg_color), m_bg_color(t_bg_color) {}

    // ONLY ONE INTERFACE WITH LCD HARDWARE!!!
    void drawPixel(int32_t t_x, int32_t t_y) { lcd_put_pixel(t_x, t_y, convert_RGB888_to_RGB565(m_fg_color)); }

    // Draw graphics element
    virtual void draw() = 0;

    // Hide graphics element
    virtual void hide() {
        swap_fg_bg_color();
        draw();
        swap_fg_bg_color();
    }

   private:
    // swap foreground and backgroud colors
    void swap_fg_bg_color() {
        RGB l_tmp = m_fg_color;
        m_fg_color = m_bg_color;
        m_bg_color = l_tmp;
    }

    // conversion of 24-bit RGB color into 16-bit color format
    uint16_t convert_RGB888_to_RGB565(RGB t_color) {
        int16_t ret = 0;
        int16_t temp = t_color.r;

        temp >>= 3;
        temp <<= 3 + 8;
        ret += temp;

        temp = t_color.g;
        temp >>= 2;
        temp <<= 2 + 3;
        ret += temp;

        t_color.b >>= 3;
        ret += t_color.b;

        return ret;
    }
};

class Pixel : public GraphElement {
   public:
    // constructor
    Pixel(Point2D t_pos, RGB t_fg_color, RGB t_bg_color) : GraphElement(t_fg_color, t_bg_color), m_pos(t_pos) {}
    // Draw method implementation
    virtual void draw() { drawPixel(m_pos.x, m_pos.y); }
    // Position of Pixel
    Point2D m_pos;
};

class Circle : public GraphElement {
   public:
    Point2D m_center;  // Center of circle
    int32_t m_radius;  // Radius of circle

    Circle(Point2D t_center, int32_t t_radius, RGB t_fg, RGB t_bg) : GraphElement(t_fg, t_bg), m_center(t_center), m_radius(t_radius) {}

    // https://ankurm.com/implementing-bresenhams-circle-drawing-algorithm-in-c/
    void draw_plot(int x1, int y1, int x, int y) {
        drawPixel(x1 + x, y1 + y);  // plotting the pixels.
        drawPixel(x1 + x, y - y1);
        drawPixel(x - x1, y1 + y);
        drawPixel(x - x1, y - y1);
        drawPixel(x + y1, y + x1);
        drawPixel(x + y1, y - x1);
        drawPixel(x - y1, y + x1);
        drawPixel(x - y1, y - x1);
    }

    void draw() {
        float dp;  // initialising the descision parameter.
        int x1, y1;
        x1 = 0;  // initialisng the X,Y cordinates.
        y1 = m_radius;
        dp = 3 - 2 * m_radius;
        while (x1 <= y1) {
            if (dp <= 0)
                dp += (4 * x1) + 6;
            else {
                dp += 4 * (x1 - y1) + 10;
                y1--;
            }
            x1++;
            draw_plot(x1, y1, m_center.x, m_center.y);
        }
    }
};

class Character : public GraphElement {
   public:
    Point2D m_pos;     // position of character
    char m_character;  // character

    Character(Point2D t_pos, char t_char, RGB t_fg, RGB t_bg) : GraphElement(t_fg, t_bg), m_pos(t_pos), m_character(t_char){};

    void draw() {
        for (int y = 0; y < (int)(sizeof(*font8x8) / sizeof(**font8x8)); y++) {
            for (int x = 0; x < (int)(8 * sizeof(**font8x8)); x++) {
                if (font8x8[(int)m_character][y] & 1 << x)
                    drawPixel(x + m_pos.x, y + m_pos.y);
            }
        }
    };

    // NOTE: custom overload method
    void draw(bool use_non_default_font) {
        if (!use_non_default_font) {
            draw();
        } else {
            for (int y = 0; y < (int)(sizeof(*font) / sizeof(**font)); y++) {
                for (int x = 0; x < (int)(8 * sizeof(**font)); x++) {
                    if (font[(int)m_character][y] & 1 << x)
                        drawPixel(x + m_pos.x, y + m_pos.y);
                }
            }
        }
    };
};

class Line : public GraphElement {
   public:
    Point2D m_pos1, m_pos2;  // the first and the last point of line

    Line(Point2D t_pos1, Point2D t_pos2, RGB t_fg, RGB t_bg) : GraphElement(t_fg, t_bg), m_pos1(t_pos1), m_pos2(t_pos2) {}

    // https://gist.github.com/nowke/965fed0d5191bf373f1262be584207bb
    void draw() {
        int x1 = m_pos1.x;  // can rename x1,... to m_pos1.x,...
        int x2 = m_pos2.x;
        int y1 = m_pos1.y;
        int y2 = m_pos2.y;

        int dx, dy, i, e;
        int incx, incy, inc1, inc2;
        int x, y;

        dx = x2 - x1;
        dy = y2 - y1;

        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;
        incx = 1;
        if (x2 < x1) incx = -1;
        incy = 1;
        if (y2 < y1) incy = -1;
        x = x1;
        y = y1;
        if (dx > dy) {
            drawPixel(x, y);
            e = 2 * dy - dx;
            inc1 = 2 * (dy - dx);
            inc2 = 2 * dy;
            for (i = 0; i < dx; i++) {
                if (e >= 0) {
                    y += incy;
                    e += inc1;
                } else
                    e += inc2;
                x += incx;
                drawPixel(x, y);
            }

        } else {
            drawPixel(x, y);
            e = 2 * dx - dy;
            inc1 = 2 * (dx - dy);
            inc2 = 2 * dx;
            for (i = 0; i < dy; i++) {
                if (e >= 0) {
                    x += incx;
                    e += inc1;
                } else
                    e += inc2;
                y += incy;
                drawPixel(x, y);
            }
        }
    };
};

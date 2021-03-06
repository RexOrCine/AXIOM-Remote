
/*	AXIOM Remote
 **
 **	Copyright (C) 2018 Sebastian Pichelhofer
 * 
 **
 **	This program is free software; you can redistribute it and/or modify
 **    	it under the terms of the GNU General Public License 2 as published 
 **	by the Free Software Foundation.
 **
 **	Compile with -O6 for best experience
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "definitions.h"
#include "utility.c"

#ifndef PAGE_C
#define PAGE_C

// Color Definitions
uint16_t _page_item_label_color;
uint16_t _page_item_value_color;
uint16_t _page_item_label_background_color;
uint16_t _page_item_value_background_color;
uint16_t _page_item_highlight_color;
uint16_t _page_background_color;
uint16_t _page_item_width;
uint8_t _padding_side;
uint8_t _padding_elements;
uint8_t _page_item_label_height;
uint8_t _page_item_value_height;


/**************************************************************************/
/*!
    @brief    draw a standard page item that contains a value and label 
    @param    screen_index - position of the item on screen, there is space for 3 top and 3 bottom, total 6 items
    @param    page_item - the struct containing details about the page item
    @param    highlighted - is the item currently highlighted
 */

/**************************************************************************/
void draw_page_item(uint8_t screen_index) {

    // don't draw empty items
    if (_main_page[page_home].page_item[screen_index].label == NULL) {
        return;
    }

    // the screen only provides space for 6 items
    screen_index = limit_range(screen_index, 0, 5);

    uint16_t page_item_height = _page_item_label_height + _page_item_value_height;

    // derive x,y coordinates from screen_index
    uint16_t x, y;
    if (screen_index == 0) {
        x = _padding_side;
        y = _height - page_item_height;
    }
    if (screen_index == 1) {
        x = _padding_side + _padding_elements + _page_item_width;
        y = _height - page_item_height;
    }
    if (screen_index == 2) {
        x = _padding_side + 2 * _padding_elements + 2 * _page_item_width;
        y = _height - page_item_height;
    }
    if (screen_index == 3) {
        x = _padding_side;
        y = 0;
    }
    if (screen_index == 4) {
        x = _padding_side + _padding_elements + _page_item_width;
        y = 0;
    }
    if (screen_index == 5) {
        x = _padding_side + 2 * _padding_elements + 2 * _page_item_width;
        y = 0;
    }

    // handle item hightlighting
    uint16_t page_item_label_color;
    uint16_t page_item_label_background_color;
    uint16_t page_item_value_background_color;
    uint16_t page_item_value_color;
    if (_main_page[page_home].page_item[screen_index].highlighted) {
        page_item_label_color = _page_item_label_background_color;
        page_item_label_background_color = _page_item_highlight_color;
        page_item_value_color = _page_item_label_color;
        page_item_value_background_color = _page_item_label_background_color;
    } else {
        page_item_label_color = _page_item_label_color;
        page_item_label_background_color = _page_item_label_background_color;
        page_item_value_background_color = _page_item_value_background_color;
        page_item_value_color = _page_item_value_color;
    }

    if (screen_index < 3) {
        // 3 top items

        if (_main_page[page_home].page_item[screen_index].item_type == button) {
            fill_round_rect(x, y + 2 + _button_height, _page_item_width, _button_height, 3, page_item_label_background_color);
            draw_string(x, y + 9 + _button_height, _main_page[page_home].page_item[screen_index].label,
                    page_item_label_color, page_item_label_color,
                    _FreeSans12pt7b, align_center, _page_item_width);
        }
        if (_main_page[page_home].page_item[screen_index].item_type == value_and_label) {
            // draw label
            fill_round_rect(x, y + _page_item_value_height, _page_item_width, _page_item_label_height, 3,
                    page_item_label_background_color);
            fill_rect(x, y + _page_item_value_height, _page_item_width, 3, 3, page_item_label_background_color);
            draw_string(x, y + _page_item_value_height + 7, _main_page[page_home].page_item[screen_index].label,
                    page_item_label_color, page_item_value_color,
                    _FreeSans9pt7b, align_center, _page_item_width);

            // draw value
            fill_round_rect(x, y, _page_item_width, _page_item_value_height, 3, page_item_value_background_color);
            fill_rect(x, y + _page_item_value_height - 3, _page_item_width, 3, page_item_value_background_color);
            draw_string(x, y + 10, _main_page[page_home].page_item[screen_index].value, page_item_value_color, page_item_value_color,
                    _FreeSans12pt7b, align_center, _page_item_width);
        }
    } else {
        // 3 bottom items

        if (_main_page[page_home].page_item[screen_index].item_type == button) {
            fill_round_rect(x, y + 2, _page_item_width, _button_height, 3, page_item_label_background_color);
            draw_string(x, y + 9, _main_page[page_home].page_item[screen_index].label, page_item_label_color, page_item_label_color,
                    _FreeSans12pt7b, align_center, _page_item_width);
        }
        if (_main_page[page_home].page_item[screen_index].item_type == value_and_label) {
            // draw label

            fill_round_rect(x, y + 1, _page_item_width, _page_item_label_height, 3, page_item_label_background_color);
            fill_rect(x, y + _page_item_label_height - 3, _page_item_width, 3, 3, page_item_label_background_color);
            draw_string(x, y + 7, _main_page[page_home].page_item[screen_index].label, page_item_label_color, page_item_label_color,
                    _FreeSans9pt7b, align_center, _page_item_width);

            // draw value
            fill_round_rect(x, y + _page_item_label_height, _page_item_width, _page_item_value_height, 3, page_item_value_background_color);
            fill_rect(x, y + _page_item_label_height, _page_item_width, 3, page_item_value_background_color);
            draw_string(x, y + _page_item_label_height + 6, _main_page[page_home].page_item[screen_index].value, page_item_value_color, page_item_value_color,
                    _FreeSans12pt7b, align_center, _page_item_width);
        }
    }
}

/**************************************************************************/
/*!
    @brief    draw one page with its 6 page_items
 */

/**************************************************************************/
void draw_page() {
    //clear the screen
    fill_rect(0, 0, _width, _height, _page_background_color);

    uint8_t a;
    for (a = 0; a < _page_count; a++) {
        if (_main_page[a].page_id == _current_page) {
            uint8_t i;
            for (i = 0; i < _main_page[a].page_items_count; i++) {
                draw_page_item(i);
            }
        }
    }

    /*
     * Testing font sizes and string length calculations
     * 
     * draw_string(15, 60, "test", _page_item_label_color, _page_item_label_color, _FreeSans9pt7b, align_left, 0);
    fill_rect(15, 55, get_string_width("test", _FreeSans9pt7b), 3, _page_item_value_color);

    draw_string(15, 80, "15", _page_item_label_color, _page_item_label_color, _FreeSans18pt7b, align_left, 0);
    fill_rect(15, 75, get_string_width("15", _FreeSans18pt7b), 3, _page_item_value_color);

    draw_string(15, 110, "A Word", _page_item_label_color, _page_item_label_color, _FreeSans18pt7b, align_left, 0);
    fill_rect(15, 105, get_string_width("A Word", _FreeSans18pt7b), 3, _page_item_value_color);

    draw_string(15, 160, "Long 34", _page_item_label_color, _page_item_label_color, _FreeSans12pt7b, align_left, 0);
    fill_rect(15, 155, get_string_width("Long 34", _FreeSans12pt7b), 3, _page_item_value_color);
     */
}

void init_pages() {
    //colors
    _page_item_label_color = color565(255, 255, 255);
    _page_item_value_color = color565(0, 0, 0);
    _page_item_label_background_color = color565(0, 0, 0);
    _page_item_value_background_color = color565(255, 255, 255);
    _page_item_highlight_color = color565(255, 128, 0);

    _page_background_color = color565(200, 200, 200);


    // dimensions
    _padding_side = 8;
    _padding_elements = 11;
    _page_item_width = 94;
    //_page_item_height = 75;
    _page_item_label_height = 25;
    _page_item_value_height = 40;

    uint8_t j = 0;
    strcpy(_main_page[page_home].label, "Main Page");
    _main_page[page_home].page_id = page_home;

    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "FPS");
    strcpy(_main_page[page_home].page_item[j].value, "...");
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = value_and_label;
    j++;
    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "Item 2");
    strcpy(_main_page[page_home].page_item[j].value, "...");
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = value_and_label;
    j++;
    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "Shutter");
    strcpy(_main_page[page_home].page_item[j].value, "...");
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = value_and_label;
    j++;
    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "MENU");
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = button;
    j++;
    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "Item 5");
    strcpy(_main_page[page_home].page_item[j].value, "...");
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = value_and_label;
    j++;
    _main_page[page_home].page_item[j].disabled = false;
    strcpy(_main_page[page_home].page_item[j].label, "WB");
    sprintf(_main_page[page_home].page_item[j].value, "%dK", _white_balance.white_balance_options[_white_balance.white_balance_selection_index].Kelvin);
    _main_page[page_home].page_item[j].link_to_subpage = page_wb;
    _main_page[page_home].page_item[j].fontsize = _FreeSans12pt7b;
    _main_page[page_home].page_item[j].highlighted = false;
    _main_page[page_home].page_item[j].item_type = value_and_label;

    _main_page[page_home].page_items_count = j + 1;

    //_current_page = page_home;
    _page_count = 2;


    _transition_active = false;
    _transition_counter = 0;
    _transition_animation_type = push_left;
}

void update_pages() {
    sprintf(_main_page[page_home].page_item[5].value, "%dK", _white_balance.white_balance_options[_white_balance.white_balance_selection_index].Kelvin);
}

void navigate_to_page(enum _page_id_t target_page, enum transition_animation animation) {
    // transition animation
    start_framebuffer_transition(animation, 60);

    _current_page = target_page;

    if (_current_menu != menu_none) {
        _current_menu = menu_none; //navigate_to_menu(menu_none);
    }
}

void main_page_button_press_handler(ButtonID button_index) {
    if (button_index == P1) {
        _main_page[page_home].page_item[0].highlighted = true;
    }
    if (button_index == P2) {
        _main_page[page_home].page_item[1].highlighted = true;
    }
    if (button_index == P3) {
        _main_page[page_home].page_item[2].highlighted = true;
    }
    if (button_index == P4) {
        _main_page[page_home].page_item[3].highlighted = true;
    }
    if (button_index == P5) {
        _main_page[page_home].page_item[4].highlighted = true;
    }
    if (button_index == P6) {
        _main_page[page_home].page_item[5].highlighted = true;
    }
}

void main_page_button_release_handler(ButtonID button_index) {
    if (button_index == P1) {
        _main_page[page_home].page_item[0].highlighted = false;
    }
    if (button_index == P2) {
        _main_page[page_home].page_item[1].highlighted = false;
    }
    if (button_index == P3) {
        _main_page[page_home].page_item[2].highlighted = false;
    }
    if (button_index == P4) {
        _main_page[page_home].page_item[3].highlighted = false;

        navigate_to_menu(menu_main);
    }
    if (button_index == P5) {
        _main_page[page_home].page_item[4].highlighted = false;
    }
    if (button_index == P6) {
        _main_page[page_home].page_item[5].highlighted = false;

        navigate_to_page(_main_page[page_home].page_item[5].link_to_subpage, push_up);
    }
}

#endif /* PAGE_C */
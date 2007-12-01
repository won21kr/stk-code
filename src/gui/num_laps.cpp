//  $Id$
//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2006, 2007 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "num_laps.hpp"
#include "race_manager.hpp"
#include "widget_manager.hpp"
#include "menu_manager.hpp"
#if defined(WIN32) && !defined(__CYGWIN__)
#  define snprintf _snprintf
#endif

enum WidgetTokens {
    WTOK_TITLE,

    WTOK_NUMLAPS,

    WTOK_LESS,
    WTOK_MORE,

    WTOK_START,
    WTOK_QUIT
};

NumLaps::NumLaps() : laps(3)
{
    widget_manager->add_wgt(WTOK_TITLE, 50, 7);
    widget_manager->show_wgt_rect(WTOK_TITLE);
    widget_manager->show_wgt_text(WTOK_TITLE);
    widget_manager->set_wgt_text(WTOK_TITLE, _("Choose number of laps"));
    widget_manager->break_line();

    widget_manager->add_wgt( WidgetManager::WGT_NONE, 100, 5);
    widget_manager->break_line();

    widget_manager->add_wgt(WTOK_NUMLAPS, 20, 7);
    widget_manager->show_wgt_rect(WTOK_NUMLAPS);
    widget_manager->show_wgt_text(WTOK_NUMLAPS);
    widget_manager->set_wgt_text(WTOK_NUMLAPS, _("Laps: 3"));
    widget_manager->break_line();

    widget_manager->add_wgt( WidgetManager::WGT_NONE, 100, 5);
    widget_manager->break_line();

    widget_manager->add_wgt(WTOK_LESS, 20, 7);
    widget_manager->show_wgt_rect(WTOK_LESS);
    widget_manager->show_wgt_text(WTOK_LESS);
    widget_manager->set_wgt_text(WTOK_LESS, _("Less"));
    widget_manager->activate_wgt(WTOK_LESS);
    widget_manager->break_line();

    widget_manager->add_wgt(WTOK_MORE, 20, 7);
    widget_manager->show_wgt_rect(WTOK_MORE);
    widget_manager->show_wgt_text(WTOK_MORE);
    widget_manager->set_wgt_text(WTOK_MORE, _("More"));
    widget_manager->activate_wgt(WTOK_MORE);
    widget_manager->break_line();

    widget_manager->add_wgt( WidgetManager::WGT_NONE, 100, 5);
    widget_manager->break_line();

    widget_manager->add_wgt(WTOK_START, 30, 7);
    widget_manager->show_wgt_rect(WTOK_START);
    widget_manager->show_wgt_text(WTOK_START);
    widget_manager->set_wgt_text(WTOK_START, _("Start race"));
    widget_manager->activate_wgt(WTOK_START);
    widget_manager->break_line();

    widget_manager->add_wgt(WTOK_QUIT, 50, 7);
    widget_manager->show_wgt_rect(WTOK_QUIT);
    widget_manager->show_wgt_text(WTOK_QUIT);
    widget_manager->set_wgt_text(WTOK_QUIT, _("Press <ESC> to go back"));
    widget_manager->activate_wgt(WTOK_QUIT);

/*    m_menu_id = widgetSet -> varray(0);
    widgetSet -> label(m_menu_id, _("Choose number of laps"),  GUI_LRG, GUI_ALL, 0, 0 );

    widgetSet -> space(m_menu_id);

    lap_label_id = widgetSet -> label(m_menu_id, _("Laps: 3"));
    widgetSet -> space(m_menu_id);
    widgetSet -> state(m_menu_id, _("Less"), GUI_MED, 10);
    widgetSet -> state(m_menu_id, _("More"), GUI_MED, 20);
    widgetSet -> space(m_menu_id);
    widgetSet -> start(m_menu_id, _("Start Race"), GUI_SML, 30);
    widgetSet -> state(m_menu_id, _("Press <ESC> to go back"), GUI_SML, -1);
    widgetSet -> space(m_menu_id);

    widgetSet -> layout(m_menu_id, 0, 0);*/
    widget_manager->layout(WGT_AREA_ALL);
}

// -----------------------------------------------------------------------------
NumLaps::~NumLaps()
{
    widget_manager->reset();
}   // ~NumLaps

// -----------------------------------------------------------------------------
void NumLaps::select()
{
    const int WGT = widget_manager->get_selected_wgt();
/*    const int id = widgetSet->click();
    const int n = widgetSet->get_token(id);*/
    //TEMP
    switch (WGT)
    {
      case WTOK_LESS:
        laps = std::max(1, laps-1);
        snprintf(lap_label, MAX_MESSAGE_LENGTH, "Laps: %d", laps);
	    widget_manager->set_wgt_text(WTOK_NUMLAPS, lap_label);
        break;
      case WTOK_MORE:
        laps = std::min(10, laps+1);
        snprintf(lap_label, MAX_MESSAGE_LENGTH, "Laps: %d", laps);
        widget_manager->set_wgt_text(WTOK_NUMLAPS, lap_label);
        break;
      case WTOK_START:
        race_manager->setNumLaps(laps);
        race_manager->start();
        break;
      case WTOK_QUIT:
        menu_manager->popMenu();
	break;
    }
}   // select




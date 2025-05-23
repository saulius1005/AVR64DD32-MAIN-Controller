/*
 * Windows.c
 *
 * Created: 2024-12-11 21:50:34
 * Author: Saulius
 *
 * This file provides functions for displaying and managing time, date, location (latitude, longitude),
 * altitude, and timezone on the screen. It includes extraction and formatting of specific data for display.
 */

#include "Settings.h"
#include "windowsVar.h"


void smartScreenUpdater() {
 /*   bool weatherChanged = isWeatherChanged();
    bool mainMenuChanged = weatherChanged || isTimeAngleChanged();

    // First open update and later according to conditions
    switch (Keypad3x4.key_held) {
	    case WINDOW_DATE_LOCATION: // Date and location
	    if (Refresh.firstUpdate[WINDOW_DATE_LOCATION] || Keypad3x4.key != Refresh.tempKey) {
		    DateAndLocationChangeWindow();
		    Refresh.firstUpdate[WINDOW_DATE_LOCATION] = true;
	    }
	    break;

	    case WINDOW_TIME_ANGLE_VIEW: // Parameters view window
	    if (Refresh.firstUpdate[WINDOW_TIME_ANGLE_VIEW] || isTimeAngleChanged()) {
		    timeBaseParameterWindow();
		    Refresh.firstUpdate[WINDOW_TIME_ANGLE_VIEW] = false;
	    }
	    break;

	    case WINDOW_LOCATION: // Long press 3
	    if (Refresh.firstUpdate[WINDOW_LOCATION] || Refresh.tempNoRefresh == 0) {
		    locationParameterWindow();
		    Refresh.firstUpdate[WINDOW_LOCATION] = false;
		    Refresh.tempNoRefresh = 1; // Specialus atvejis tik ðiam langui
	    }
	    break;

	    case WINDOW_WEATHER: // Long press 4
	    if (Refresh.firstUpdate[WINDOW_WEATHER] || weatherChanged) {
		    weatherParameterWindow();
		    Refresh.firstUpdate[WINDOW_WEATHER] = false;
	    }
	    break;

	    default: // Main menu
	    if (Refresh.firstUpdate[WINDOW_MAIN_MENU] || mainMenuChanged) {
		    MainWindow();
		    Refresh.firstUpdate[WINDOW_MAIN_MENU] = false;
	    }
	    break;
    }

    // Reset pradinio atnaujinimo indikatorius, kai pereinama á kità langà
    for (int i = 0; i < 5; i++) {
	    Refresh.firstUpdate[i] = (i == Keypad3x4.key_held) ? Refresh.firstUpdate[i] : true;
    }

    // Specialus atvejis tik langui 23
    Refresh.tempNoRefresh = (Keypad3x4.key_held == WINDOW_LOCATION) ? 1 : 0;*/
}

void updateRefreshValues() {

}

void windows() {
	smartScreenUpdater();
	updateRefreshValues();
}
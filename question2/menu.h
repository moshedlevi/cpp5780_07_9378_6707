/*
   File: menu.h
   Description: this is header file of enum for menu options
   Course: 150018 C++ Workshop
   Exercise 7, Question 2
   Authors: David Ovits 311179378, Moshe David Levi 200436707
*/

#ifndef __MENU_H
#define __MENU_H

enum MenuOption {
	 EXIT, OPEN, CURRENT_FILE, ADD, DELETE, PRINT_INFO, CHECK_REG, SET_REG, SET_UNREG, PRINT_REG_COURSE, PRINT_ALL_REG, COMBINE_FILES,
	 FIRST_MENU_OPTION = EXIT, LAST_MENU_OPTION = COMBINE_FILES
};

MenuOption menu();

#endif // __MENU_H
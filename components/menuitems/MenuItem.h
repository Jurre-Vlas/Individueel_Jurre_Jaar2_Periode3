//
// Created by Mick on 10/03/2021.
//

#ifndef INC_2021_TI23_A2_MENUITEM_H
#define INC_2021_TI23_A2_MENUITEM_H

typedef struct {
   char *nameEN;
   char *nameNL;
   void (*handle)(void *args);
} MenuItem;

#endif //INC_2021_TI23_A2_MENUITEM_H

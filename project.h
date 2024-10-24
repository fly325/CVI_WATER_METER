/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_COMLED                     3       /* control type: LED, callback function: (none) */
#define  PANEL_WATERTANK                  4       /* control type: scale, callback function: (none) */
#define  PANEL_PUMP_ON                    5       /* control type: LED, callback function: (none) */
#define  PANEL_DECORATION_2               6       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_3               7       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_5               8       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               9       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_6               10      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 11      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_7               12      /* control type: deco, callback function: (none) */
#define  PANEL_LOW_THRES                  13      /* control type: numeric, callback function: Low_Thres */
#define  PANEL_UP_THRES                   14      /* control type: numeric, callback function: Up_Thres */
#define  PANEL_DISCONNECT                 15      /* control type: command, callback function: Disconnect */

#define  PANEL_CONN                       2
#define  PANEL_CONN_CONNECT               2       /* control type: command, callback function: connect */
#define  PANEL_CONN_CLOSE                 3       /* control type: command, callback function: Close */
#define  PANEL_CONN_BAUD                  4       /* control type: slide, callback function: (none) */
#define  PANEL_CONN_COM                   5       /* control type: slide, callback function: (none) */

#define  PANEL_GRAP                       3
#define  PANEL_GRAP_TAB                   2       /* control type: tab, callback function: (none) */
#define  PANEL_GRAP_CL_GR                 3       /* control type: command, callback function: Close_Gr */

#define  PANEL_MGT                        4
#define  PANEL_MGT_CLOSE                  2       /* control type: command, callback function: CloseDM */
#define  PANEL_MGT_TAB                    3       /* control type: tab, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_GRAPH                   2       /* control type: graph, callback function: cursorGR */
#define  TABPANEL_SAVE_GR_DTA_CSV         3       /* control type: command, callback function: Save_data_CSV */
#define  TABPANEL_SAVE_GR_DTA             4       /* control type: command, callback function: Save_data_file */
#define  TABPANEL_WL_2                    5       /* control type: numeric, callback function: (none) */
#define  TABPANEL_WL                      6       /* control type: numeric, callback function: (none) */
#define  TABPANEL_CLEAR_GR                7       /* control type: command, callback function: Clear_gr */
#define  TABPANEL_TEXTMSG_3               8       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_TEXTMSG_2               9       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_TEXTMSG                 10      /* control type: textMsg, callback function: (none) */
#define  TABPANEL_HOLD                    11      /* control type: binary, callback function: Hold */
#define  TABPANEL_TEXTMSG_4               12      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_2_TEXTBOX               2       /* control type: textBox, callback function: (none) */
#define  TABPANEL_2_CLEAR_LOG             3       /* control type: command, callback function: Clear_log */
#define  TABPANEL_2_LOS_ST                4       /* control type: command, callback function: Log_St */
#define  TABPANEL_2_TEXTMSG               5       /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_3_WL_2                  2       /* control type: numeric, callback function: (none) */
#define  TABPANEL_3_WL                    3       /* control type: numeric, callback function: (none) */
#define  TABPANEL_3_CLEAR                 4       /* control type: command, callback function: clr */
#define  TABPANEL_3_GRAPH                 5       /* control type: graph, callback function: cursorGR2 */
#define  TABPANEL_3_IMPORT                6       /* control type: command, callback function: Import_Data */
#define  TABPANEL_3_TEXTMSG_3             7       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_3_TEXTMSG_2             8       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_3_TEXTMSG_4             9       /* control type: textMsg, callback function: (none) */
#define  TABPANEL_3_TEXTMSG               10      /* control type: textMsg, callback function: (none) */

     /* tab page panel controls */
#define  TABPANEL_4_TABLE                 2       /* control type: table, callback function: (none) */
#define  TABPANEL_4_TABLE_CLEAR           3       /* control type: command, callback function: Table_Clear */
#define  TABPANEL_4_IMP_EXCEL             4       /* control type: command, callback function: Imp_Excel */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_ITEM1              3       /* callback function: connect_menu */
#define  MENUBAR_MENU2                    4
#define  MENUBAR_MENU2_ITEM1_2            5       /* callback function: G_and_L */
#define  MENUBAR_MENU2_ITEM2              6       /* callback function: Open_DM */
#define  MENUBAR_Help                     7
#define  MENUBAR_Help_ABOUT               8       /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Clear_gr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clear_log(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close_Gr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CloseDM(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK connect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK connect_menu(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK cursorGR(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK cursorGR2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Disconnect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK G_and_L(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Hold(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Imp_Excel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Import_Data(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Log_St(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Low_Thres(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Open_DM(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_data_CSV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_data_file(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Table_Clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Up_Thres(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
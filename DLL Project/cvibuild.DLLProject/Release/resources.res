        ��  ��                  �       �� ��     0 	        <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" />�      �� ��     0 	        �4   V S _ V E R S I O N _ I N F O     ���                 ?                            S t r i n g F i l e I n f o   �   0 4 0 9 0 4 b 0        C o m p a n y N a m e     Z   F i l e D e s c r i p t i o n     D L L P r o j e c t   ( R e l e a s e   x 8 6 )     (   F i l e V e r s i o n     1 . 0   6   I n t e r n a l N a m e   D L L P r o j e c t     F   L e g a l C o p y r i g h t   C o p y r i g h t       2 0 2 4     F   O r i g i n a l F i l e n a m e   D L L P r o j e c t . d l l     8   P r o d u c t N a m e       D L L P r o j e c t   ,   P r o d u c t V e r s i o n   1 . 0   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	��  X   C V I D L L P R O T O T Y P E S   C V I D L L E X P O R T S         0 	        long ExcelRpt_ActivateWorksheet(CAObjHandle worksheetHandle);
long ExcelRpt_AddHyperlink(CAObjHandle worksheetHandle, const char *cellRange, const char *address, const char *screenTip);
long ExcelRpt_AllowCSSSupport(CAObjHandle workbookHandle, int value);
long ExcelRpt_AllowPNGSupport(CAObjHandle workbookHandle, int value);
long ExcelRpt_AllowVMLSupport(CAObjHandle workbookHandle, int value);
long ExcelRpt_ApplicationNew(int makeVisible, CAObjHandle *applicationHandle);
long ExcelRpt_ApplicationQuit(CAObjHandle applicationHandle);
long ExcelRpt_ChartActivate(CAObjHandle chartHandle);
long ExcelRpt_ChartAddtoWorksheet(CAObjHandle worksheetHandle, double left, double top, double width, double height, CAObjHandle *chartHandle);
long ExcelRpt_ChartDelete(CAObjHandle chartHandle);
long ExcelRpt_ChartNew(CAObjHandle workbookHandle, int insertBeforeIndex, CAObjHandle *chartHandle);
long ExcelRpt_ChartPrint(CAObjHandle chartHandle, int displayPrintDialog);
long ExcelRpt_ChartSetSourceRange(CAObjHandle chartHandle, CAObjHandle worksheetHandle, const char *cellRange);
long ExcelRpt_ChartWizard(CAObjHandle chartHandle, CAObjHandle worksheetHandle, const char *sourceRange, enum ExREnum_ExChartWizardGallery chartGallery, int format, enum ExREnum_ExRowCol plotBy, int categoryLabels, int seriesLabels, int hasLegend, const char *title, const char *categoryAxisTitle, const char *valueAxisTitle, const char *extraAxisTitle);
long ExcelRpt_DeleteColumn(CAObjHandle worksheetHandle, int columnIndex, int numColumns);
long ExcelRpt_DeleteRow(CAObjHandle worksheetHandle, int rowIndex, int numRows);
long ExcelRpt_Fill(CAObjHandle worksheetHandle, enum ExREnum_ExFillOptions direction, const char *cellRange);
long ExcelRpt_Find(CAObjHandle worksheetHandle, enum ExREnum_ExDataType dataType, const void *data, const char *afterCell, enum ExREnum_ExFindLookIn lookIn, enum ExREnum_ExLookAt lookAt, enum ExREnum_ExSearchOrder searchOrder, enum ExREnum_ExSearchDirection searchDirection, int matchCase, int matchByte, char foundRange[]);
long ExcelRpt_FreeStringData(char **data, unsigned int count);
long ExcelRpt_GetApplicationAttribute(CAObjHandle applicationHandle, int attribute, void *attributeValue);
long ExcelRpt_GetCellDataType(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType *dataType);
long ExcelRpt_GetCellRangeAttribute(CAObjHandle worksheetHandle, const char *cellRange, int attribute, void *attributeValue);
long ExcelRpt_GetCellValue(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType dataType, void *dataValue);
long ExcelRpt_GetCellValueStringLen(CAObjHandle worksheetHandle, const char *cellRange, int *length);
long ExcelRpt_GetChartAttribute(CAObjHandle chartHandle, int attribute, void *attributeValue);
long ExcelRpt_GetChartAxisAttribute(CAObjHandle chartHandle, enum ExREnum_ExAxisType axisType, enum ExREnum_ExAxisGroup axisGroup, int attribute, void *attributeValue);
long ExcelRpt_GetChartsheetFromIndex(CAObjHandle workbookHandle, int Index, CAObjHandle *chartsheetHandle);
long ExcelRpt_GetChartsheetFromName(CAObjHandle workbookHandle, const char *chartName, CAObjHandle *chartsheetHandle);
long ExcelRpt_GetEmbeddedChartFromIndex(CAObjHandle worksheetHandle, int Index, CAObjHandle *chartHandle);
long ExcelRpt_GetEmbeddedChartFromName(CAObjHandle worksheetHandle, const char *chartName, CAObjHandle *chartHandle);
struct ERRORINFO *ExcelRpt_GetErrorInfo();
long ExcelRpt_GetNumCellsInRange(CAObjHandle worksheetHandle, const char *cellRange, int *numCells);
long ExcelRpt_GetRangeDataType(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType *dataType);
long ExcelRpt_GetSheetTypeFromIndex(CAObjHandle workbookHandle, int Index, enum ExREnum_ExSheetType *sheetType);
long ExcelRpt_GetWorkbookAttribute(CAObjHandle workbookHandle, int attribute, void *attributeValue);
long ExcelRpt_GetWorksheetAttribute(CAObjHandle worksheetHandle, int attribute, void *attributeValue);
long ExcelRpt_GetWorksheetFromIndex(CAObjHandle workbookHandle, int Index, CAObjHandle *worksheetHandle);
long ExcelRpt_GetWorksheetFromName(CAObjHandle workbookHandle, const char *worksheetName, CAObjHandle *worksheetHandle);
long ExcelRpt_InsertColumn(CAObjHandle worksheetHandle, int insertBeforeColumnIndex, int numColumns);
long ExcelRpt_InsertPicture(CAObjHandle worksheetHandle, const char *fileName, int top, int left, int width, int height);
long ExcelRpt_InsertRow(CAObjHandle worksheetHandle, int insertBeforeRowIndex, int numRows);
long ExcelRpt_RangeBorder(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExLineStyle Linestyle, long color, enum ExREnum_ExBorderWeight weight, unsigned char edges);
long ExcelRpt_RangeDelete(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDeleteShiftDirection shiftDirection);
long ExcelRpt_RangeInsert(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExInsertShiftDirection shiftDirection);
long ExcelRpt_RangePrint(CAObjHandle worksheetHandle, const char *cellRange, int displayDialog);
long ExcelRpt_RangeSelect(CAObjHandle worksheetHandle, const char *cellRange);
long ExcelRpt_ReadData(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType dataType, void *data);
long ExcelRpt_ReadDataToTableControl(CAObjHandle worksheetHandle, const char *cellRange, struct Point startpoint, enum ExREnum_ExInsertMode insertmode, int panel, int control);
long ExcelRpt_RunMacro(CAObjHandle applicationHandle, const char *macroName);
long ExcelRpt_SetApplicationAttribute(CAObjHandle applicationHandle, int attribute, ...);
long ExcelRpt_SetCellRangeAttribute(CAObjHandle worksheetHandle, const char *cellRange, int attribute, ...);
long ExcelRpt_SetCellValue(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType dataType, ...);
long ExcelRpt_SetChartAttribute(CAObjHandle chartHandle, int attribute, ...);
long ExcelRpt_SetChartAxisAttribute(CAObjHandle chartHandle, enum ExREnum_ExAxisType axisType, enum ExREnum_ExAxisGroup axisGroup, int attribute, ...);
long ExcelRpt_SetEncoding(CAObjHandle workbookHandle, int encoding);
long ExcelRpt_SetMinimumMonitor(CAObjHandle workbookHandle, long resolution, long pixelsPerInch);
long ExcelRpt_SetWorksheetAttribute(CAObjHandle worksheetHandle, int attribute, ...);
long ExcelRpt_Show(CAObjHandle worksheetHandle, const char *cellRange);
long ExcelRpt_Sort(CAObjHandle worksheetHandle, const char *cellRange, const char *key1, enum ExREnum_ExSortOrder sortOrder1, const char *key2, enum ExREnum_ExSortOrder sortOrder2, enum ExREnum_ExSortOrientation sortOrientation, enum ExREnum_ExYesNo header);
long ExcelRpt_WorkbookClose(CAObjHandle workbookHandle, int saveChanges);
long ExcelRpt_WorkbookNew(CAObjHandle applicationHandle, CAObjHandle *workbookHandle);
long ExcelRpt_WorkbookOpen(CAObjHandle applicationHandle, const char *fileName, CAObjHandle *workbookHandle);
long ExcelRpt_WorkbookSave(CAObjHandle workbookHandle, const char *fileName, enum ExREnum_ExFileFormat format);
long ExcelRpt_WorksheetDelete(CAObjHandle worksheetHandle);
long ExcelRpt_WorksheetNew(CAObjHandle workbookHandle, int insertBeforeIndex, CAObjHandle *worksheetHandle);
long ExcelRpt_WriteData(CAObjHandle worksheetHandle, const char *cellRange, enum ExREnum_ExDataType dataType, unsigned int dim1, unsigned int dim2, const void *data);
long ExcelRpt_WriteDataFromTableControl(CAObjHandle worksheetHandle, const char *cellRange, int panel, int control);
void LoadXLSX(double *timeT, double *dataT, double *UpLimitT, double *LowLimitT) __declspec(dllexport);
void SaveXLSX(struct datastr Data) __declspec(dllexport);
void UpdateLogDLL(int data, unsigned char cmd, char *stringPrint, char *Date_string) __declspec(dllexport);
void sendAlert(char cmd, int com) __declspec(dllexport);
           �� ��     0	                                        
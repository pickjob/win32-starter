/**
 * 资源类型
 *      RT_ACCELERATOR      MAKEINTRESOURCE(9)      Accelerator table
 *      RT_ANICURSOR        MAKEINTRESOURCE(21)     Animated cursor
 *      RT_ANIICON          MAKEINTRESOURCE(22)     Animated icon
 *      RT_BITMAP           MAKEINTRESOURCE(2)      Bitmap resource
 *      RT_CURSOR           MAKEINTRESOURCE(1)      Hardware-dependent cursor resource
 *      RT_DIALOG           MAKEINTRESOURCE(5)      Dialog box
 *      RT_DLGINCLUDE       MAKEINTRESOURCE(17)     Allows a resource editing tool to associate a string with an .rc file
 *      RT_FONT             MAKEINTRESOURCE(8)      Font resource
 *      RT_FONTDIR          MAKEINTRESOURCE(7)      Font directory resource
 *      RT_GROUP_CURSOR     MAKEINTRESOURCE((ULONG_PTR)(RT_CURSOR) + 11)        Hardware-independent cursor resource
 *      RT_GROUP_ICON       MAKEINTRESOURCE((ULONG_PTR)(RT_ICON) + 11)          Hardware-independent icon resource
 *      RT_HTML             MAKEINTRESOURCE(23)     HTML resource
 *      RT_ICON             MAKEINTRESOURCE(3)      Hardware-dependent icon resource
 *      RT_MANIFEST         MAKEINTRESOURCE(24)     Side-by-Side Assembly Manifest
 *      RT_MENU             MAKEINTRESOURCE(4)      Menu resource
 *      RT_MESSAGETABLE     MAKEINTRESOURCE(11)     Message-table entry
 *      RT_PLUGPLAY         MAKEINTRESOURCE(19)     Plug and Play resource
 *      RT_RCDATA           MAKEINTRESOURCE(10)     Application-defined resource (raw data)
 *      RT_STRING           MAKEINTRESOURCE(6)      String-table entry
 *      RT_VERSION          MAKEINTRESOURCE(16)     Version resource
 *      RT_VXD              MAKEINTRESOURCE(20)     VXD
 * 资源文件语法
 *      CURSOR
 *          nameID CURSOR filename
 *      MENU
 *          menuID MENU
 *          [optional-statements]
 *          BEGIN
 *               MENUITEM text, result, [optionlist]
 *               MENUITEM SEPARATOR
 *                   result:
 *                       CHECKED、GRAYED、HELP、INACTIVE、MENUBARBREAK、MENUBREAK
 *          END
 *          POPUP text, [optionlist]
 *               optionlist:
 *                   CHECKED、GRAYED、HELP、INACTIVE、MENUBARBREAK、MENUBREAK
 *          BEGIN
 *               MENUITEM text, result, [optionlist]
 *               MENUITEM SEPARATOR
 *                   result:
 *                       CHECKED、GRAYED、HELP、INACTIVE、MENUBARBREAK、MENUBREAK
 *          END
 *      ACCELERATORS
 *          acctablename ACCELERATORS
 *          [optional-statements]
 *          BEGIN
 *              event, idvalue, [type] [options]...
 *                  event: 双引号
 *                  options:
 *                      ALT
 *                      SHIFT
 *                      CONTROL
 *          END
 *      DIALOGEX
 *          nameID DIALOGEX x, y, width, height [ , helpID] [optional-statements]
 *              optional-statements
 *                  CAPTION "captiontext"   标题
 *                  CLASS class     注册类
 *                  MENU menuname       菜单
 *                  STYLE style     样式
 *                  EXSTYLE extended-style      样式
 *                  VERSION dword   版本
 *          BEGIN
 *               CONTROL controlText, id, className, style   通用控件
 *                   className
 *                       BUTTON, STATIC, EDIT, LISTBOX, SCROLLBAR, COMBOBOX
 *                   style
 *                       WS_*, BS_*, SS_*, ES_*, LBS_*, SBS_*, CBS_*
 *               staticClass controlText, id     文本控件
 *                   staticClass
 *                       LTEXT, RTEXT, CTEXT
 *               buttonClass controlText, id     按钮控件
 *                   buttonClass
 *                       AUTO3STATE, AUTOCHECKBOX, AUTORADIOBUTTON, CHECKBOX, PUSHBOX, PUSHBUTTON, RADIOBUTTON, STATE3, USERBUTTON
 *               editClass id    编辑控件
 *                   editClass
 *                       EDITTEXT, BEDIT, HEDIT, IEDIT
 *          END
 *      CONTROL
 *          ICON
 *              nameID ICON filename
 *          LTEXT text, id, x, y, width, height [, style [, extended-style]]: 文本
 *               style: SS_LEFT | WS_GROUP
 *                   SS_LEFT, WS_TABSTOP, WS_GROUP
 *          CTEXT text, id, x, y, width, height [, style [, extended-style]]: 文本
 *               style: SS_CENTER | WS_GROUP
 *                   SS_CENTER, WS_TABSTOP, WS_GROUP
 *          RTEXT text, id, x, y, width, height [, style [, extended-style]]: 文本
 *               style: SS_RIGHT | WS_GROUP
 *                   WS_TABSTOP and WS_GROUP
 *          DEFPUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]: 按钮
 *               style: BS_DEFPUSHBUTTON | WS_TABSTO
 *                   BS_DEFPUSHBUTTON, WS_TABSTOP, WS_GROUP, WS_DISABLED
 *          PUSHBUTTON text, id, x, y, width, height [, style [, extended-style]]
 *               style: BS_PUSHBUTTON | WS_TABSTOP
 *                   WS_TABSTOP, WS_DISABLED, WS_GROUP
 *          PUSHBOX text, id, x, y, width, height [, style [, extended-style]]:
 *               style: BS_PUSHBOX | WS_TABSTOP
 *                   WS_TABSTOP, WS_DISABLED, WS_GROUP
 *          EDITTEXT id, x, y, width, height [, style [, extended-style]]: 编辑框
 *               style: ES_LEFT | WS_BORDER | WS_TABSTOP
 *                   WS_TABSTOP, WS_GROUP, WS_VSCROLL, WS_HSCROLL, WS_DISABLED
 *          RADIOBUTTON text, id, x, y, width, height [, style [, extended-style]]
 *               style: BS_RADIOBUTTON | WS_TABSTOP
 *                   WS_TABSTOP, WS_DISABLED, WS_GROUP
 *          CHECKBOX text, id, x, y, width, height [, style [, extended-style]]: 多选框
 *               style: BS_CHECKBOX | WS_TABSTOP
 *                   BS_CHECKBOX, WS_TABSTOP, WS_GROUP
 *          AUTOCHECKBOX text, id, x, y, width, height [, style [, extended-style]]: 多选框
 *               style: BS_AUTOCHECKBOX | WS_TABSTOP
 *                   WS_TABSTOP, WS_GROUP
 *          AUTO3STATE text, id, x, y, width, height [, style [, extended-style]]: 三状态多选款
 *               style: BS_AUTO3STATE | WS_TABSTOP
 *                    WS_TABSTOP, WS_DISABLED, WS_GROUP
 *          COMBOBOX id, x, y, width, height [, style [, extended-style]]
 *               style: CBS_SIMPLE | WS_TABSTOP
 *                   WS_TABSTOP, WS_GROUP, WS_VSCROLL, WS_DISABLED
 *          LISTBOX id, x, y, width, height [, style [, extended-style]]
 *               style: LBS_NOTIFY | WS_BORDER
 *                    WS_BORDER, WS_VSCROLL
 *          SCROLLBAR id, x, y, width, height [, style [, extended-style]]
 *               style: SBS_HORZ
 *                   WS_TABSTOP, WS_GROUP, and WS_DISABLED
 *          STATE3 text, id, x, y, width, height [, style [, extended-style]]
 *               style: BS_3STATE | WS_TABSTOP
 *                   BS_3STATE, WS_TABSTOP, WS_GROUP
 * 函数
 *      遍历资源
 *          EnumResourceType / EnumResourceTypesEx: 函数提供模块中找到的资源类型的列表
 *          EnumResourceNames / EnumResourceNamesEx: 函数提供给定类型中每个资源的名称
 *          EnumResourceLanguages / EnumResourceLanguagesEx: 函数提供给定名称和类型的每个资源的
 *      查找资源
 *          FindResource / FindResourceEx: 在模块中查找资源，并返回二进制资源数据的句柄
 *      加载资源
 *          LoadResource: 使用FindResource返回的资源句柄将资源加载到内存中
 *          LockResource: 锁定资源
 *          特定资源
 *              LoadAccelerators / TranslateAccelerator / DestroyAcceleratorTable: 快捷键表
 *              LoadCursor / LoadCursorFromFile / DestroyCursor: 游标资源
 *              LoadIcon / DrawIcon / DrawIconEx / ExtractIcon / ExtractIconEx / DestroyIcon: 图标资源
 *              LoadBitmap / DeleteObject: 位图资源
 *              LoadImage / DeleteObject: 图标、光标或位图资源
 *              LoadMenu / DestroyMenu: 菜单资源
 *              LoadString: 字符串表
 *              GetFileVersionInfo / GetFileVersionInfoSize / VerQueryValue: 版本信息
 *      光标
 *          ShowCursor: 显示或隐藏光标
 *          GetCursorInfo: 检索有关全局游标的信息。
 *          GetCursorPos / SetCursorPos: 光标的位置
 *          GetCursor / SetCursor: 当前游标的句柄
 *          LoadCursor: 从与应用程序实例关联的可执行文件（.EXE）文件加载指定的游标资源
 *          LoadCursorFromFile: 基于文件中包含的数据创建游标
 *      菜单
 *          GetMenu / SetMenu: 窗口的菜单的句柄
 *          CreateMenu: 创建菜单
 *          CreatePopupMenu: 创建下拉菜单、子菜单或快捷菜单
 *          DeleteMenu / DestroyMenu: 从指定菜单中删除项
 *          AppendMenu: 将新项追加到指定菜单栏、下拉菜单、子菜单或快捷菜单的末尾
 *          InsertMenuItem: 在菜单中的指定位置插入新菜单项
 *          RemoveMenu: 删除菜单项或从指定菜单中分离子菜单
 *          CheckMenuItem: 将指定菜单项的复选标记属性的状态设置为选中或清除
 *          CheckMenuRadioItem: 检查指定的菜单项，并将其作为单选项
 * 宏
 *      MAKEINTRESOURCE(i): INT 转为资源
 **/

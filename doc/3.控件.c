/**
 * Win32控件(ComCtl32.dll):
 *      CONTROL text, id, class, style, x, y, width, height
 *          Button
 *               消息&通知
 *                   BM_GETCHECK / BM_SETCHECK: 单选按钮或复选框的选中状态
 *                   BM_GETSTATE / BM_SETSTATE: 按钮或复选框的状态
 *                   BM_CLICK: 模拟用户单击按钮
 *
 *                   BN_CLICKED: 当用户单击按钮时发送
 *                   BN_DBLCLK / BN_DOUBLECLICKED: 当用户双击按钮时发送
 *               函数
 *                   CheckRadioButton: 单选按钮添加复选标记
 *                   CheckDlgButton: 更改按钮控件的检查状态
 *                       BST_CHECKED: 选中
 *                       BST_UNCHECKED: 不选中
 *                       BST_INDETERMINATE: 部分选中(BS_3STATE BS_AUTO3STATE)
 *               宏
 *          BUTTON:
 *               类名: WC_BUTTON
 *               样式:
 *                   BS_BOTTOM: 普通按钮
 *                   BS_PUSHBUTTON / BS_DEFPUSHBUTTON: 按钮
 *                   BS_RADIOBUTTON / BS_AUTORADIOBUTTON: 单选按钮
 *                   BS_CHECKBOX / BS_AUTOCHECKBOX: 多选按钮
 *                   BS_SPLITBUTTON: 分割按钮
 *                   BS_GROUPBOX: 组按钮
 *                   BS_BITMAP: 显示位图按钮
 *                   BS_CENTER / BS_VCENTER: 内容居中
 *                   BS_MULTILINE: 换行
 *                   BS_3STATE / BS_AUTO3STATE: 按钮三种状态
 *               消息:
 *                   BM_GETSTATE: 按钮状态
 *                       wParam: BOOL
 *                       lParam: NULL
 *                   BM_GETSTATE:
 *                       wParam: 0
 *                       lParam: 0
 *                   BM_SETCHECK: 按钮选中
 *                       wParam: BST_CHECKED BST_INDETERMINATE BST_UNCHECKED
 *                       lParam: NULL
 *                   BM_GETCHECK:
 *                       wParam: 0
 *                       lParam: 0
 *          EDIT:
 *               类名: WC_EDIT
 *               样式:
 *                  ES_AUTOHSCROLL / ES_AUTOVSCROLL: 自动滚动
 *                  ES_LEFT / ES_CENTER / ES_RIGHT: 对齐
 *                  ES_MULTILINE: 多行
 *                  ES_PASSWORD: 密码
 *                  ES_READONLY: 只读
 *               消息:
 *                  EM_GETLINE: 复制字符
 *                       wParam: 文本所在行(zero-base)
 *                       lParam: LPCTSTR
 *                  EM_GETLINECOUNT: 获得行数
 *                       wParam: 0
 *                       lParam: 0
 *               宏(windowsx.h): Edit_XXX
 *          LISTBOX:
 *               类名: WC_LISTBOX
 *               样式:
 *                   LBS_STANDARD: 标准
 *                   LBS_MULTIPLESEL: 多选
 *               消息:
 *                   LB_ADDSTRING: 添加项目
 *                       wParam: NULL
 *                       lParam: LPCTSTR
 *                   LB_INSERTSTRING: 插入项目
 *                       wParam: 选项Index(zero-based)
 *                       lParam: LPCTSTR
 *                   LB_DELETESTRING
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *                   LB_FINDSTRING
 *                       wParam: 查找的第一个选项Index(zero-based)
 *                       lParam: LPCTSTR
 *                   LB_GETITEMDATA: 获得选项数据
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *                   LB_GETCOUNT: 获得选项个数
 *                       wParam: 0
 *                       lParam: 0
 *                   LB_GETCURSEL: 获得当前选择
 *                       wParam: 0
 *                       lParam: 0
 *                   LB_SETCURSEL: 设置当前选择
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *               宏(windowsx.h): ListBox_XXX
 *                   ListBox_AddString
 *                   ListBox_DeleteString
 *          COMBOBOX:
 *               类名: WC_COMBOBOX
 *               样式:
 *                   CBS_SIMPLE
 *                   CBS_DROPDOWN
 *                   CBS_DROPDOWNLIST
 *               消息:
 *                   CB_ADDSTRING: 插入选项
 *                       wParam: NULL
 *                       lParam: LPCTSTR
 *                   CB_INSERTSTRING: 插入项目
 *                       wParam: 选项Index(zero-based)
 *                       lParam: LPCTSTR
 *                   CB_DELETESTRING
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *                   CB_FINDSTRING: 查找选项
 *                       wParam: 查找的第一个选项Index(zero-based)
 *                       lParam: LPCTSTR
 *                   CB_SETITEMDATA: 设置选项关联数据
 *                       wParam: 选项Index(zero-based)
 *                       lParam: 关联数据
 *                   CB_GETITEMDATA: 获取选项关联数据
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *                   CB_SETCURSEL:
 *                       wParam: 选项Index(zero-based)
 *                       lParam: NULL
 *                   CB_GETCURSEL: 获得当前选中选项
 *                       wParam: 0
 *                       lParam: 0
 *                   CB_GETCOUNT: 获得选项个数
 *                       wParam: 0
 *                       lParam: 0
 *                   CBN_SELCHANGE: 选项变动回调
 *                       wParam:
 *                           LOWORD: control identifier
 *                           HIWORD: notification code
 *                       lParam： Handle to the combo box
 *               宏(windowsx.h): 封装消息 ComboBox_XXX
 *                   ComboBox_AddString(
 *                       hwndCtl,
 *                       lpsz
 *                   ): void
 *                   ComboBox_SetCurSel(
 *                       hwndCtl,
 *                       index
 *                   ): void
 *          COMBOBOXEX:
 *               类名: WC_COMBOBOXEX
 *               样式:
 *                   CBS_SIMPLE
 *                   CBS_DROPDOWN
 *                   CBS_DROPDOWNLIST
 *               消息:
 *                   CBEM_INSERTITEM: 插入选项
 *                       wParam: 0
 *                       lParam: &COMBOBOXEXITEM
 *                   CBEM_DELETEITEM: 删除选线
 *                       wParam: 选项Index(zero-based)
 *                       lParam: 0
 * 环境
 *          InitCommonControlsEx: 初始化
 **/
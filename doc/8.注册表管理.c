/**
 * 组成:
 *      Key Name(大小写不明感)
 *          HKEY_CLASSES_ROOT
 *          HKEY_CURRENT_USER
 *          HKEY_LOCAL_MACHINE
 *          HKEY_USERS
 *      Key Value Type:
 *          REG_DWORD / REG_QWORD
 *          REG_SZ / REG_EXPAND_SZ / REG_MULTI_SZ
 *          REG_BINARY
 *          REG_NONE
 *      Key Security:
 *          KEY_ALL_ACCESS
 *          KEY_CREATE_SUB_KEY
 *          KEY_ENUMERATE_SUB_KEYS
 *          KEY_NOTIFY
 *          KEY_QUERY_VALUE / KEY_READ / KEY_WRITE / KEY_SET_VALUE
 * 基本函数:
 *      RegEnumKeyEx: 枚举指定打开的注册表项的子项
 *      RegEnumValue: 枚举指定打开的注册表项的值
 *      RegQueryInfoKey: 检索有关指定注册表项的信息
 *      RegQueryValueEx: 检索与打开的注册表项关联的指定值名称的类型和数据
 *      RegCreateKeyEx: 创建指定的注册表项
 *          hKey:
 *              HKEY_CLASSES_ROOT
 *              HKEY_CURRENT_CONFIG
 *              HKEY_CURRENT_USER
 *              HKEY_LOCAL_MACHINE
 *              HKEY_USERS
 *          dwOptions:
 *              REG_OPTION_BACKUP_RESTORE
 *              REG_OPTION_NON_VOLATILE
 *              REG_OPTION_VOLATILE
 *          lpdwDisposition:
 *              REG_CREATED_NEW_KEY
 *              REG_OPENED_EXISTING_KEY
 *      RegOpenKeyEx: 打开指定的注册表项
 *      RegGetValue / RegSetValueEx: 注册表值的类型和数据
 *      RegDeleteKey: 删除子项及其值
 *      RegDeleteValue: 从指定的注册表项中删除命名值
 *      RegDeleteKeyValue: 从指定的注册表项和子项中删除指定的值
 *      RegDeleteTree: 以递归方式删除指定键的子项和值
 *      RegFlushKey: 将指定打开的注册表项的所有属性写入注册表
 *      RegCloseKey: 关闭指定注册表项的句柄
 **/

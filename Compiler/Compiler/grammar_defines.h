/// <summary>
/// Конец входной ленты
/// </summary>
#define END_OF_TAPE  "~`~`~"

/// <summary>
/// Дно магазина
/// </summary>
#define MAGAZINE_BOTTOM  "`~`~`"

/// <summary>
/// Номер правила перехода в случае успешного завершения
/// </summary>
#define SUCCESS  -2

/// <summary>
/// Идентификатор
/// </summary>
#define _IDENT "ident"

/// <summary>
/// Начало программы
/// </summary>
#define _BEGIN  "begin"

/// <summary>
/// Неизвестный идентификатор
/// </summary>
#define UNKNOWN_IDENT 1

/// <summary>
/// Повторно-объявленный индентификатор
/// </summary>
#define REDECLARED_IDENT 0

/// <summary>
/// Нет ошибок в объявлении идентификаторов
/// </summary>
#define NO_ERROR_IN_DECLARE_IDENT -1

/// <summary>
/// Максимальный размер индентификатора
/// </summary>
#define _MAX_IDENT_LENGTH  11

/// <summary>
/// Длина идентификатора больше 11 символов
/// </summary>
#define LONG_IDENT -1

/// <summary>
/// Не идентификатор
/// </summary>
#define NOT_IDENT 0

/// <summary>
/// Идентификатор
/// </summary>
#define IS_IDENT 1

/// <summary>
/// Переход на новую строку
/// </summary>
#define _NL + "\n" +

/// <summary>
/// Конструкция, за которой следует индекс лексемы
/// </summary>
#define _START_INDEX_OF_LEXEM "{!"

/// <summary>
/// Конструкция, которая завершает индекс лексемы
/// </summary>
#define _END_INDEX_OF_LEXEM "}"

/// <summary>
/// Генерирует новый индекс при использование правила трансляции
/// </summary>
#define _NEW_INDEX "{@I}"

/// <summary>
/// Конструкция, используемая для перевода каретки при трансляции
/// </summary>
#define _TRANSLATE_NL "push offset __nl\ncall printf\nadd esp, 4"

/// <summary>
/// Конструкция, которую необходжимо удалить для отпимизациия кода
/// </summary>
#define _DELETED_CONSTR_FOR_OPTIMIZE "push eax\npop eax\n"
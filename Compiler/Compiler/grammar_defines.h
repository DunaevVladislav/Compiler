/// <summary>
/// ����� ������� �����
/// </summary>
#define END_OF_TAPE  "~`~`~"

/// <summary>
/// ��� ��������
/// </summary>
#define MAGAZINE_BOTTOM  "`~`~`"

/// <summary>
/// ����� ������� �������� � ������ ��������� ����������
/// </summary>
#define SUCCESS  -2

/// <summary>
/// �������������
/// </summary>
#define _IDENT "ident"

/// <summary>
/// ������ ���������
/// </summary>
#define _BEGIN  "begin"

/// <summary>
/// ����������� �������������
/// </summary>
#define UNKNOWN_IDENT 1

/// <summary>
/// ��������-����������� ��������������
/// </summary>
#define REDECLARED_IDENT 0

/// <summary>
/// ��� ������ � ���������� ���������������
/// </summary>
#define NO_ERROR_IN_DECLARE_IDENT -1

/// <summary>
/// ������������ ������ ���������������
/// </summary>
#define _MAX_IDENT_LENGTH  11

/// <summary>
/// ����� �������������� ������ 11 ��������
/// </summary>
#define LONG_IDENT -1

/// <summary>
/// �� �������������
/// </summary>
#define NOT_IDENT 0

/// <summary>
/// �������������
/// </summary>
#define IS_IDENT 1

/// <summary>
/// ������� �� ����� ������
/// </summary>
#define _NL + "\n" +

/// <summary>
/// �����������, �� ������� ������� ������ �������
/// </summary>
#define _START_INDEX_OF_LEXEM "{!"

/// <summary>
/// �����������, ������� ��������� ������ �������
/// </summary>
#define _END_INDEX_OF_LEXEM "}"

/// <summary>
/// ���������� ����� ������ ��� ������������� ������� ����������
/// </summary>
#define _NEW_INDEX "{@I}"

/// <summary>
/// �����������, ������������ ��� �������� ������� ��� ����������
/// </summary>
#define _TRANSLATE_NL "push offset __nl\ncall printf\nadd esp, 4"

/// <summary>
/// �����������, ������� ����������� ������� ��� ������������ ����
/// </summary>
#define _DELETED_CONSTR_FOR_OPTIMIZE "push eax\npop eax\n"
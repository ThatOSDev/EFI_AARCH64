// https://github.com/ThatOSDev

#ifndef EFI_H
#define EFI_H

#include <stdint.h>

#define EFI_NOT_READY                           0x8000000000000006

#define EFI_BLACK                               0x00
#define EFI_BLUE                                0x01
#define EFI_GREEN                               0x02
#define EFI_CYAN                                0x03
#define EFI_RED                                 0x04
#define EFI_MAGENTA                             0x05
#define EFI_BROWN                               0x06
#define EFI_LIGHTGRAY                           0x07
#define EFI_DARKGRAY                            0x08
#define EFI_LIGHTBLUE                           0x09
#define EFI_LIGHTGREEN                          0x0A
#define EFI_LIGHTCYAN                           0x0B
#define EFI_LIGHTRED                            0x0C
#define EFI_LIGHTMAGENTA                        0x0D
#define EFI_YELLOW                              0x0E
#define EFI_WHITE                               0x0F
                                               
#define EFI_BACKGROUND_BLACK                    0x00
#define EFI_BACKGROUND_BLUE                     0x10
#define EFI_BACKGROUND_GREEN                    0x20
#define EFI_BACKGROUND_CYAN                     0x30
#define EFI_BACKGROUND_RED                      0x40
#define EFI_BACKGROUND_MAGENTA                  0x50
#define EFI_BACKGROUND_BROWN                    0x60
#define EFI_BACKGROUND_LIGHTGRAY                0x70

typedef uint_least16_t      CHAR16;

typedef unsigned short      UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

typedef unsigned long long      UINTN;

typedef unsigned char       BOOLEAN;

typedef void                *EFI_HANDLE;
typedef UINT64              EFI_STATUS;
typedef void                *EFI_EVENT;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct EFI_INPUT_KEY
{
	UINT16    ScanCode;
	UINT16    UnicodeChar;
}EFI_INPUT_KEY;

typedef void(*EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);

typedef EFI_STATUS (*EFI_INPUT_RESET)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL
{
	EFI_INPUT_RESET        Reset;
	EFI_INPUT_READ_KEY     ReadKeyStroke;
	EFI_EVENT              WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_TEXT_RESET)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

typedef EFI_STATUS (*EFI_TEXT_STRING)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS (*EFI_TEXT_TEST_STRING)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);
typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber, UINTN *Columns, UINTN *Rows);
typedef EFI_STATUS (*EFI_TEXT_SET_MODE)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber);

typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET                         Reset;
    EFI_TEXT_STRING                        OutputString;
    EFI_TEXT_TEST_STRING                   TestString;
    EFI_TEXT_QUERY_MODE                    QueryMode;
    EFI_TEXT_SET_MODE                      SetMode;
    EFI_TEXT_SET_ATTRIBUTE                 SetAttribute;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct EFI_TABLE_HEADER
{
    UINT64    Signature;
    UINT32    Revision;
    UINT32    HeaderSize;
    UINT32    CRC32;
    UINT32    Reserved;
} EFI_TABLE_HEADER;

typedef struct EFI_SYSTEM_TABLE
{
    EFI_TABLE_HEADER                hrd;
    CHAR16                          *FirmwareVendor;
    UINT32                          FirmwareVersion;
    EFI_HANDLE                      ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *ConIn;
    EFI_HANDLE                      ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
} EFI_SYSTEM_TABLE ;

#endif // EFI_H

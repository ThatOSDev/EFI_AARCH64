// UEFI From Scratch for AARCH64 - ThatOSDev ( 2024 )
// https://github.com/ThatOSDev/EFI_AARCH64

#include "efi.h"
#include "ErrorCodes.h"
#include "efilibs.h"

// This is like int main() in a typical C program.
// In this case, we create an ImageHandle for the overall EFI interface,
// as well as a System Table pointer to the EFI_SYSTEM_TABLE struct.
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *ST)
{
	(void)ImageHandle;

    // We setup this global variable in the libs.h file.
    SystemTable = ST;
    
    ResetScreen();
    
    SetColor(EFI_WHITE);
    SetTextPosition(10, 2);
    Print(L"EFI loaded on AARCH64 Hardware !\r\n\r\n");
    
    SetColor(EFI_GREEN);
    SetTextPosition(10, 4);
    Print(L"Hit Any Key to see Graphics");

    HitAnyKey();
    
	SetTextPosition(10, 6);
    Print(L"Loading Graphics Output Protocol ... ");
    EFI_STATUS Status = SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
    if(Status == EFI_SUCCESS)
    {
        SetColor(EFI_CYAN);
        Print(CheckStandardEFIError(Status));
        SetGraphicsColor(ORANGE);
        CreateFilledBox(50, 50, 100, 200);
        SetGraphicsColor(RED);
        CreateFilledBox(60, 60, 80, 30);
        SetColor(EFI_YELLOW);
        SetTextPosition(10, 8);
        Print(L"We have Graphics !!");
    } else {
        SetColor(EFI_RED);
        Print(CheckStandardEFIError(Status));
    }

    SetColor(EFI_GREEN);
    SetTextPosition(2, 10);
    Print(L"Hit Any Key");

    HitAnyKey();
	
    SetColor(EFI_GREEN);
    SetTextPosition(2, 10);
    Print(L"Halting the CPU, you can shut this off now.");
	
	while(1){__asm__("wfi\n\t");}   // WFI is similar to the HLT in x86_64

    // The EFI needs to have a 0 ( or EFI_SUCCESS ) in order to know everything is ok.
    return EFI_SUCCESS;
}

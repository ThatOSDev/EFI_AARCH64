
#include "efi.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
	(void)ImageHandle;

    SystemTable->ConOut->Reset(SystemTable->ConOut, 1);

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_LIGHTGREEN);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Hit Any Key\r\n");

    SystemTable->ConIn->Reset(SystemTable->ConIn, 1);

    EFI_INPUT_KEY Key;

    while((SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key)) == EFI_NOT_READY);

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_YELLOW);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Good Job !\r\n");
	
	while(1){};

    return 0;
}
	


// UEFI From Scratch for AARCH64 - ThatOSDev ( 2024 )
// https://github.com/ThatOSDev/EFI_AARCH64

#include "efi.h"
#include "ErrorCodes.h"
#include "efilibs.h"

EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *system)
{
	InitEFI(image, system);

    void* ExternalFileBuffer;

    EFI_FILE_PROTOCOL* efimyfile = openFile(u"testfile.bin");

    UINT64 fsize = 0x00001000;
    EFI_STATUS Status = SystemTable->BootServices->AllocatePool(EfiLoaderData, fsize, (void**)&ExternalFileBuffer);
	SetTextColor(EFI_BROWN);
    wprintf(u"AllocatePool ExternalFileBuffer");
	SetTextColor(EFI_LIGHTCYAN);  
    wprintf(CheckStandardEFIError(Status));

    efimyfile->SetPosition(efimyfile, 0);
    
    efimyfile->Read(efimyfile, &fsize, ExternalFileBuffer);
    SetTextColor(EFI_GREEN);
    wprintf(u"\r\nRead ExternalFileBuffer");
	SetTextColor(EFI_LIGHTCYAN);  
    wprintf(CheckStandardEFIError(Status));

    SetTextColor(EFI_LIGHTCYAN);    
    wprintf(u"\r\nFile Signature\r\n");
    SetTextColor(EFI_LIGHTRED);    
    UINT8* test = (UINT8*)ExternalFileBuffer;

    for(int m = 0; m < 5; m++)
    {
        int j = *test;
        wprintf(u" %x", j);
        test++;
    }
    
    SetTextColor(EFI_GREEN);
    SetTextPosition(10, 20);
    wprintf(u"Hit Any Key to shutdown");

    HitAnyKey();
	
	SHUTDOWN();
	
    SetTextColor(EFI_GREEN);
    SetTextPosition(0, 22);
    wprintf(u"If you see this, something went wrong. Manually turn off the computer.");
	
	while(1){__asm__("wfi\n\t");}   // WFI is similar to the HLT in x86_64

    return EFI_SUCCESS;
}

VbeInfoBlock STRUC
	VbeSignature		db 'VESA' ; VBE Signature
	VbeVersion			dw 0200h ; VBE Version
	OemStringPtr		dd ? ; Pointer to OEM String
	Capabilities		db 4 dup (?) ; Capabilities of graphics controller
	VideoModePtr		dd ? ; Pointer to VideoModeList
	TotalMemory			dw ? ; Number of 64kb memory blocks
	; Added for VBE 2.0
	OemSoftwareRev		dw ? ; VBE implementation Software revision
	OemVendorNamePtr	dd ? ; Pointer to Vendor Name String
	OemProductNamePtr	dd ? ; Pointer to Product Name String
	OemProductRevPtr	dd ? ; Pointer to Product Revision String
    Reserved0           db 222 dup (?) ; Reserved for VBE implementation scratch area
	OemData				db 256 dup (?) ; Data Area for OEM Strings
VbeInfoBlock ENDS

ModeInfoBlock STRUC
	; Mandatory information for all VBE revisions
	ModeAttributes		dw ? ; mode attributes
	WinAAttributes		db ? ; window A attributes
	WinBAttributes		db ? ; window B attributes
	WinGranularity		dw ? ; window granularity
	WinSize				dw ? ; window size
	WinASegment			dw ? ; window A start segment
	WinBSegment			dw ? ; window B start segment
	WinFuncPtr			dd ? ; pointer to window function
	BytesPerScanLine	dw ? ; bytes per scan line
	
	; Mandatory information for VBE 1.2 and above
	
    XResolution         dw ? ; horizontal resolution in pixels or characters
	YResolution			dw ? ; vertical resolution in pixels or characters
	XCharSize			db ? ; character cell width in pixels
	YCharSize			db ? ; character cell height in pixels
	NumberOfPlanes		db ? ; number of memory planes
	BitsPerPixel		db ? ; bits per pixel
	NumberOfBanks		db ? ; number of banks
	MemoryModel			db ? ; memory model type
	BankSize			db ? ; bank size in KB
	NumberOfImagePages	db ? ; number of images
    Reserved1           db 1 ; reserved for page function
; Direct Color fields (required for direct/6 and YUV/7 memory models)
	RedMaskSize			db ? ; size of direct color red mask in bits
	RedFieldPosition	db ? ; bit position of lsb of red mask
	GreenMaskSize		db ? ; size of direct color green mask in bits
	GreenFieldPosition	db ? ; bit position of lsb of green mask
	BlueMaskSize		db ? ; size of direct color blue mask in bits
	BlueFieldPosition	db ? ; bit position of lsb of blue mask
	RsvdMaskSize		db ? ; size of direct color reserved mask in bits
	RsvdFieldPosition	db ? ; bit position of lsb of reserved mask
	DirectColorModeInfo	db ? ; direct color mode attributes
; Mandatory information for VBE 2.0 and above
	PhysBasePtr			dd ? ; physical address for flat memory frame buffer
	OffScreenMemOffset	dd ? ; pointer to start of off screen memory
	OffScreenMemSize	dw ? ; amount of off screen memory in 1k units
; Mandatory information for VBE 3.0 and above
	LinBytesPerScanLine	dw 0	; bytes per scan line for linear modes
	BnkNumberOfImagePages	db 0	; number of images for banked modes
	LinNumberOfImagePages	db 0	; number of images for linear modes

	LinRedMaskSize	db 0	; size of direct color red mask (linear modes)
	LinRedFieldPosition	db 0	; bit position of lsb of red mask (linear modes)

    LinGreenMaskSize    db 0    ; size of direct color green mask  (linear modes)
	LinGreenFieldPosition	db 0	; bit position of lsb of green mask (linear modes)

	LinBlueMaskSize	db 0	; size of direct color blue mask  (linear modes)
	LinBlueFieldPosition	db 0	; bit position of lsb of blue mask (linear modes)

	LinRsvdMaskSize	db 0	; size of direct color reserved mask (linear modes)
	LinRsvdFieldPosition	db 0	; bit position of lsb of reserved mask (linear modes)
	MaxPixelClock		dd 0	; maximum pixel clock (in Hz) for graphics mode
    Reserved3            db 190 dup (?) ; remainder of ModeInfoBlock
ModeInfoBlock ENDS

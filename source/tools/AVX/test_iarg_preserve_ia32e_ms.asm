
PUBLIC XSaveHelper1
PUBLIC XSaveHelper2
PUBLIC XRstorHelper
PUBLIC Fld2tToTop3a






.code

XSaveHelper1	proc
	mov    eax, 7
    xor    edx, edx
	;xsave [rcx]
        db 0Fh, 0AEh, 021h
	ret
XSaveHelper1	Endp

XSaveHelper2	proc
	mov    eax, 7
    xor    edx, edx
	;xsave [rcx]
        db 0Fh, 0AEh, 021h
	ret
XSaveHelper2	Endp

XRstorHelper proc
	mov    eax, 7
    xor    edx, edx
	;xrstor [rcx]
	db 0Fh, 0AEh, 029h	
	ret
XRstorHelper Endp





FldzToTop3 PROC
	fldz
	fldz
	fldz
    ret

FldzToTop3 ENDP





Fld2tToTop3a PROC
    
	fldl2t
	fldl2t
	fldl2t
    ret

Fld2tToTop3a ENDP




end



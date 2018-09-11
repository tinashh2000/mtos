/***************************************************************************************
* Copyright (C) 2018 Tinashe Mutandagayi                                               *
*                                                                                      *
* This file is part of the MT-Operating System source code. The author(s) of this file *
* is/are not liable for any damages, loss or loss of information, deaths, sicknesses   *
* or other bad things resulting from use of this file or software, either direct or    *
* indirect.                                                                            *
* Terms and conditions for use and distribution can be found in the license file named *
* LICENSE.TXT. If you distribute this file or continue using it,                       *
* it means you understand and agree with the terms and conditions in the license file. *
* binding this file.                                                                   *
*                                                                                      *
* Happy Coding :)                                                                      *
****************************************************************************************/


#pragma once

#define KF_CREATE_THREAD 0
#define KF_CREATE_PROCESS 1
#define KF__IDLE 2
#define KF__ACTIVE 3
#define KF__HALT 4
#define KF_RUNTHREAD 5
#define KF_SUSPENDTHREAD 6
#define KF_GETCURRENTPROCESS 7
#define KF_GETCURRENTTHREAD 8
#define KF_CRITICALPROCESSSTART 9
#define KF_CRITICALPROCESSEND 10
#define KF_SPINLOCK 11
#define KF_SPINUNLOCK 12
#define KF_KESPINLOCKVARIABLE 13
#define KF_INITLOCK 14
#define KF_LOCK 15
#define KF_LOCKX 16
#define KF_UNLOCK 17
#define KF_ACQUIRELOCK 18
#define KF_CREATELOCK 19
#define KF_DESTROYLOCK 20
#define KF_ISLOCKED 21
#define KF_PROCESSISRUNNING 22
#define KF_THREADISRUNNING 23
#define KF_FAVOURTHREAD 24
#define KF_RETIRETHREAD 25
#define KF_ISCURRENTTHREADKERNEL 26
#define KF_ISCURRENTPROCESSKERNEL 27
#define KF_ISTHREADCRITICAL 28
#define KF_DESTROYTHREAD 29
#define KF_GETTHREADNAME 30
#define KF_GETPROCESSNAME 31
#define KF_GETCURRENTPROCESSNAME 32
#define KF_GETCURRENTTHREADNAME 33
#define KF_CRITICALSECTIONSTART 34
#define KF_CRITICALSECTIONEND 35
#define KF_KERNELCRITICALSECTIONSTART 36
#define KF_KERNELCRITICALSECTIONEND 37
#define KF_ISKERNELCRITICALSECTION 38
#define KF_ISKERNELPROCESS 39
#define KF_ISKERNELTHREAD 40
#define KF_ISOSREADY 41
#define KF_SETTHREADLOG 42
#define KF_SETTIMEOUT 43
#define KF_SETTIMERINTERVAL 44
#define KF_CANCELTIMER 45
#define KF_SETCURRENTTHREADNAME 46
#define KF_SETTHREADNAME 47
#define KF_VERIFYPROCESS 48
#define KF_VERIFYTHREAD 49
#define KF_GETPROCESSPRIVATEDATA 50
#define KF_SETPROCESSPRIVATEDATA 51
#define KF_GETPROCESSPRIVATEITEM 52
#define KF_SETPROCESSPRIVATEITEM 53
#define KF_INITIALIZEPROCESSPRIVATEDATA 54
#define KF_SETTHREADPRIVATEDATA 55
#define KF_GETTHREADPRIVATEDATA 56
#define KF_GETTHREADPRIVATEITEM 57
#define KF_SETTHREADPRIVATEITEM 58
#define KF_INITIALIZETHREADPRIVATEDATA 59
#define KF_VMMALLOCATEMEMORY 60
#define KF_VMMREALLOCATEMEMORY 61
#define KF_VMMFREEMEMORY 62
#define KF_VMMRESERVE 63
#define KF_VMMCOMMIT 64
#define KF_VMMGETMEMORYSIZE 65
#define KF_VMMSHAREMEMORY 66
#define KF_VMMPROTECT 67
#define KF_WAITFOREVENT 68
#define KF_DOEVENTS 69
#define KF_WAITFOREVENTS 70
#define KF_PROCESSEVENTS 71
#define KF_EVENTSLOOP 72
#define KF_GETNUMEVENTS 73
#define KF_ADDEVENTTOQUEUE 74
#define KF_REGISTEREVENTSCLASS 75
#define KF_SENDPROCESSEVENT 76
#define KF_GETNEXTEVENT 77
#define KF_EVENTSINQUEUE 78
#define KF_GETMAXEVENTS 79
#define KF_DELAY 80
#define KF_DELAYUS 81
#define KF_GETTICKSUS 82
#define KF_GETTICKSMS 83
#define KF_SETINTERRUPTVECTOR 84
#define KF_DISABLEINTERRUPTS 85
#define KF_ENABLEINTERRUPTS 86
#define KF__SCHEDULER 87
#define KF_OSREBOOT 88
#define KF_OSSHUTDOWN 89
#define KF_GETFEATURES 90
#define KF_GETCURRENTEXU 91
#define KF_GETSYSTEMINFORMATION 92
#define KF_UISHOWMESSAGE 93
#define KF_SETUIPROCESS 94
#define KF_GETUIPROCESS 95
#define KF_GISETPIXEL 96
#define KF_GIGETPIXEL 97
#define KF_GIDRAWBOX 98
#define KF_GISETVIDEOPARAMS 99
#define KF_GIGETVIDEOBPP 100
#define KF_GIGETVIDEOHEIGHT 101
#define KF_GIGETVIDEOWIDTH 102
#define KF_UIPRINTSTR 103
#define KF_UIPRINTCHAR 104
#define KF_UIPRINTWSTR 105
#define KF_UIPRINTSTRX 106
#define KF_UIPRINTWSTRX 107
#define KF_UICLEARSCREEN 108
#define KF_FS_FINDFILEINIT 109
#define KF_FS_FINDFILEDONE 110
#define KF_FS_FINDFILE 111
#define KF_FS_GETFILEINFO 112
#define KF_FS_GETOPENFILEINFO 113
#define KF_FS_VOLUMEEXISTS 114
#define KF_FS_CHARTOUNICODE 115
#define KF_FS_UNICODETOCHAR 116
#define KF_FS_READ 117
#define KF_FS_WRITE 118
#define KF_FS_SETFILEPOSITION 119
#define KF_FS_GETFILEPOSITION 120
#define KF_FS_GETFILESIZE 121
#define KF_FS_DELETEFILE 122
#define KF_FS_VOLGETBYTESPERUNIT 123
#define KF_FS_ISUNICODE 124
#define KF_FS_GETLASTERROR 125
#define KF_FS_SETLASTERROR 126
#define KF_FS_PARSEPATH 127
#define KF_FS_OPENFILE 128
#define KF_FS_READFILE 129
#define KF_FS_WRITEFILE 130
#define KF_FS_CLOSEFILE 131
#define KF_DLFIND 132
#define KF_DLOPENFILE 133
#define KF_DLSYM 134
#define KF_DLCLOSEFILE 135

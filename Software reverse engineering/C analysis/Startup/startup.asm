                            LAB_80000000:                 ;XREF[13,0]:  80000058,8000005c,80000e14,800164cc
                                                          ;             80037494,8003749c,800374c8,800374d8
                                                          ;             800374dc,80037500,80037508,8003750c
                                                          ;             8003a7b0
ram:80000000    dbf021e3        msr         cpsr_c,#0xdb                                                           ;Setup stack pointers
ram:80000004    58d09fe5        ldr         sp,[DAT_80000064]                       ;= 81FB5000h
ram:80000008    d7f021e3        msr         cpsr_c,#0xd7                            
ram:8000000c    54d09fe5        ldr         sp,[DAT_80000068]                       ;= 81FC1800h
                                                          ;XREF[0,1]:   80035b10
ram:80000010    d2f021e3        msr         cpsr_c,#0xd2                            
ram:80000014    50d09fe5        ldr         sp,[DAT_8000006c]                       ;= 81FDA800h
                                                          ;XREF[0,1]:   80035b38
ram:80000018    d1f021e3        msr         cpsr_c,#0xd1                            
ram:8000001c    4cd09fe5        ldr         sp,[DAT_80000070]                       ;= 81FE7000h
ram:80000020    dff021e3        msr         cpsr_c,#0xdf                            
ram:80000024    48d09fe5        ldr         sp,[DAT_80000074]                       ;= 82000000h
ram:80000028    d3f021e3        msr         cpsr_c,#0xd3                            
ram:8000002c    44d09fe5        ldr         sp,[DAT_80000078]                       ;= 81FF3800h
ram:80000030    100f11ee        mrc         p15,0x0,r0,cr1,cr0,0x0                                                  ;Reset MMU and get address for where to write the vectors
ram:80000034    020ac0e3        bic         r0,r0,#0x2000                           
ram:80000038    100f01ee        mcr         p15,0x0,r0,cr1,cr0,0x0                  
ram:8000003c    38009fe5        ldr         r0,[PTR_DAT_8000007c]                   ;= 80000df4                     ;r0 points to where the vectors are stored
ram:80000040    102f11ee        mrc         p15,0x0,r2,cr1,cr0,0x0                  
ram:80000044    022a12e2        ands        r2,r2,#0x2000                           
ram:80000048    0010a003        moveq       r1,#0x0                                 
ram:8000004c    2c109f15        ldrne       r1,[->H_Reset]                          ;= ffff0000                      ;r1 points to where they need to go
                                                          ; FWD[8,0]:   80000df4,80000df8,80000dfc,80000e00
                                                          ;             80000e04,80000e08,80000e0c,80000e10
ram:80000050    fc05b0e8        ldmia       r0!,{r2 r3 r4 r5 r6 r7 r8 r10}=>DAT_8...;= E59FF018h                     ;Load the vectors from ram
                                                                                    ;= E1A00000h
                                                                                    ;= EAFFFC81h
ram:80000054    fc05a1e8        stmia       r1!,{ r2 r3 r4 r5 r6 r7 r8 r10 }                                         ;Store the first 8 words
                                                          ; FWD[10,0]:  80000000,80000e14,80000e18,80000e1c
                                                          ;             80000e20,80000e24,80000e28,80000e2c
                                                          ;             80000e30,80000e34
ram:80000058    fc05b0e8        ldmia       r0!,{r2 r3 r4 r5 r6 r7 r8 r10}=>PTR_L...;= 80000e40                      ;load the second 8
                                                                                    ;= 80000000
                                                                                    ;= 80000e38
                                                                                    ;= 80000e48
                                                                                    ;= 80000e34
                                                                                    ;= 80000e3c
                                                          ; FWD[7,0]:   80000000,80000e34,80000e38,80000e3c
                                                          ;             80000e40,80000e48,80000e4c
ram:8000005c    fc05a1e8        stmia       r1!,{ r2 r3 r4 r5 r6 r7 r8 r10 }=>LAB...                                  ;Store them to.
ram:80000060    070000ea        b           LAB_80000084                                                              ;Jump to init section

;Stack pointers initial values
                            DAT_80000064:                 ;XREF[1,0]:   80000004
ram:80000064    0050fb81        undefined4  81FB5000h                               
                            DAT_80000068:                 ;XREF[1,0]:   8000000c
ram:80000068    0018fc81        undefined4  81FC1800h                               
                            DAT_8000006c:                 ;XREF[1,0]:   80000014
ram:8000006c    00a8fd81        undefined4  81FDA800h                               
                            DAT_80000070:                 ;XREF[1,0]:   8000001c
ram:80000070    0070fe81        undefined4  81FE7000h                               
                            DAT_80000074:                 ;XREF[1,0]:   80000024
ram:80000074    00000082        undefined4  82000000h                               
                            DAT_80000078:                 ;XREF[1,0]:   8000002c
ram:80000078    0038ff81        undefined4  81FF3800h                               
                            PTR_DAT_8000007c:             ;XREF[1,0]:   8000003c
ram:8000007c    f40d0080        addr        DAT_80000df4                            ;= EAFFFC81h
                            PTR_H_Reset_80000080:         ;XREF[1,0]:   8000004c
ram:80000080    0000ffff        addr        H_Reset                                 
                            LAB_80000084:                 ;XREF[1,0]:   80000060

;init section
ram:80000084    000000eb        bl          FUN_8000008c                            ;undefined FUN_8000008c()
ram:80000088    3e0000eb        bl          FUN_80000188                            ;undefined FUN_80000188()
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_8000008c()
                                                          ;XREF[1,0]:   80000084
ram:8000008c    2c008fe2        adr         r0=>DAT_800000c0,0x800000c0             ;= 00192DACh           ;r0 points to 0x800000c0
                                                          ; FWD[2,0]:   800000c0,800000c4
ram:80000090    000c90e8        ldmia       r0,{r10 r11}=>DAT_800000c0              ;= 00192DACh           ;r10 = 0x00192DAC
                                                                                    ;= 00192DDCh           ;r11 = 0x00192DDC
                                                                                                           ;r0  = 0x800000C0
ram:80000094    00a08ae0        add         r10,r10,r0                                                     ;r10 = 0x80192E6C
ram:80000098    00b08be0        add         r11,r11,r0                                                     ;r11 = 0x80192E9C
ram:8000009c    01704ae2        sub         r7,r10,#0x1                                                    ;r7  = 0x80192E6B
ram:800000a0    0b005ae1        cmp         r10,r11                                                        ;r10 != r11
ram:800000a4    0000001a        bne         LAB_800000ac                                                   ;branch
ram:800000a8    360000eb        bl          FUN_80000188                            ;undefined FUN_80000188()
                            LAB_800000ac:                 ;XREF[1,0]:   800000a4
                                                          ; FWD[4,0]:   80192e6c,80192e70,80192e74,80192e78
ram:800000ac    0f00bae8        ldmia       r10!,{r0 r1 r2 r3}=>PTR_DAT_80192e6c    ;= 80000124             ;r3   copy function
                                                                                    ;= 80192e9c             ;r0   source address
                                                                                    ;= 00000A18h            ;r2   Number of bytes
                                                                                    ;= 8019D5A0h            ;r1   destination address
ram:800000b0    18e04fe2        adr         lr,0x800000a0                                                   ;set return address to compare instruction at 0x800000a0
ram:800000b4    010013e3        tst         r3,#0x1                                                         ;see if r3 bit 0 is 0x01
ram:800000b8    03f04710        subne       pc=>LAB_00192d47,r7,r3                  
ram:800000bc    13ff2fe1        bx          r3=>LAB_80000124                        

                            DAT_800000c0:                 ;XREF[2,0]:   8000008c,80000090
ram:800000c0    ac2d1900        undefined4  00192DACh                               
                            DAT_800000c4:                 ;XREF[1,0]:   80000090
ram:800000c4    dc2d1900        undefined4  00192DDCh                               

//Switch to thumb code at address 0x800000d0
ram:800000c8    01c08fe2        adr         r12,0x800000d1                          
ram:800000cc    1cff2fe1        bx          r12=>LAB_800000d0                       

                            LAB_800000d0:                 ;XREF[1,0]:   800000cc
ram:800000d0    8a18            add         r2,r1,r2                                
                            LAB_800000d2:                 ;XREF[1,0]:   80000120
ram:800000d2    0378            ldrb        r3,[r0,#0x0]                            
ram:800000d4    0130            add         r0,#0x1                                 
ram:800000d6    5c07            lsl         r4,r3,#0x1d                             
ram:800000d8    640f            lsr         r4,r4,#0x1d                             
ram:800000da    01d1            bne         LAB_800000e0                            
ram:800000dc    0478            ldrb        r4,[r0,#0x0]                            
ram:800000de    0130            add         r0,#0x1                                 
                            LAB_800000e0:                 ;XREF[1,0]:   800000da
ram:800000e0    1d11            asr         r5,r3,#0x4                              
ram:800000e2    01d1            bne         LAB_800000e8                            
ram:800000e4    0578            ldrb        r5,[r0,#0x0]                            
ram:800000e6    0130            add         r0,#0x1                                 
                            LAB_800000e8:                 ;XREF[1,0]:   800000e2
ram:800000e8    013c            sub         r4,#0x1                                 
ram:800000ea    05d0            beq         LAB_800000f8                            
                            LAB_800000ec:                 ;XREF[1,0]:   800000f6
ram:800000ec    0678            ldrb        r6,[r0,#0x0]                            
ram:800000ee    0130            add         r0,#0x1                                 
ram:800000f0    0e70            strb        r6,[r1,#0x0]                            
ram:800000f2    0131            add         r1,#0x1                                 
ram:800000f4    013c            sub         r4,#0x1                                 
ram:800000f6    f9d1            bne         LAB_800000ec                            
                            LAB_800000f8:                 ;XREF[1,0]:   800000ea
ram:800000f8    1e07            lsl         r6,r3,#0x1c                             
ram:800000fa    06d4            bmi         LAB_8000010a                            
ram:800000fc    2e1c            add         r6,r5,#0x0                              
ram:800000fe    0ed0            beq         LAB_8000011e                            
                            LAB_80000100:                 ;XREF[1,0]:   80000104
ram:80000100    013e            sub         r6,#0x1                                 
ram:80000102    8c55            strb        r4,[r1,r6]                              
ram:80000104    fcd1            bne         LAB_80000100                            
ram:80000106    4919            add         r1,r1,r5                                
ram:80000108    09e0            b           LAB_8000011e                            
                            LAB_8000010a:                 ;XREF[1,0]:   800000fa
ram:8000010a    0478            ldrb        r4,[r0,#0x0]                            
ram:8000010c    0130            add         r0,#0x1                                 
ram:8000010e    0c1b            sub         r4,r1,r4                                
ram:80000110    0135            add         r5,#0x1                                 
                            LAB_80000112:                 ;XREF[1,0]:   8000011c
ram:80000112    2678            ldrb        r6,[r4,#0x0]                            
ram:80000114    0134            add         r4,#0x1                                 
ram:80000116    0e70            strb        r6,[r1,#0x0]                            
ram:80000118    0131            add         r1,#0x1                                 
ram:8000011a    013d            sub         r5,#0x1                                 
ram:8000011c    f9d5            bpl         LAB_80000112                            
                            LAB_8000011e:                 ;XREF[2,0]:   800000fe,80000108
ram:8000011e    9142            cmp         r1,r2                                   
ram:80000120    d7d3            bcc         LAB_800000d2                            
ram:80000122    7047            bx          lr                                      
                            LAB_80000124:                 ;XREF[3,0]:   800000bc,80000130,80192e78
ram:80000124    102052e2        subs        r2,r2,#0x10                             
                                                          ; FWD[8,0]:   80192e9c,80192ea0,80192ea4,80192ea8
                                                          ;             80192eac,80192eb0,80192eb4,80192eb8
ram:80000128    7800b028        ldmiacs     r0!,{r3 r4 r5 r6}=>DAT_80192e9c         ;= C1h
                                                                                    ;= 45h    E
                                                                                    ;= 01h
                                                                                    ;= DDh
                                                                                    ;= 90220502h
                                                                                    ;= 23h    #
                                                          ; FWD[8,0]:   8019d5a0,8019d5a4,8019d5a8,8019d5ac
                                                          ;             8019d5b0,8019d5b4,8019d5b8,8019d5bc
ram:8000012c    7800a128        stmiacs     r1!,{ r3 r4 r5 r6 }=>DAT_8019d5a0       
ram:80000130    fbffff8a        bhi         LAB_80000124                            
ram:80000134    822eb0e1        movs        r2,r2, lsl #0x1d                        
                                                          ; FWD[3,0]:   80192eac,80192eb0,80192eb4
ram:80000138    3000b028        ldmiacs     r0!,{r4 r5}=>DAT_80192eac               ;= 7Fh    
                                                                                    ;= DDh
                                                                                    ;= 23h    #
                                                          ; FWD[2,0]:   8019d5b0,8019d5b4
ram:8000013c    3000a128        stmiacs     r1!,{ r4 r5 }=>DAT_8019d5b0             
ram:80000140    00409045        ldrmi       r4,[r0,#0x0]=>DAT_80192eb4              ;= 7Fh    
ram:80000144    00408145        strmi       r4,[r1,#0x0]=>DAT_8019d5b8              
ram:80000148    1eff2fe1        bx          lr                                      
ram:8000014c    0030b0e3        movs        r3,#0x0                                 
ram:80000150    0040b0e3        movs        r4,#0x0                                 
ram:80000154    0050b0e3        movs        r5,#0x0                                 
ram:80000158    0060b0e3        movs        r6,#0x0                                 
                            LAB_8000015c:                 ;XREF[1,0]:   80000164
ram:8000015c    102052e2        subs        r2,r2,#0x10                             
ram:80000160    7800a128        stmiacs     r1!,{ r3 r4 r5 r6 }                     
ram:80000164    fcffff8a        bhi         LAB_8000015c                            
ram:80000168    822eb0e1        movs        r2,r2, lsl #0x1d                        
ram:8000016c    3000a128        stmiacs     r1!,{ r4 r5 }                           
ram:80000170    00308145        strmi       r3,[r1,#0x0]                            
ram:80000174    1eff2fe1        bx          lr                                      
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_80000178()
          ;local_14      undefined4         -14                      ;XREF[1,0]:   8000017c
          ;local_18      undefined4         -18                      ;XREF[1,0]:   8000017a
                                                          ;XREF[1,0]:   80000190
ram:80000178    1fb5            push        { r0, r1, r2, r3, r4, lr }              
ram:8000017a    0098            ldr         r0,[sp,#0x0]=>local_18                  
ram:8000017c    0199            ldr         r1,[sp,#local_14+0x18]                  
ram:8000017e    00f0f8fc        bl          FUN_80000b72                            ;undefined FUN_80000b72()
ram:80000182    1fbd            pop         { r0, r1, r2, r3, r4, pc }              
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_80000184()
                                                          ;XREF[1,0]:   800001c0
ram:80000184    10b5            push        { r4, lr }                              
ram:80000186    10bd            pop         { r4, pc }                              
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_80000188()
                                                          ;XREF[2,0]:   80000088,800000a8
ram:80000188    b6c600eb        bl          FUN_80031c68                            ;undefined FUN_80031c68()
ram:8000018c    0210a0e1        mov         r1,r2                                   
ram:80000190    f8fffffa        blx         FUN_80000178                            ;undefined FUN_80000178()
ram:80000194    1cc09fe5        ldr         r12,[DAT_800001b8]                      ;= 00035180h
ram:80000198    0fc08ce0        add         r12,r12,pc                              
ram:8000019c    01001ce3        tst         r12,#0x1                                
ram:800001a0    0de08f12        adrne       lr,0x800001b5                           
ram:800001a4    0fe0a001        moveq       lr,pc                                   
ram:800001a8    1cff2fe1        bx          r12=>main                               ;undefined main()
ram:800001ac    01c08fe2        adr         r12,0x800001b5                          
ram:800001b0    1cff2fe1        bx          r12=>LAB_800001b4                       
                            LAB_800001b4:                 ;XREF[1,0]:   800001b0
ram:800001b4    00f0b6fd        bl          FUN_80000d24                            ;undefined FUN_80000d24()
                            DAT_800001b8:                 ;XREF[1,0]:   80000194
ram:800001b8    80510300        undefined4  00035180h                               
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_800001bc()
          ;local_8       undefined4          -8                      ;XREF[1,0]:   800001c4
                                                          ;XREF[1,0]:   80000d2e
ram:800001bc    03002de9        stmdb       sp!,{r0 r1}                             
ram:800001c0    effffffa        blx         FUN_80000184                            ;undefined FUN_80000184()
ram:800001c4    0300bde8        ldmia       sp!,{r0 r1}=>local_8                    
ram:800001c8    f5c600eb        bl          FUN_80031da4                            ;undefined FUN_80031da4()
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_800001cc()
                                                          ;XREF[4,0]:   800001cc,8000a0e4,800332a0,80033364
ram:800001cc    70b5            push        { r4, r5, r6, lr }=>FUN_800001cc        
ram:800001ce    0600            mov         r6,r0                                   
ram:800001d0    00f0b0ec        blx         FUN_80000b34                            ;undefined FUN_80000b34()
ram:800001d4    0568            ldr         r5,[r0,#0x0]                            
ram:800001d6    3000            mov         r0,r6                                   
ram:800001d8    0b30            add         r0,#0xb                                 
ram:800001da    c408            lsr         r4,r0,#0x3                              
ram:800001dc    e400            lsl         r4,r4,#0x3                              
ram:800001de    b442            cmp         r4,r6                                   
ram:800001e0    01d8            bhi         LAB_800001e6                            
ram:800001e2    0020            mov         r0,#0x0                                 
ram:800001e4    70bd            pop         { r4, r5, r6, pc }                      
                            LAB_800001e6:                 ;XREF[2,0]:   800001e0,8000022a
ram:800001e6    6868            ldr         r0,[r5,#0x4]                            
ram:800001e8    2a00            mov         r2,r5                                   
ram:800001ea    0028            cmp         r0,#0x0                                 
ram:800001ec    18d0            beq         LAB_80000220                            
                            LAB_800001ee:                 ;XREF[1,0]:   8000021e
ram:800001ee    0168            ldr         r1,[r0,#0x0]                            
ram:800001f0    a142            cmp         r1,r4                                   
ram:800001f2    11d3            bcc         LAB_80000218                            
ram:800001f4    0b00            mov         r3,r1                                   
ram:800001f6    2100            mov         r1,r4                                   
ram:800001f8    0831            add         r1,#0x8                                 
ram:800001fa    8b42            cmp         r3,r1                                   
ram:800001fc    08d3            bcc         LAB_80000210                            
ram:800001fe    4368            ldr         r3,[r0,#0x4]                            
ram:80000200    0119            add         r1,r0,r4                                
ram:80000202    4b60            str         r3,[r1,#0x4]                            
ram:80000204    0368            ldr         r3,[r0,#0x0]                            
ram:80000206    1b1b            sub         r3,r3,r4                                
ram:80000208    0b60            str         r3,[r1,#0x0]                            
ram:8000020a    5160            str         r1,[r2,#0x4]                            
ram:8000020c    0460            str         r4,[r0,#0x0]                            
ram:8000020e    01e0            b           LAB_80000214                            
                            LAB_80000210:                 ;XREF[1,0]:   800001fc
ram:80000210    4168            ldr         r1,[r0,#0x4]                            
ram:80000212    5160            str         r1,[r2,#0x4]                            
                            LAB_80000214:                 ;XREF[1,0]:   8000020e
ram:80000214    001d            add         r0,r0,#0x4                              
ram:80000216    70bd            pop         { r4, r5, r6, pc }                      
                            LAB_80000218:                 ;XREF[1,0]:   800001f2
ram:80000218    0200            mov         r2,r0                                   
ram:8000021a    4068            ldr         r0,[r0,#0x4]                            
ram:8000021c    0028            cmp         r0,#0x0                                 
ram:8000021e    e6d1            bne         LAB_800001ee                            
                            LAB_80000220:                 ;XREF[1,0]:   800001ec
ram:80000220    2100            mov         r1,r4                                   
ram:80000222    2800            mov         r0,r5                                   
ram:80000224    00f090fc        bl          FUN_80000b48                            ;undefined FUN_80000b48()
ram:80000228    0028            cmp         r0,#0x0                                 
ram:8000022a    dcd1            bne         LAB_800001e6                            
ram:8000022c    70bd            pop         { r4, r5, r6, pc }                      
                            ;************************************************************************************************
                            ;*                                           FUNCTION                                           *
                            ;************************************************************************************************
                            ;undefined FUN_8000022e()
                                                          ;XREF[3,0]:   80000cc2,800332e0,800333a0
ram:8000022e    70b5            push        { r4, r5, r6, lr }                      
ram:80000230    0400            mov         r4,r0                                   
ram:80000232    051f            sub         r5,r0,#0x4                              
ram:80000234    00f07eec        blx         FUN_80000b34                            ;undefined FUN_80000b34()
ram:80000238    0068            ldr         r0,[r0,#0x0]                            
ram:8000023a    002c            cmp         r4,#0x0                                 
ram:8000023c    1ad0            beq         LAB_80000274                            
ram:8000023e    4468            ldr         r4,[r0,#0x4]                            
ram:80000240    01e0            b           LAB_80000246                            
                            LAB_80000242:                 ;XREF[1,0]:   8000024c
ram:80000242    2000            mov         r0,r4                                   
ram:80000244    6468            ldr         r4,[r4,#0x4]                            
                            LAB_80000246:                 ;XREF[1,0]:   80000240
ram:80000246    002c            cmp         r4,#0x0                                 
ram:80000248    01d0            beq         LAB_8000024e                            
ram:8000024a    ac42            cmp         r4,r5                                   
ram:8000024c    f9d3            bcc         LAB_80000242                            
                            LAB_8000024e:                 ;XREF[1,0]:   80000248
ram:8000024e    0168            ldr         r1,[r0,#0x0]                            
ram:80000250    0a18            add         r2,r1,r0                                
ram:80000252    aa42            cmp         r2,r5                                   
ram:80000254    04d1            bne         LAB_80000260                            
ram:80000256    2a68            ldr         r2,[r5,#0x0]                            
ram:80000258    8918            add         r1,r1,r2                                
ram:8000025a    0500            mov         r5,r0                                   
ram:8000025c    0160            str         r1,[r0,#0x0]                            
ram:8000025e    00e0            b           LAB_80000262                            
                            LAB_80000260:                 ;XREF[1,0]:   80000254
ram:80000260    4560            str         r5,[r0,#0x4]                            
                            LAB_80000262:                 ;XREF[1,0]:   8000025e
ram:80000262    2868            ldr         r0,[r5,#0x0]                            
ram:80000264    4119            add         r1,r0,r5                                
ram:80000266    a142            cmp         r1,r4                                   
ram:80000268    05d1            bne         LAB_80000276                            
ram:8000026a    6168            ldr         r1,[r4,#0x4]                            
ram:8000026c    6960            str         r1,[r5,#0x4]                            
ram:8000026e    2168            ldr         r1,[r4,#0x0]                            
ram:80000270    4018            add         r0,r0,r1                                
ram:80000272    2860            str         r0,[r5,#0x0]                            
                            LAB_80000274:                 ;XREF[1,0]:   8000023c
ram:80000274    70bd            pop         { r4, r5, r6, pc }                      
                            LAB_80000276:                 ;XREF[1,0]:   80000268
ram:80000276    6c60            str         r4,[r5,#0x4]                            
ram:80000278    70bd            pop         { r4, r5, r6, pc }                      
ram:8000027a    00              ??          00h                                     
ram:8000027b    00              ??          00h                                     


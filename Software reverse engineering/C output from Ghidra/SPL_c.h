typedef unsigned char   undefined;

typedef unsigned char    undefined1;
typedef unsigned int    undefined4;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void




void Reset(void);
void UndefinedInstruction(void);
void SupervisorCall(void);
void PrefetchAbort(void);
void DataAbort(void);
void NotUsed(void);
void IRQ(void);
void FIQ(void);
void FUN_0000009c(void);
undefined8 FUN_00000104(undefined4 param_1,undefined4 param_2);
void FUN_00000108(void);
void FUN_0000010c(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void FUN_00000140(undefined4 param_1,undefined4 param_2);
void FUN_00000150(void);
void FUN_000001f8(void);
void FUN_000002a0(void);
uint FUN_000002f4(void);
uint FUN_0000033c(void);
void FUN_00000384(uint param_1);
void FUN_000003e0(uint param_1);
void FUN_0000043c(void);
void FUN_00000460(void);
void FUN_0000046c(int param_1,int param_2,int param_3,int param_4,undefined2 *param_5);
void FUN_000004d8(void);
void FUN_00000758(void);
undefined8 FUN_00000768(undefined4 param_1,undefined4 param_2);
undefined4 FUN_000007b8(undefined4 *param_1);
void FUN_000007e8(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_000007f8(undefined4 param_1);
void FUN_00000838(uint param_1);
void FUN_00000970(void);
void FUN_00000a74(void);
undefined4 FUN_00000af4(undefined4 *param_1);
void FUN_00000b24(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00000b34(undefined4 param_1);
undefined4 FUN_00000b5c(void);
undefined4 FUN_00000bc4(void);
void FUN_00000c2c(uint param_1);
void FUN_00000d08(int param_1);
int FUN_00000db8(int param_1);
undefined4 FUN_00000e90(void);
uint FUN_00000f04(void);
bool FUN_00000f68(int param_1);
undefined4 FUN_00000ff8(int param_1);
undefined4 FUN_00001150(int param_1);
undefined4 FUN_000012e0(int *param_1);
void FUN_00001670(void);
void FUN_000017d8(int param_1,uint param_2,int param_3,int param_4);
void FUN_000018c0(int param_1,uint param_2);
void FUN_000018d4(int param_1,uint param_2);
undefined4 FUN_00001930(undefined4 *param_1);
void FUN_00001960(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_00001970(undefined4 param_1);
void FUN_00001ad0(undefined4 param_1);
void FUN_00001b0c(char *param_1);
void FUN_00001b34(undefined4 param_1,int param_2);
void FUN_00001b5c(int param_1,int param_2);
void FUN_00001b84(uint param_1,int param_2,int param_3,int param_4);
byte * FUN_00001d44(byte *param_1,uint param_2);
void FUN_00001fe0(int param_1);
void FUN_00002040(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined FUN_000020cc(undefined *param_1);
undefined4 FUN_000020ec(undefined4 *param_1);
void FUN_0000210c(undefined *param_1,undefined4 param_2,undefined param_3);
void FUN_0000211c(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_0000212c(void);
void FUN_000022f8(void);
void FUN_00002334(void);
void FUN_00002374(void);
void FUN_000023b4(undefined *param_1,uint param_2);
uint FUN_00002428(int param_1,undefined *param_2,uint param_3,undefined4 param_4);
undefined4 FUN_0000254c(undefined4 param_1,int param_2,undefined4 param_3,int param_4);
void FUN_000025a8(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_0000262c(undefined4 *param_1);
void FUN_0000265c(undefined4 *param_1,undefined4 param_2,undefined4 param_3);
void FUN_0000266c(int param_1);
void FUN_000028e4(int param_1);
void FUN_00002a5c(int param_1,uint param_2);
void FUN_00002a90(int param_1);
void FUN_00002ac4(int param_1);
void FUN_00002b38(undefined4 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_00002cf0(undefined4 param_1);
void FUN_00002d24(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
uint * FUN_00002d78(uint *param_1);
longlong FUN_00002f38(undefined4 param_1);
longlong FUN_00002f44(uint param_1,uint param_2);
uint FUN_00002fc4(uint param_1,uint param_2);
longlong FUN_00003034(uint param_1,uint param_2,uint param_3,uint param_4);
undefined8 FUN_000031ac(int param_1,uint param_2,int param_3,uint param_4);
longlong FUN_00003274(uint param_1,int param_2);
uint FUN_000032d8(uint param_1);
uint FUN_00003308(uint param_1,uint param_2,uint param_3);

